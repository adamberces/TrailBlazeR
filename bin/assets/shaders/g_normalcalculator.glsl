#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 Normal;

void main() {
    // Calculate the normal of the triangle surface
    vec3 v1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 v2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    Normal = normalize(cross(v1, v2));

    // Propagate triangle vertices without change
    for (int i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}