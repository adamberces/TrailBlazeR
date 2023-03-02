#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 VertexPosition[];
in vec3 FragPosition[];

out vec3 Normal;
out vec3 FragPos;

void main()
{
    // Calculate the normal of the triangle surface
    vec3 v1 = VertexPosition[1] - VertexPosition[0];
    vec3 v2 = VertexPosition[2] - VertexPosition[0];
    Normal = normalize(cross(v1, v2));

    // Propagate triangle vertices without change
    for (int i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        FragPos = FragPosition[i];
        EmitVertex();
    }
    EndPrimitive();
}