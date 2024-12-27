#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.hpp"
#include "Solver.hpp"

#define NUM_PARTICLES 12

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
    GLFWwindow* window = glfwCreateWindow(VIEW_WIDTH, VIEW_HEIGHT, "Fluid Simulation v1.0", nullptr, nullptr);
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

    // Initalise the particles
    Solver s(NUM_PARTICLES);
    s.SetParticleSize(0.02);
    s.Start(true); // Places the particles in an evenly spaced grid or random arrangement

    // Create a renderer object to handle drawing everything into the window
    Renderer r(window, VIEW_WIDTH, VIEW_HEIGHT, s.GetParticles());
    r.SetParticleRadius(s.GetParticleSize());
    r.InitGL();

    double lastTime = glfwGetTime(); 
    double currentTime; 
    const double desiredTimestep = 1.0 / 60.0; // 60 frames per second
    bool isPaused = false;
    bool wasPressed = false;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        r.ProcessInputs(isPaused, wasPressed);

        currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Accumulate time for fixed timestep updates
        static double accumulatedTime = 0.0;
        accumulatedTime += deltaTime;

        // Update simulation at fixed timestep
        if(!isPaused) {
            while (accumulatedTime >= desiredTimestep) {
                s.Update(); // Pass the fixed timestep to s.Update()
                accumulatedTime -= desiredTimestep;
            }
        }

        r.UpdateParticleBuffer(); // Update buffers to draw new position
        r.Render(); // Draw the scene

        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
