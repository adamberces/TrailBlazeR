#pragma once

#include <glkit/functors/functor_types.hpp>
#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Uniform functor for scene light source color

UNIFORM_ARGS(Float_s)
{
    float Value;
};

static auto Float_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    Float_s* cfg = dynamic_cast<Float_s*>(ptr);
    return cfg->Value;
};

} // namespace glkit::functors