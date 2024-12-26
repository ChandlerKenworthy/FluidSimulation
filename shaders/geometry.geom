#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 128) out;

in vec2 particlePos[];
uniform float radius;
uniform float aspectRatio;

void main() {
    const int NUM_SEGMENTS = 128;
    vec2 center = particlePos[0];

    // Vertices of the square (offset from the center)
    vec2 topLeft = center + vec2(-radius / aspectRatio, radius);   // Top-left corner
    vec2 topRight = center + vec2(radius / aspectRatio, radius);   // Top-right corner
    vec2 bottomLeft = center + vec2(-radius / aspectRatio, -radius); // Bottom-left corner
    vec2 bottomRight = center + vec2(radius / aspectRatio, -radius); // Bottom-right corner

    // Emit the vertices for the square (in a clockwise order)
    gl_Position = vec4(topLeft, 0.0, 1.0);  // Top-left corner
    EmitVertex();
    
    gl_Position = vec4(topRight, 0.0, 1.0);  // Top-right corner
    EmitVertex();
    
    gl_Position = vec4(bottomLeft, 0.0, 1.0);  // Bottom-left corner
    EmitVertex();
    
    gl_Position = vec4(bottomRight, 0.0, 1.0);  // Bottom-right corner
    EmitVertex();
    
    EndPrimitive();  // End the primitive, drawing the square
}
