#include <memory>
#include <vector>

#include "shader.hpp"
#include "shaderprogram.hpp"


#include <iostream>


using ShaderSourcePtr_t = std::string ShaderSourceList_s::*;

ShaderSourcePtr_t ShaderSourceListMember[] = {
    &ShaderSourceList_s::VertexShader,
    &ShaderSourceList_s::FragmentShader,
};

ShaderProgram_c::ShaderProgram_c(ShaderSourceList_s& ssl)
{
    std::vector<Shader_i*> shaders;
    
    for (size_t i = 0; i < 2; i++)
    {
        std::cout << ssl.*ShaderSourceListMember[i] << std::endl;
        //shaders.push_back();
    }

}