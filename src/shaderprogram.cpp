#include <memory>
#include <vector>

#include "shader.hpp"
#include "shaderprogram.hpp"


ShaderProgram_c::ShaderProgram_c(const char** shaderSourceList)
{
    size_t shaders_count = sizeof(shaderSourceList);
    std::vector<Shader_i*> shaders;
    shaders.reserve(shaders_count);

    for (size_t i = 0; i < shaders_count; i++)
    {
        shaders.push_back()
    }

}