#include <game/gfx/renderpipeline.hpp>  


namespace trailblazer::gfx
{

glkit::functors::ProjectionConfig_s RenderPipeline_i::ProjectionConfig =
    glkit::functors::ProjectionConfig_s {};
glkit::functors::CameraConfig_s RenderPipeline_i::CameraConfig =
    glkit::functors::CameraConfig_s {};

void RenderPipeline_i::run()
{
    if (!Mesh || !ShaderProgram || !Uniforms)
    {
        throw std::runtime_error("GLKPipeline::run: call setup first!");
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ShaderProgram->use();

    Uniforms->update("projection", &ProjectionConfig);
    Uniforms->update("model", &ModelConfig);
    Uniforms->update("view", &CameraConfig);
    Uniforms->update("myColor", &ModelConfig);

    Mesh->draw();
}

void RenderPipeline_i::setup()
{
    setupSSL();
    constructMesh();

    ShaderProgram = std::make_unique<glkit::core::shaders::ShaderProgram_c>(SSL);
    Uniforms = std::make_unique<glkit::core::uniforms::ShaderUniformInterface_c>(ShaderProgram->getId());

    Uniforms->add("model", glkit::functors::ModelTransformation_f);
    Uniforms->add("view", glkit::functors::Camera_f);
    Uniforms->add("projection", glkit::functors::PerspectiveProjection_f);
    Uniforms->add("myColor", glkit::functors::UniformColor_f);
}

} //namespace trailblazer::gfx
