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
        explicit Renderer(GLFWwindow *window, const float view_width, const float view_height, std::vector<Particle> *particles);
        void InitGL();
        void Render();
        void ProcessInputs(bool &isPaused, bool &wasPressed);
        void UpdateParticleBuffer();
        void SetParticleRadius(const float radius) { fParticleRadius = radius; }
    private:
        GLuint CreateShaderProgram(const char* vertexPath, const char* geomPath, const char* fragmentPath);

        GLFWwindow *fWindow;
        float fViewWidth;
        float fViewHeight;
        float fAspectRatio;
        std::vector<Particle> *fParticles;
        float fParticleRadius;

        // Buffer objects
        GLuint fVAO, fVBO;
        GLuint fShaderProgram;
        GLint fProjLoc, fRadiusLoc, fAspectLoc;


};

#endif