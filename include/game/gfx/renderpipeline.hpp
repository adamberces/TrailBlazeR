#pragma once

#include <memory>

#include <glkit/core/shaderprogram.hpp>
#include <glkit/core/uniformiface.hpp>

#include <glkit/functors/camera.hpp>
#include <glkit/functors/model.hpp>
#include <glkit/functors/projection.hpp>
#include <glkit/functors/uniformcolor.hpp>

#include <glkit/mesh/glkcube.hpp>
#include <glkit/mesh/glksphere.hpp>


namespace trailblazer::gfx
{

struct RenderConfig_s
{
    glkit::functors::CameraConfig_s CameraConfig;
    glkit::functors::ModelConfig_s ModelConfig;
    glkit::functors::ProjectionConfig_s ProjectionConfig;
};

class RenderPipeline_i
{
protected:
    RenderConfig_s Config;
    glkit::core::shaders::ShaderSourceList_s SSL;
    
    std::unique_ptr<glkit::mesh::GLKMesh_i> Mesh;
    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<glkit::core::uniforms::ShaderUniformInterface_c> Uniforms;
    
    virtual void constructMesh() = 0;
    virtual void setupSSL() = 0;

public:
    RenderConfig_s& config()
    {
        return Config;
    }

    void run()
    {
        if (!Mesh || !ShaderProgram || !Uniforms)
        {
            throw std::runtime_error("GLKPipeline::run: call setup first!");
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        ShaderProgram->use();

        Uniforms->update("model", &Config.ModelConfig);
        Uniforms->update("view", &Config.CameraConfig);
        Uniforms->update("myColor", &Config.ModelConfig);

        Mesh->draw();
    }

    void setup()
    {
        setupSSL();
        constructMesh();

        ShaderProgram = std::make_unique<glkit::core::shaders::ShaderProgram_c>(SSL);
        Uniforms = std::make_unique<glkit::core::uniforms::ShaderUniformInterface_c>(ShaderProgram->getId());

        Uniforms->add("model", glkit::functors::ModelTransformation_f);
        Uniforms->add("view", glkit::functors::Camera_f);
        Uniforms->add("projection", glkit::functors::PerspectiveProjection_f);
        Uniforms->add("myColor", glkit::functors::UniformColor_f);

        ShaderProgram->use();
        Uniforms->update("projection", &Config.ProjectionConfig);
    }
};

class TilePipeline_c : public RenderPipeline_i
{
    void setupSSL() override
    {
        SSL.VertexShaderPath = "./assets/shaders/v_perspective.glsl";
        SSL.FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl";
    }

    void constructMesh() override
    {
        Mesh = std::make_unique<glkit::mesh::GLKCube_c>(1, 1, .3);
    }
};

} //trailblazer::gfx