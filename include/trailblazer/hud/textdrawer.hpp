#pragma once

#include <glkit/core/buffers/vertexarray.hpp>
#include <glkit/core/shaders/shaderprogram.hpp>
#include <glkit/core/uniforms/uniformiface.hpp>
#include <glkit/core/functors/ortho.hpp>
#include <glkit/core/functors/color.hpp>

namespace trailblazer::hud
{

class TextPipeline_c
{
    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<core::buffers::VertexArrayObject_c<float>> VertexArrayObject;
    std::unique_ptr<glkit::core::uniforms::ShaderUniformInterface_c> Uniforms;

    unsigned int VAO, VBO;

      
    void RenderText(std::string text, float x, float y, glm::vec3 color)
    {
        // activate corresponding render state	
        ShaderProgram->use();
        glUniform3f(glGetUniformLocation(ShaderProgram->getId(), "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++) 
        {
            Character_s ch = Characters[*c];

            float xpos = x + ch.XOffset;
            float ypos = y - (ch.Height - ch.YOffset);
            float w = ch.Width;
            float h = ch.Height;

            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }           
            };

            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureId);

            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += ch.XAdvance; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


public:
    void drawText(std::string text)
    {
        if (!ShaderProgram)
        {
            throw std::runtime_error("BackgroundPipeline_c::run: call setup first!");
        }
        
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        ShaderProgram->use();
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
    }

    void setupBuffer
    {

    }

    void setup()
    {


        

        ShaderProgram->use();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(1024), 0.0f, static_cast<float>(768));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram->getId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        loadFont("./assets/fonts/font");

        // configure VAO/VBO for texture quads
        // -----------------------------------
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    TextDrawer_c()
    {}
};

} // namespace trailblazer::hud