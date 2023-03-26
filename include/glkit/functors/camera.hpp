#pragma once

#include <glkit/functors/functor_types.hpp>
#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Uniform functor for scene camera matrix calculation

UNIFORM_ARGS(CameraConfig_s)
{
    point3d_t Position;
    point3d_t Direction;
};

static auto Camera_f =
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