#version 330 core

in vec3 Normal;
in vec3 FragPos;

uniform vec3 object_color;
uniform vec3 light_position;
uniform vec3 light_color;
uniform vec3 cam_position;

const float shininess = 32.0;
const float fresnel_strength = 0.2;

out vec4 FragColor;

void main()
{
    // Compute the diffuse and specular components of the reflection
    vec3 light_dir = normalize(light_position - FragPos);
    vec3 view_dir = normalize(cam_position - FragPos);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    
    float diffuse_intensity = max(dot(Normal, light_dir), 0.0);
    float specular_intensity = pow(max(dot(Normal, halfway_dir), 0.0), shininess);
    
    // Compute the Fresnel factor
    float fresnel_factor = fresnel_strength + (1.0 - fresnel_strength) * pow(1.0 - dot(view_dir, Normal), 5.0);
    
    // Compute the final color
    vec3 ambient = 0.2 * object_color;
    vec3 diffuse = diffuse_intensity * light_color * object_color;
    vec3 specular = specular_intensity * light_color;
    vec3 reflection_color = fresnel_factor * (ambient + diffuse + specular);
    
    FragColor = vec4(reflection_color, 1.0);
}
