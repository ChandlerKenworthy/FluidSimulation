#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initalise glfw/glad and make a window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    // Create the window object
    const float VIEW_WIDTH = 800;
    const float VIEW_HEIGHT = 600;
    GLFWwindow* window = glfwCreateWindow(VIEW_WIDTH, VIEW_HEIGHT, "OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Ensure GLAD is loaded
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initalise GLAD" << std::endl;
        return -1;
    }

    // Create a renderer object to handle drawing everything into the window
    std::vector<Particle> particles{};
    particles.push_back(Particle(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), 5.0f));
    Renderer r(window, VIEW_WIDTH, VIEW_HEIGHT, particles);
    r.InitGL();

    while (!glfwWindowShouldClose(window)) {
        r.ProcessInputs();
        r.Render();

        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
