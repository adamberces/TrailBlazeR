#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 object_color;
uniform vec3 light_position; 
uniform vec3 light_color;

uniform vec3 cam_position;

const float shininess = .5;

void main()
{
    // ambient
    vec3 ambient = light_color * object_color;
    
    // diffuse 
    vec3 lightDir = normalize(light_position - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = light_color * diff * object_color;
    
    // specular
    vec3 viewDir = normalize(cam_position - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = vec3(1, 1, 1) * spec;
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}