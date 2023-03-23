#include <glkit/drawables/glkdrawable.hpp>


namespace glkit::drawables
{


/////////////////////////////////////////////////////////////////////////////////////////
// GLKDrawable_i implementation

void GLKDrawable_i::draw() const
{
    VertexArrayObject->bind();
    glDrawElements(GL_TRIANGLES, NumberOfElements,
                    GL_UNSIGNED_INT, 0);
    VertexArrayObject->unbind();
}

void GLKDrawable_i::initialize(const vertex_vector_t& vertices,
    const element_vector_t& indices) 
{
    NumberOfElements = indices.size();
    VertexArrayObject = std::make_unique<core::buffers::StaticVertexArrayObject_c<float>>();
    VertexArrayObject->copyVertexData(vertices, indices);
    VertexArrayObject->setVertexAttribute(0, 4);     
}

} // namespace glkit::drawables
