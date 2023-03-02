#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 object_color;
uniform vec3 light_position; 
uniform vec3 light_color;

void main()
{
    // ambient lightning
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light_color;
  	
    // diffuse lightning 
    vec3 lightDir = normalize(light_position - FragPos);
    float diff = max(dot(Normal, lightDir), 1.0);
    vec3 diffuse = diff * light_color;
            
    vec3 result = vec3(0.0001*(ambient + diffuse)) * object_color;
    FragColor = vec4(result, 1.0);
} 