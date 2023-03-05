#version 330 core

layout (location = 0) in vec4 aPos;

out vec3 VertexPosition;
out vec3 FragPosition;
out float Colored;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    vec3 Coordinate = vec3(aPos[0], aPos[1], aPos[2]);

    Colored = aPos[3];
    VertexPosition = Coordinate;
    FragPosition = vec3(model * vec4(Coordinate, 1.F));
    
    gl_Position = projection * view * model * vec4(Coordinate, 1.F);
}