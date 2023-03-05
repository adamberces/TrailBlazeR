#version 330 core

in vec3 Normal;
in vec3 FragPos;
in float IsColored;

uniform vec3 object_color;
uniform vec3 light_position;
uniform vec3 light_color;
uniform vec3 cam_position;

const float shininess = 12.F;
const float fresnel_strength = 0.3F;

out vec4 FragColor;

void main()
{
    // Compute the diffuse and specular components of the reflection
    vec3 light_dir = normalize(light_position - FragPos);
    vec3 view_dir = normalize(cam_position - FragPos);
    vec3 halfway_dir = normalize(light_dir + view_dir);
    
    float diffuse_intensity = max(dot(Normal, light_dir), 0.F);
    float specular_intensity = pow(max(dot(Normal, halfway_dir), 0.F), shininess);
    
    // Compute the Fresnel factor
    float fresnel_factor = fresnel_strength + (1.F - fresnel_strength) * pow(1.F - dot(view_dir, Normal), 5.F);
    
    // Compute the final color
    vec3 actual_color = object_color;
    if (IsColored <= 0)
    {
        actual_color = vec3(1.F, 1.F, 1.F);
    }

    vec3 ambient = 0.2F * actual_color;
    vec3 diffuse = diffuse_intensity * light_color * actual_color;
    vec3 specular = specular_intensity * light_color;
    vec3 reflection_color = fresnel_factor * (ambient + diffuse + specular);
    
    FragColor = vec4(reflection_color, 1.F);
}
