#pragma once

#include <glkit/drawables/glkbackground.hpp>

#include <glkit/core/shaders/shaderprogram.hpp>
#include <glkit/core/uniforms/uniformiface.hpp>
#include <glkit/functors/float.hpp>

#include <trailblazer/game/clock.hpp>
#include <trailblazer/game/constants.hpp>


namespace trailblazer::pipelines
{

/////////////////////////////////////////////////////////////////////////////////////////
/// This class is not inherits from RenderPipeline_i, as it is not part of the 3D scene
/// but uses the same semantics and elements

class BackgroundPipeline_c
{
    std::unique_ptr<glkit::drawables::GLKBackground_c> Background;
    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<glkit::core::uniforms::ShaderUniformInterface_c> Uniforms;

public:
    glkit::functors::Float_s AlphaConfig;

    inline void run()
    {
        if (!Background || !ShaderProgram || !Uniforms)
        {
            throw std::runtime_error("BackgroundPipeline_c::run: call setup first!");
        }
        
                
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Background->activateTexture();
        ShaderProgram->use();
        Uniforms->update("alpha", &AlphaConfig);

        Background->draw();
    }

    inline void setup()
    {
        glkit::core::shaders::ShaderSourceList_s SSL;
        SSL.VertexShaderPath = "./assets/shaders/v_ortotexture.glsl";
        SSL.FragmentShaderPath = "./assets/shaders/f_texturedquad.glsl";

        ShaderProgram = std::make_unique<glkit::core::shaders::ShaderProgram_c>(SSL);
        Uniforms = std::make_unique<glkit::core::uniforms::ShaderUniformInterface_c>(ShaderProgram->getId());
        
        // This uniform is used to fade in/out the background image
        Uniforms->add("alpha", glkit::functors::Float_f);
    }

    explicit BackgroundPipeline_c(std::string fileName) :
        Background(std::make_unique<glkit::drawables::GLKBackground_c>(fileName))
    {
        setup();
        AlphaConfig.Value = 1.F;
    }
};

} // namespace trailblazer::pipelines