#pragma once

#include <glkit/window/background.hpp>


namespace trailblazer::pipelines
{

class BackgroundPipeline_c
{
    std::unique_ptr<glkit::window::GLKBackgound_c> Background;
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
        Background(std::make_unique<glkit::window::GLKBackgound_c>(fileName))
    {}
};

} // namespace trailblazer::pipelines