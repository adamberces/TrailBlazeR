#pragma once

#include <glkit/window/background.hpp>
#include <string>
#include <map>

#include <png/pngimage.hpp>
#include <opencv2/opencv.hpp>

namespace trailblazer::pipelines
{

class TextPipeline_c
{
    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    struct Character_s
    {
        int Width;
        int Height;
        int XOffset;
        int YOffset;
        int XAdvance;

        unsigned int TextureId;
    };

    std::map<char, Character_s> Characters;
    unsigned int VAO, VBO;

    void loadFont(std::string fileName)
    {
        png::PngImage_c im(fileName + ".png");

        FILE *f;
        std::string fntFile = fileName + ".fnt";
        f = fopen(fntFile.c_str(), "r");

        int n;
        fscanf(f, "chars count=%d\n", &n);
        for (int i = 0; i < n; i++)
        {
            // ID, x, y, Width, Height, x_offset, y_offset, w_full
            int x;
            int y;
            int Id;
            Character_s c;
            fscanf(f, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d\n",
                &Id, &x, &y, &(c.Width), &(c.Height), &(c.XOffset), &(c.YOffset), &(c.XAdvance));

            auto cropped = im.crop(x, y, c.Width, c.Height);

            // generate texture
            glGenTextures(1, &(c.TextureId));
            glBindTexture(GL_TEXTURE_2D, c.TextureId);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                (cropped->hasAlpha() ? GL_RGBA : GL_RGB),
                c.Width,
                c.Height,
                0,
                (cropped->hasAlpha() ? GL_RGBA : GL_RGB),
                GL_UNSIGNED_BYTE,
                cropped->data()
            );

            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            Characters[Id] = c;
        }
    }

    
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
                { xpos,     ypos,       1.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       0.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f }           
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
    void run()
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
        RenderText("123456789 Test test", 100, 100, glm::vec3(1, 0, 1));

        glEnable(GL_DEPTH_TEST); 
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    }

    void setup()
    {
        glkit::core::shaders::ShaderSourceList_s SSL;
        SSL.VertexShaderPath = "./assets/shaders/v_text.glsl";
        SSL.FragmentShaderPath = "./assets/shaders/f_text.glsl";

        ShaderProgram = std::make_unique<glkit::core::shaders::ShaderProgram_c>(SSL);

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

    TextPipeline_c()
    {}
};

} // namespace trailblazer::pipelines