#include <glkit/mesh/glmesh.hpp>
#include <glkit/mesh/shaderuniforms.hpp>
#include <iostream>
#include <thread>

namespace glkit::mesh
{

void GLMesh_i::draw(const ShaderProgram& sp) const
{
    sp.use();
    VertexArrayObject->bind();

    glm::mat4 model = glm::mat4(1.0f);
    static float angle = 0;
    angle++;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    UNIFORMS.Model.setData(model);
    UNIFORMS.Color.setData(glm::vec4(1.F, 0.F, 0.F, 1.F));

    glDrawElements(GL_TRIANGLES, NumberOfElements,
                    GL_UNSIGNED_INT, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    VertexArrayObject->unbind();
}

void GLMesh_i::constructShaderProgram(const core::ShaderSourceList_s& ssl)
{
    ShaderProgram = std::make_unique<core::ShaderProgram_c>(ssl);
    ShaderProgram->use();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glm::mat4 view          = glm::mat4(1.0f); 
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f);
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    UNIFORMS.Projection.setData(projection);
    UNIFORMS.Camera.setData(view);
}

void GLMesh_i::initialize(const vertex_vector_t& vertices,
    const element_vector_t& indices) 
{
    NumberOfElements = indices.size();
    VertexArrayObject = std::make_unique<core::VertexArrayObject_c<float>>();
    VertexArrayObject->copyVertexData(vertices, indices);
    VertexArrayObject->setVertexAttribute(0, 3);    
}

} // namespace glkit::mesh
