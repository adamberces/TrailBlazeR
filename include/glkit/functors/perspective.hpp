#pragma once

#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

/////////////////////////////////////////////////////////////////////////////////////////
// Uniform functor for perspective projection matrix generation

UNIFORM_ARGS(OrthoConfig_s)
{
    float Xmin = 0.f;
    float Xmax;
    float Ymin = 0.f;
    float Ymax;
};

static auto PerspectiveProjection_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    OrthoConfig_s* cfg = dynamic_cast<OrthoConfig_s*>(ptr);

    glm::mat4 projection = glm::ortho(cfg->Xmin, cfg->Xmax, cfg->Ymin, cfg->YMax);
        
    return { projection };
};

} // namespace glkit::functors