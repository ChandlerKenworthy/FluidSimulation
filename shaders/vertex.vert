#version 330 core

layout(location = 0) in vec2 aPos; // Particle position
uniform mat4 projection; // Projection matrix for 2D space

out vec2 particlePos; // Pass particle position to the geometry shader

void main() {
    particlePos = aPos;
    gl_Position = projection * vec4(aPos, 0.0, 1.0); // Apply transformation
}
