#version 330 core

layout(location = 0) in vec2 aPos; // Particle position

uniform mat4 projection; // Projection matrix for 2D space
uniform float pointSize; // Point size

void main() {
    gl_Position = projection * vec4(aPos, 0.0, 1.0); // Apply transformation
    gl_PointSize = pointSize; // Set the size of the point
}
