
#include "Renderer.hpp"

Renderer::Renderer(GLFWwindow *window, const int view_width, const int view_height, std::vector<Particle> &particles) : 
fWindow(window), fViewWidth(view_width), fViewHeight(view_height), fParticles(&particles) { 
    
}

GLuint Renderer::CreateShaderProgram(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fragShaderFile;

    // Ensure ifstream objects can throw exceptios
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Try to open the files
    try {
        vShaderFile.open(vertexPath);
        fragShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fragShaderStream;

        // Read file buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fragShaderStream << fragShaderFile.rdbuf();

        vShaderFile.close();
        fragShaderFile.close();

        // Convert stream to a string
        vertexCode = vShaderStream.str();
        fragmentCode = fragShaderStream.str();
    } catch(std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCESSFULLY_READ" << std::endl;
        std::cerr << "What: " << e.what() << "\n";
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
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
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shaderProgram;
}

void Renderer::InitGL(const float particle_smoothing_length) {
    glfwMakeContextCurrent(fWindow); // Ensure the correct context is active
    
    glViewport(0, 0, fViewWidth, fViewHeight);
    glClearColor(0.9f, 0.9f, 0.9f, 1); // Light grey background colour

    // Compile and link shaders
    fShaderProgram = CreateShaderProgram("..\\shaders\\vertex.vert", "..\\shaders\\fragment.frag");

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
    glPointSize(10.0f); // Set point size for rendering particles

}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Use the shader program
    glUseProgram(fShaderProgram);

    /*
    // Set up the projection matrix (2D orthographic projection)
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(fViewWidth), 0.0f, static_cast<float>(fViewHeight));
    GLint projLoc = glGetUniformLocation(fShaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Set the point size (optional, you can change this dynamically)
    GLint pointSizeLoc = glGetUniformLocation(fShaderProgram, "pointSize");
    glUniform1f(pointSizeLoc, 10.0f); // Set point size to 10.0f

    // Bind VAO and render particles
    glBindVertexArray(fVAO);
    glDrawArrays(GL_POINTS, 0, fParticles->size()); // Draw particles as points
    glBindVertexArray(0);
    */
    glfwSwapBuffers(fWindow); // Swap buffers for the next frame
}

void Renderer::ProcessInputs() {
    if(glfwGetKey(fWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(fWindow, GL_TRUE);
    }
}
