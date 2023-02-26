#pragma once

#include <glkit/core/uniformfunctor.hpp>


namespace glkit::functors
{

UNIFORM_ARGS(CameraConfig_s)
{
    struct
    {
        float X;
        float Y;
        float Z;
    } Position;

    struct
    {
        float X;
        float Y;
        float Z;
    } Direction;
};

auto Camera_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    CameraConfig_s* cfg = dynamic_cast<CameraConfig_s*>(ptr);

    glm::mat4 view = glm::mat4(1.0f); 
    view = glm::lookAt
        (glm::vec3(cfg->Position.X, cfg->Position.Y, cfg->Position.Z),
         glm::vec3(cfg->Direction.X, cfg->Direction.Y, cfg->Direction.Z),
         glm::vec3(0.0f, 1.0f, 0.0f));
        
    return { view };
};

} // namespace glkit::functors