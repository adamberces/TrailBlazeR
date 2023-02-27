#pragma once

#include <memory>
#include <unordered_map>

#include <glkit/core/uniforms/shaderuniform.hpp>


namespace glkit::core::uniforms
{

/////////////////////////////////////////////////////////////////////////////////////////
// This class maintains a list of ShaderUniform_c's and provides a convient interface
// to assign the uniform values for a given Shader Program

class ShaderUniformInterface_c
{
    GLuint ProgramId;
    std::unordered_map<uniform_name_t, std::unique_ptr<ShaderUniform_c>> UniformList;

public:
    void update(const uniform_name_t& name, const uniform_args_ptr_t argsPtr) const;

    void add(const uniform_name_t& name, const uniform_functor_t& func);

    ShaderUniformInterface_c(GLuint programId);
};


} // namespace glkit::core::uniforms
