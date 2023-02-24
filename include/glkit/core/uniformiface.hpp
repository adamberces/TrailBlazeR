#pragma once

#include "globject.hpp"


namespace glkit::core::uniforms
{

/////////////////////////////////////////////////////////////////////////////////////////
// uniform_functor_t's are special function pointers, which is called by the ShaderUniform_c
// class which wraps a respective uniform variable. This function calculates the value
// (which takes one type from uniform_types_t) which is then passed to the shader.

using shader_uniform_list_t = std::vector<ShaderUniform_c>;

class ShaderUniformInterface_c
{
    GLuint ProgramId;
    shader_uniform_list_t UniformList;

public:

    ShaderUniformInterface_c
        (GLuint programId,
         shader_uniform_list_t uniformList) :
        UniformName(uniformName),
        UniformList(uniformList)
    {
    }
};


} // namespace glkit::core
