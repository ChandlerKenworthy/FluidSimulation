
#include "Renderer.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Renderer::Renderer(GLFWwindow *window, const float view_width, const float view_height, std::vector<Particle> &particles) : 
fWindow(window), fViewWidth(view_width), fViewHeight(view_height), fParticles(&particles) { 
    
}

GLuint Renderer::CreateShaderProgram(const char* vertexPath, const char* geomPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string geomCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream gShaderFile;
    std::ifstream fragShaderFile;

    // Ensure ifstream objects can throw exceptios
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Try to open the files
    try {
        vShaderFile.open(vertexPath);
        gShaderFile.open(geomPath);
        fragShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, gShaderStream, fragShaderStream;

        // Read file buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();
        fragShaderStream << fragShaderFile.rdbuf();

        vShaderFile.close();
        gShaderFile.close();
        fragShaderFile.close();

        // Convert stream to a string
        vertexCode = vShaderStream.str();
        geomCode = gShaderStream.str();
        fragmentCode = fragShaderStream.str();
    } catch(std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCESSFULLY_READ" << std::endl;
        std::cerr << "What: " << e.what() << "\n";
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* gShaderCode = geomCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, geometry, fragment;
    int success;
    char infoLog[512];

    // Compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile geometry shader
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(geometry, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, geometry);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(geometry);
    glDeleteShader(fragment);

    return shaderProgram;
}

void Renderer::InitGL() {
    glfwMakeContextCurrent(fWindow); // Ensure the correct context is active
    
    glViewport(0, 0, fViewWidth, fViewHeight);
    glClearColor(0.9f, 0.9f, 0.9f, 1); // Light grey background colour

    // Compile and link shaders
    fShaderProgram = CreateShaderProgram("..\\shaders\\vertex.vert", "..\\shaders\\geometry.geom", "..\\shaders\\fragment.frag");

    // Generate the VAO and VBO
    glGenVertexArrays(1, &fVAO);
    glGenBuffers(1, &fVBO);
    glBindVertexArray(fVAO);

    // Set up the VBO and bind data
    glBindBuffer(GL_ARRAY_BUFFER, fVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * fParticles->size(), fParticles->data(), GL_STATIC_DRAW);

    // Define the vertex position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the VBO

    glBindVertexArray(0); // Unbind the VAO

    // Set up OpenGL for point smoothing and projection matrix
    glEnable(GL_MULTISAMPLE);

    glUseProgram(fShaderProgram);
    fProjLoc = glGetUniformLocation(fShaderProgram, "projection");
    fRadiusLoc = glGetUniformLocation(fShaderProgram, "radius");
    fAspectLoc = glGetUniformLocation(fShaderProgram, "aspectRatio");

    // Calculate the aspect ratio
    fAspectRatio = fViewWidth / fViewHeight;
}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Use the shader program
    glUseProgram(fShaderProgram);

    // Set up the projection matrix (2D orthographic projection)
    glm::mat4 projection = glm::ortho(
        -fViewWidth / 2., 
        fViewWidth / 2., 
        -fViewHeight / 2., 
        fViewHeight / 2.
    );

    glUniformMatrix4fv(fProjLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1f(fRadiusLoc, 0.03f);  // Set the radius for the particles
    glUniform1f(fAspectLoc, fAspectRatio);

    // Bind VAO and render particles
    glBindVertexArray(fVAO);
    glDrawArrays(GL_POINTS, 0, fParticles->size()); // Draw particles as points
    glBindVertexArray(0);
    glfwSwapBuffers(fWindow); // Swap buffers for the next frame

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << err << std::endl;
    }

}

void Renderer::ProcessInputs() {
    if(glfwGetKey(fWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(fWindow, GL_TRUE);
    }
}
