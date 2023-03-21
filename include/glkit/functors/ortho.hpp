#pragma once

#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

/////////////////////////////////////////////////////////////////////////////////////////
// Uniform functor for perspective projection matrix generation

UNIFORM_ARGS(ProjectionConfig_s)
{
    float FOV;

    unsigned ScreenWidth;
    unsigned ScreenHeight;

    float NearPlane;
    float FarPlane;
};

static auto OrthogonalProjection_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    ProjectionConfig_s* cfg = dynamic_cast<ProjectionConfig_s*>(ptr);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(
        glm::radians(cfg->FOV),
        float(cfg->ScreenWidth) / float(cfg->ScreenHeight),
        cfg->NearPlane, cfg->FarPlane);
        
    return { projection };
};

} // namespace glkit::functors