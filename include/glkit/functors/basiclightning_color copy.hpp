#pragma once

#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

UNIFORM_ARGS(LightningColorConfig_s)
{
    struct
    {
        float R;
        float G;
        float B;
    } Color;
};

auto BasicLightningColor_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    LightningColorConfig_s* cfg = dynamic_cast<LightningColorConfig_s*>(ptr);

    glm::vec4 color(cfg.Color.R, cfg.Color.G, cfg.Color.B 1.F);
        
    return { color };
};

} // namespace glkit::functors