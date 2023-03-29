#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D bgTexture;
uniform float alpha;

void main()
{
    vec4 pixel = texture(bgTexture, TexCoord);
    FragColor = vec4(pixel.xyz, alpha);
}
