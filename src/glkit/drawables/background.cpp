#include <stdexcept>
#include <glkit/drawables/background.hpp>
#include <png/pngimage.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
// GLKBackground_c implementation

void GLKBackground_c::activateTexture() const
{
    glBindTexture(GL_TEXTURE_2D, TextureID);
}

void GLKBackground_c::draw() const
{
    glDisable(GL_DEPTH_TEST);
    VertexArrayObject->bind();
    glDrawElements(GL_TRIANGLES, NumberOfElements,
                    GL_UNSIGNED_INT, 0);
    VertexArrayObject->unbind();
    glEnable(GL_DEPTH_TEST); 
}

std::pair<drawables::GLKDrawable_i::vertex_vector_t, drawables::GLKDrawable_i::element_vector_t>
GLKBackground_c::constructVertexData()
{
    vertex_vector_t v =
    {
        // Position          // Texture coordinates
        -1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,  1.0f, 1.0f
    };

    element_vector_t e =
    {
        0, 1, 2,
        2, 3, 0
    };

    return std::make_pair(v, e);
}

void GLKBackground_c::initialize(const vertex_vector_t& vertices,
    const element_vector_t& indices) 
{
    NumberOfElements = indices.size();
    VertexArrayObject = std::make_unique<core::buffers::StaticVertexArrayObject_c<float>>();

    VertexArrayObject->copyVertexData(vertices, indices);
    VertexArrayObject->setVertexAttribute(0, 3, 5);  
    VertexArrayObject->setVertexAttribute(1, 2, 5, 3);      

    png::PngImage_c im(FileName);

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    glTexImage2D(GL_TEXTURE_2D, 0,
                (im.hasAlpha() ? GL_RGBA : GL_RGB),
                im.width(), im.height(), 0,
                (im.hasAlpha() ? GL_RGBA : GL_RGB),
                GL_UNSIGNED_BYTE, im.data());

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLKBackground_c::GLKBackground_c(std::string fileName) :
    FileName(fileName)
{
    auto data = constructVertexData();
    initialize(data.first, data.second);
}

} // namespace glkit::drawables
