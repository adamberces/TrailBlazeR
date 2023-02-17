#include <glkit/mesh/glmesh.hpp>


namespace glkit::mesh
{

void GLMesh_i::draw()
{
    ShaderProgram->use();
    VertexArrayObject->bind();

    glDrawElements(GL_TRIANGLES, NumberOfElements,
                    GL_UNSIGNED_INT, 0);

    VertexArrayObject->unbind();
}

void GLMesh_i::constructVertexArrayObject
    (const vertex_vector_t& vertices, const element_vector_t& indices)
{
    NumberOfElements = indices.size();
    VertexArrayObject = std::make_unique<core::VertexArrayObject_c<float>>();
    VertexArrayObject->copyVertexData(vertices, indices);
    VertexArrayObject->setVertexAttribute(0, 3);
}

void GLMesh_i::constructShaderProgram(const core::ShaderSourceList_s& ssl)
{
    ShaderProgram = std::make_unique<core::ShaderProgram_c>(ssl);
}

void GLMesh_i::initialize(const core::ShaderSourceList_s& shaderSourceList,
    const vertex_vector_t& vertices,
    const element_vector_t& indices) 
{
    constructShaderProgram(shaderSourceList);
    constructVertexArrayObject(vertices, indices);       
}

} // namespace glkit::mesh
