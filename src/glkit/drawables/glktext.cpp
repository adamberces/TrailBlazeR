#include <glkit/drawables/glktext.hpp>
#include <glkit/core/buffers/dynamicvertexarray.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for GLKText_c

void GLKText_c::drawCharacter(const Character_s& ch, float x, float y) const
{
    float xpos = x + ch.XOffset;
    float ypos = y - (ch.Height - ch.YOffset);
    float w = ch.Width;
    float h = ch.Height;

    // update VBO for each character
    std::vector<float> vertices =
    {
        xpos,     ypos + h,   0.0f, 0.0f,            
        xpos,     ypos,       0.0f, 1.0f,
        xpos + w, ypos,       1.0f, 1.0f,
        
        xpos,     ypos + h,   0.0f, 0.0f,
        xpos + w, ypos,       1.0f, 1.0f,
        xpos + w, ypos + h,   1.0f, 0.0f           
    };

    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.TextureId);
    VertexArrayObject->copyVertexData(vertices, {});
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GLKText_c::drawText(std::string text, int x, int y) const
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    glActiveTexture(GL_TEXTURE0);
    VertexArrayObject->bind();

    for(char c : text)
    {
        const Character_s& ch = Font.characters().at(static_cast<std::size_t>(c));
        drawCharacter(ch, x, y);

        // Shift x coordinate to the starting point of the next character
        x += ch.XAdvance;
    }

    VertexArrayObject->unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_DEPTH_TEST); 
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
}

GLKText_c::GLKText_c(std::string fontFileName) :
    Font(fontFileName)
{
    VertexArrayObject = std::make_unique<core::buffers::DynamicVertexArrayObject_c<float>>();

    // 6 vertices for the two triangles of a 2D quad, 2 screen and 2 texture coordinates for each 
    core::buffers::DynamicVertexArrayObject_c<float>* VAO =
            dynamic_cast<core::buffers::DynamicVertexArrayObject_c<float>*>(VertexArrayObject.get());
    VAO->allocateVertexBuffer(6 * 2 * 2);
    VAO->setVertexAttribute(0, 4);
}

} // namespace trailblazer::hud