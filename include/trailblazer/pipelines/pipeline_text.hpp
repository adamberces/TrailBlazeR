#pragma once

#include <glkit/drawables/glktext.hpp>

#include <glkit/core/shaders/shaderprogram.hpp>
#include <glkit/core/uniforms/uniformiface.hpp>
#include <glkit/functors/ortho.hpp>
#include <glkit/functors/color.hpp>

#include <trailblazer/game/constants.hpp>


namespace trailblazer::pipelines
{

/////////////////////////////////////////////////////////////////////////////////////////
// This class is not inherits from RenderPipeline_i, as it is not part of the 3D scene
// but uses the same semantics and elements

class TextPipeline_c
{
    std::unique_ptr<glkit::drawables::GLKText_c> TextDrawer;

    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<glkit::core::uniforms::ShaderUniformInterface_c> Uniforms;
    glkit::functors::OrthoConfig_s ProjectionConfig;

public:
    void run(std::string text, int x, int y, glkit::functors::rgb_t color)
    {
        if (!TextDrawer || !ShaderProgram)
        {
            throw std::runtime_error("BackgroundPipeline_c::run: call setup first!");
        }
        
        glkit::functors::ColorConfig_s colorconfig;
        colorconfig.Color = color;

        ShaderProgram->use();
        Uniforms->update("projection", &ProjectionConfig);
        Uniforms->update("textColor", &colorconfig);
        TextDrawer->drawText(text, x, y);
    }

    void setup()
    {
        glkit::core::shaders::ShaderSourceList_s SSL;
        SSL.VertexShaderPath = "./assets/shaders/v_text.glsl";
        SSL.FragmentShaderPath = "./assets/shaders/f_text.glsl";
        ShaderProgram = std::make_unique<glkit::core::shaders::ShaderProgram_c>(SSL);
        ShaderProgram->use();
       
        Uniforms = std::make_unique<glkit::core::uniforms::ShaderUniformInterface_c>(ShaderProgram->getId());
        Uniforms->add("projection", glkit::functors::OrthogonalProjection_f);
        Uniforms->add("textColor", glkit::functors::Color_f);

        ProjectionConfig.Xmax = Constants_s::WINDOW_WIDTH;
        ProjectionConfig.Ymax = Constants_s::WINDOW_HEIGHT;
    }

    TextPipeline_c(std::string fontFileName) :
        TextDrawer(std::make_unique<glkit::drawables::GLKText_c>(fontFileName))
    {
        setup();
    }
};

} // namespace trailblazer::pipelines