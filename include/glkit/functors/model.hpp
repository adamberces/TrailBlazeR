#pragma once

#include <glkit/functors/functor_types.hpp>
#include <glkit/core/uniforms/uniformfunctor.hpp>


namespace glkit::functors
{

UNIFORM_ARGS(ModelConfig_s)
{
    point3d_t Position;
    rotation3d_t Rotation;
    scale_t Scale;
};

auto ModelTransformation_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    ModelConfig_s* cfg = dynamic_cast<ModelConfig_s*>(ptr);

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate
        (model,
         glm::vec3(cfg->Position.X, cfg->Position.Y, cfg->Position.Z));

    model = glm::rotate(model, glm::radians(cfg->Rotation.Angle),
         glm::vec3(cfg->Rotation.X, cfg->Rotation.Y, cfg->Rotation.Z));

    model = glm::scale(model, glm::vec3(cfg->Scale.X, cfg->Scale.Y, cfg->Scale.Z));
    
    return { model };
};

} // namespace glkit::functors