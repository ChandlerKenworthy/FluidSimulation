#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Particle.hpp"

class Renderer {
    public:
        explicit Renderer(GLFWwindow *window, const int view_width, const int view_height, std::vector<Particle> &particles);
        void InitGL(const float particle_smoothing_length);
        void Render();
        void ProcessInputs();
    private:
        GLuint CreateShaderProgram(const char* vertexPath, const char* fragmentPath);

        GLFWwindow *fWindow;
        int fViewWidth;
        int fViewHeight;
        std::vector<Particle> *fParticles;

        // Buffer objects
        GLuint fVAO, fVBO;
        GLuint fShaderProgram;


};

#endif