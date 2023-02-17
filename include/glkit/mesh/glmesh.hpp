#pragma once

#include <memory>
#include <vector>

#include <glkit/core/shaderprogram.hpp>
#include <glkit/core/vertexarray.hpp>

namespace glkit::mesh
{

class GLMesh_i
{
    std::unique_ptr<core::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<core::VertexArrayObject_c<float>> VertexArrayObject;

    unsigned int NumberOfElements;

public:
    void draw()
    {
        ShaderProgram->use();
        VertexArrayObject->bind();

        glDrawElements(GL_TRIANGLES, NumberOfElements,
                       GL_UNSIGNED_INT, 0);

        VertexArrayObject->unbind();
    }

protected:
    using vertex_vector_t = std::vector<float>;
    using element_vector_t = std::vector<unsigned int>;

    void constructVertexArrayObject
        (const vertex_vector_t& vertices, const element_vector_t& indices)
    {
        VertexArrayObject = std::make_unique<core::VertexArrayObject_c<float>>();
        VertexArrayObject->copyVertexData(vertices, indices);
        VertexArrayObject->setVertexAttribute(0, 3);
    }

    void constructShaderProgram(const core::ShaderSourceList_s& ssl)
    {
        ShaderProgram = std::make_unique<core::ShaderProgram_c>(ssl);
    }

    void initialize(const core::ShaderSourceList_s& shaderSourceList,
        const vertex_vector_t& vertices,
        const element_vector_t& indices) 
    {
        constructShaderProgram(shaderSourceList);
        constructVertexArrayObject(vertices, indices);       
    }

    GLMesh_i() : NumberOfElements(0)
    {
    }
};

} // namespace glkit::mesh