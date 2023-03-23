#pragma once

#include <glkit/drawables/background.hpp>


namespace trailblazer::pipelines
{

/////////////////////////////////////////////////////////////////////////////////////////
// This class is not inherits from RenderPipeline_i, as it is not part of the 3D scene
// but uses the same semantics and elements

class BackgroundPipeline_c
{
    std::unique_ptr<glkit::drawables::GLKBackground_c> Background;
    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;

public:
    void run()
    {
        if (!Background || !ShaderProgram)
        {
            throw std::runtime_error("BackgroundPipeline_c::run: call setup first!");
        }
        
        Background->activateTexture();
        ShaderProgram->use();
        Background->draw();
    }

    void setup()
    {
        glkit::core::shaders::ShaderSourceList_s SSL;
        SSL.VertexShaderPath = "./assets/shaders/v_ortotexture.glsl";
        SSL.FragmentShaderPath = "./assets/shaders/f_texturedquad.glsl";

        ShaderProgram = std::make_unique<glkit::core::shaders::ShaderProgram_c>(SSL);
    }

    BackgroundPipeline_c(std::string fileName) :
        Background(std::make_unique<glkit::drawables::GLKBackground_c>(fileName))
    {}
};

} // namespace trailblazer::pipelines