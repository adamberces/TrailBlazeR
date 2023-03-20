#include <glkit/mesh/glkmesh.hpp>


namespace glkit::mesh
{


/////////////////////////////////////////////////////////////////////////////////////////
// GLKMesh_i implementation

void GLKMesh_i::draw() const
{
    VertexArrayObject->bind();
    glDrawElements(GL_TRIANGLES, NumberOfElements,
                    GL_UNSIGNED_INT, 0);
    VertexArrayObject->unbind();
}

void GLKMesh_i::initialize(const vertex_vector_t& vertices,
    const element_vector_t& indices) 
{
    NumberOfElements = indices.size();
    VertexArrayObject = std::make_unique<core::buffers::VertexArrayObject_c<float>>();
    VertexArrayObject->copyVertexData(vertices, indices);
    VertexArrayObject->setVertexAttribute(0, 4);     
}

} // namespace glkit::mesh
