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
        explicit Renderer(GLFWwindow *window, const float view_width, const float view_height, std::vector<Particle> &particles);
        void InitGL();
        void Render();
        void ProcessInputs();
        void UpdateParticleBuffer();
    private:
        GLuint CreateShaderProgram(const char* vertexPath, const char* geomPath, const char* fragmentPath);

        GLFWwindow *fWindow;
        float fViewWidth;
        float fViewHeight;
        float fAspectRatio;
        std::vector<Particle> *fParticles;

        // Buffer objects
        GLuint fVAO, fVBO;
        GLuint fShaderProgram;
        GLint fProjLoc, fRadiusLoc, fAspectLoc;


};

#endif