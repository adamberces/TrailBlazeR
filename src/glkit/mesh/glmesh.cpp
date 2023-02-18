#include <glkit/mesh/glmesh.hpp>
#include <iostream>

namespace glkit::mesh
{

void GLMesh_i::draw()
{
    ShaderProgram->use();
    VertexArrayObject->bind();

    glm::mat4 model = glm::mat4(1.0f);
    static float angle = 0;
    angle++;
    std::cout << angle << std::endl;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    ShaderProgram->setMat4Data("model", model);

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
    ShaderProgram->use();

    glm::mat4 view          = glm::mat4(1.0f); 
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    ShaderProgram->setMat4Data("projection", projection); 
    ShaderProgram->setMat4Data("view", view);
}

void GLMesh_i::initialize(const core::ShaderSourceList_s& shaderSourceList,
    const vertex_vector_t& vertices,
    const element_vector_t& indices) 
{
    constructShaderProgram(shaderSourceList);
    constructVertexArrayObject(vertices, indices);       
}

} // namespace glkit::mesh
