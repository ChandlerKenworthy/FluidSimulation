#version 330 core

out vec4 FragColor; // Output color of the particle

void main() {
    // Simple color for particles (could be parameterized)
    FragColor = vec4(0.2f, 0.6f, 1.0f, 1.0f); // Light blue color
}
