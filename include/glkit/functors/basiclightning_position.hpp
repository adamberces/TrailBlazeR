#pragma once

#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

UNIFORM_ARGS(LightningPositionConfig_s)
{
    struct
    {
        float X;
        float Y;
        float Z;
    } Position;
};

auto BasicLightningPosition_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    LightningPositionConfig_s* cfg = dynamic_cast<LightningPositionConfig_s*>(ptr);

    glm::vec3 pos(cfg->Position.X, cfg->Position.Y, cfg->Position.Z);
        
    return { pos };
};

} // namespace glkit::functors