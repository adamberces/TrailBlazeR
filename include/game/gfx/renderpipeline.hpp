#pragma once

#include <vector>
#include <memory>

#include <glkit/core/shaderprogram.hpp>
#include <glkit/core/uniformiface.hpp>

#include <glkit/functors/camera.hpp>
#include <glkit/functors/model.hpp>
#include <glkit/functors/projection.hpp>
#include <glkit/functors/uniformcolor.hpp>

#include <glkit/mesh/glkcube.hpp>
#include <glkit/mesh/glksphere.hpp>

#include "shaderfiles.hpp"


namespace trailblazer::gfx
{

struct RenderConfig_s
{
    glkit::functors::CameraConfig_s CameraConfig;
    glkit::functors::ModelConfig_s ModelConfig;
    glkit::functors::ProjectionConfig_s ProjectionConfig;
};

class RenderPipeline_c
{
    RenderConfig_s Config;

    std::unique_ptr<glkit::mesh::GLKMesh_i> Mesh;
    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<glkit::core::uniforms::ShaderUniformInterface_c> Uniforms;

public:
    RenderConfig_s& config()
    {
        return Config;
    }

    void run()
    {
        if (!Mesh || !ShaderProgram || !Uniforms)
        {
            throw std::runtime_error("GLKPipeline::run: setup incomplete!");
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
        ShaderProgram = std::make_unique<glkit::core::shaders::ShaderProgram_c>(CubeShaderSources);
        Uniforms = std::make_unique<glkit::core::uniforms::ShaderUniformInterface_c>(ShaderProgram->getId());
        Mesh = std::make_unique<glkit::mesh::GLKCube_c>(1, 1, .1);

        Uniforms->add("model", glkit::functors::ModelTransformation_f);
        Uniforms->add("view", glkit::functors::Camera_f);
        Uniforms->add("projection", glkit::functors::PerspectiveProjection_f);
        Uniforms->add("myColor", glkit::functors::UniformColor_f);

        ShaderProgram->use();
        Uniforms->update("projection", &Config.ProjectionConfig);
    }


/*
    virtual void updateUniform
        (const core::uniforms::uniform_name_t& name,
         const core::uniforms::uniform_args_ptr_t argsPtr)
    {
        if (!Uniforms)
        {
            throw std::runtime_error("GLKPipeline::updateUniform: Shader is not set up yet. "
                "Please call setupShader first!");
        }
        Uniforms->update(name, argsPtr);
    }

    void addUniform
        (const core::uniforms::uniform_name_t& name,
         const core::uniforms::uniform_functor_t& functor)
    {
        if (!Uniforms)
        {
            throw std::runtime_error("GLKPipeline::addUniform: Shader is not set up yet. "
                "Please call setupShader first!");
        }
        Uniforms->add(name, functor);
    }

    void setupShader(const ShaderSourceList_s& sourceList)
    {
        ShaderProgram = decltype(ShaderProgram)
            (new core::shaders::ShaderProgram_c(sourceList));

        Uniforms = decltype(Uniforms)
            (new core::uniforms::ShaderUniformInterface_c(Shader->getId()));
    }

    template<typename MeshType, typename... CtorArgs>
    void setupMesh()
    {
        Mesh = decltype(Mesh)(new MeshType(CtorArgs));
    }
    */
};

} //trailblazer::gfx