#pragma once

#include <glkit/core/buffers/dynamicvertexarray.hpp>
#include <glkit/core/shaders/shaderprogram.hpp>
#include <glkit/core/uniforms/uniformiface.hpp>
#include <glkit/functors/ortho.hpp>
#include <glkit/functors/color.hpp>

#include <trailblazer/game/constants.hpp>


namespace trailblazer::hud
{

class TextPipeline_c
{
    std::unique_ptr<core::buffers::DynamicVertexArrayObject_c<float>> VertexArrayObject;

    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<glkit::core::uniforms::ShaderUniformInterface_c> Uniforms;
    glkit::functors::OrthoConfig_s ProjectionConfig;

    void RenderText(std::string text, float x, float y, glm::vec3 color)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // iterate through all characters
        std::string::const_iterator c;
        for(char c : text)
        {
            Character_s ch = Characters[*c];

            float xpos = x + ch.XOffset;
            float ypos = y - (ch.Height - ch.YOffset);
            float w = ch.Width;
            float h = ch.Height;

            // update VBO for each character
            std::vector<float> =
            {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }           
            };

            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureId);
            VertexArrayObject->copyVertexData(vertices);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += ch.XAdvance;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


public:
    void drawText(std::string text, int x, int y, glkit::functors::rgb_t color)
    {
        if (!ShaderProgram || !VertexArrayObject)
        {
            throw std::runtime_error("BackgroundPipeline_c::run: call setup first!");
        }
        
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        glkit::functors::Color_f colorconfig { color };

        ShaderProgram->use();
        Uniforms->update("projection", &ProjectionConfig);
        Uniforms->update("textColor", &colorconfig);

        RenderText(text, 100, 100, glm::vec3(1, 0, 1));

        glEnable(GL_DEPTH_TEST); 
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    }

    void setupShader()
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

    void setupBuffer();
    {
        VertexArrayObject = std::make_unique<core::buffers::DynamicVertexArrayObject_c<float>>();

        // 6 vertices for the two triangles of a 2D quad, 2 screen and 2 texture coordinates for each 
        VertexArrayObject->allocateVertexBuffer(6 * 2 * 2)
        VertexArrayObject->setVertexAttribute(0, 4);     
    }

    void setup()
    {   
        setupBuffer();
        setupShader();
        loadFont("./assets/fonts/font");
    }

    TextDrawer_c()
    {}
};

} // namespace trailblazer::hud