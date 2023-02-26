#pragma once

#include <vector>
#include <variant>
#include <functional>

#include <glkit/core/globject.hpp>


namespace glkit::core::uniforms
{

/////////////////////////////////////////////////////////////////////////////////////////
// uniform_functor_t's are special function pointers, which is called by the ShaderUniform_c
// class which wraps a respective uniform variable. This function calculates the value
// (which takes one type from uniform_types_t) which is then passed to the shader.
// 
// A functor takes its input arguments of type uniform_args_ptr_t (UniformFunctorArgs_i*)
// This is an abstract parent struct, from which we can derive structs which can be passed
// to uniform functors and thanks to polymorphism we can transfer any number/type of arguments
// packed into these structs (which has to be dynamic_casted to the actual struct type).
// This header also provides the UNIFORM_ARGS macro and an example use, EmptyPlaceholder,
// which is intended to be used when no arguments are needed to pass to an uniform functor.

struct UniformFunctorArgs_i
{
    virtual ~UniformFunctorArgs_i() {};
};

#define UNIFORM_ARGS(struct_name) struct struct_name : glkit::core::uniforms::UniformFunctorArgs_i

UNIFORM_ARGS(EmptyPlaceholder)
{
};

/////////////////////////////////////////////////////////////////////////////////////////

using uniform_types_t = std::variant<
    glm::vec3,
    glm::vec4,
    glm::mat4
>;

using uniform_args_ptr_t = UniformFunctorArgs_i*;

using uniform_functor_t =
    std::function<uniform_types_t(uniform_args_ptr_t)>;

} //namespace glkit::core::uniforms