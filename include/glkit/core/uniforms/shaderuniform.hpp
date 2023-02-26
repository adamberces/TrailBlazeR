#pragma once

#include <string>

#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::core::uniforms
{

/////////////////////////////////////////////////////////////////////////////////////////
// Class represents a shader's uniform variable and the strategy of how a value
// is assigned to this variable. Thus it is constructed by the uniform's name 
// (from the GLSL source code) and a functor object, which points to a function which
// takes an uniform_args_ptr_t (which can hold any number of arguments) and returns
// an uniform_types_t (which is an std::variant under the hood). The responsibility of
// this class is essentially to wrap the glUniform(etc...) OpenGL API functions.
// setData calls the functor and assigns the resulting value to a uniform of the given
// shader program by calling the correct API function

using uniform_name_t = std::string;

class ShaderUniform_c
{
    uniform_name_t UniformName;
    uniform_functor_t UniformFunctor;

public:
    void setData(GLuint shaderProgramId, uniform_args_ptr_t uniformArguments) const;

    ShaderUniform_c(const uniform_name_t&, const uniform_functor_t&);
};

} // namespace glkit::core::uniforms
