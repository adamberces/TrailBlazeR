#include <SOIL/SOIL.h>
#include <glkit/window/background.hpp>

#include <iostream>
namespace glkit::window
{

void GLKBackgound_c::activateTexture() const
{
    glBindTexture(GL_TEXTURE_2D, TextureID);
}

void GLKBackgound_c::draw() const
{
    VertexArrayObject->bind();
    glDrawElements(GL_TRIANGLES, NumberOfElements,
                    GL_UNSIGNED_INT, 0);
    VertexArrayObject->unbind();
}

std::pair<mesh::GLKMesh_i::vertex_vector_t, mesh::GLKMesh_i::element_vector_t>
GLKBackgound_c::constructVertexData()
{
    vertex_vector_t v =
    {
        // Position          // Texture coordinates
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
         1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,  0.0f, 1.0f
    };

    element_vector_t e =
    {
        0, 1, 2,
        2, 3, 0
    };

    return std::make_pair(v, e);
}


void GLKBackgound_c::initialize(const vertex_vector_t& vertices,
    const element_vector_t& indices) 
{
    NumberOfElements = indices.size();
    VertexArrayObject = std::make_unique<core::buffers::VertexArrayObject_c<float>>();

    VertexArrayObject->copyVertexData(vertices, indices);
    VertexArrayObject->setVertexAttribute(0, 3, 5);  
    VertexArrayObject->setVertexAttribute(1, 2, 5, 3);      

    glGenTextures(1, &TextureID);
    int width, height;
    unsigned char* image = SOIL_load_image(FileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLKBackgound_c::GLKBackgound_c(std::string fileName) :
    FileName(fileName)
{
    auto data = constructVertexData();
    initialize(data.first, data.second);
}

} // namespace glkit::window
