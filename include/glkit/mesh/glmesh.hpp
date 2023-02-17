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
    void draw();

protected:
    using vertex_vector_t = std::vector<float>;
    using element_vector_t = std::vector<unsigned int>;

    void constructVertexArrayObject
        (const vertex_vector_t&, const element_vector_t&);

    void constructShaderProgram(const core::ShaderSourceList_s&);
  
    void initialize(const core::ShaderSourceList_s&,
        const vertex_vector_t&,
        const element_vector_t&);

    GLMesh_i() : NumberOfElements(0)
    {
    }
};

} // namespace glkit::mesh