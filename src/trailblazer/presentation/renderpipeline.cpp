#include <stdexcept>
#include <trailblazer/pipelines/renderpipeline.hpp>  


namespace trailblazer::pipelines
{

// Define static members of RenderPipeline_i
glkit::functors::ProjectionConfig_s RenderPipeline_i::ProjectionConfig =
    glkit::functors::ProjectionConfig_s {};
glkit::functors::CameraConfig_s RenderPipeline_i::CameraConfig =
    glkit::functors::CameraConfig_s {};

glkit::functors::LightningColorConfig_s RenderPipeline_i::LightningColorConfig =
    glkit::functors::LightningColorConfig_s {};
glkit::functors::LightningPositionConfig_s RenderPipeline_i::LightningPositionConfig =
    glkit::functors::LightningPositionConfig_s {};
glkit::functors::LightningPositionConfig_s RenderPipeline_i::CameraPositionConfig =
    glkit::functors::LightningPositionConfig_s {};

void RenderPipeline_i::run()
{
    if (!Mesh || !ShaderProgram || !Uniforms)
    {
        throw std::runtime_error("GLKPipeline::run: call setup first!");
    }

    ShaderProgram->use();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Uniforms->update("model", &ModelConfig);
    Uniforms->update("view", &CameraConfig);
    Uniforms->update("projection", &ProjectionConfig);
    Uniforms->update("light_color", &LightningColorConfig);
    Uniforms->update("light_position", &LightningPositionConfig);
    Uniforms->update("cam_position", &LightningPositionConfig);
    Uniforms->update("object_color", &ModelColorConfig);
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
    Uniforms->add("light_color", glkit::functors::BasicLightningColor_f);
    Uniforms->add("light_position", glkit::functors::BasicLightningPosition_f);
    Uniforms->add("cam_position", glkit::functors::BasicLightningPosition_f);
    Uniforms->add("object_color", glkit::functors::BasicLightningColor_f);

}

} //namespace trailblazer::pipelines
