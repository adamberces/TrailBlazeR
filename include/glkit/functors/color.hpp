#pragma once

#include <glkit/functors/functor_types.hpp>
#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

/////////////////////////////////////////////////////////////////////////////////////////
// Uniform functor for scene light source color

UNIFORM_ARGS(ColorConfig_s)
{
    rgb_t Color;
};

static auto Color_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    ColorConfig_s* cfg = dynamic_cast<ColorConfig_s*>(ptr);

    glm::vec3 color(cfg->Color.R, cfg->Color.G, cfg->Color.B);
        
    return { color };
};

} // namespace glkit::functors