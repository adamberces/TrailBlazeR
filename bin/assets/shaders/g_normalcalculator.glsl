#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 VertexPosition[];
in vec3 FragPosition[];
in float Colored[];

out vec3 Normal;
out vec3 FragPos;
out float IsColored;

void main()
{
    // Calculate the normal of the triangle surface
    vec3 v1 = FragPosition[1] - FragPosition[0];
    vec3 v2 = FragPosition[2] - FragPosition[0];
    Normal = normalize(cross(v1, v2));

    // Propagate triangle vertices without change
    for (int i = 0; i < gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        FragPos = FragPosition[i];
        IsColored = Colored[i];
        EmitVertex();
    }
    EndPrimitive();
}