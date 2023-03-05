#pragma once

#include <glkit/core/uniforms/uniformfunctor.hpp>


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
        float X = 1.F;
        float Y = 0.F;
        float Z = 0.F;
        float Angle;
    } Rotation;

    struct
    {
        float X = 1.F;
        float Y = 1.F;
        float Z = 1.F;
    } Scale;
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