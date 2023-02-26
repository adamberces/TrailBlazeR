#pragma once

#include <glkit/core/uniformfunctor.hpp>


namespace glkit::functors
{

UNIFORM_ARGS(ModelConfig_s)
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
        float Angle;
    } Rotation;

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
  
    return { model };
};

} // namespace glkit::functors