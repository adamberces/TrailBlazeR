#pragma once

#include <memory>
#include <vector>

#include <glkit/core/buffers/vertexarray.hpp>


namespace glkit::mesh
{

class GLKMesh_i
{
    std::unique_ptr<core::buffers::VertexArrayObject_c<float>> VertexArrayObject;

    unsigned int NumberOfElements;

public:
    void draw() const;

protected:
    using vertex_vector_t = std::vector<float>;
    using element_vector_t = std::vector<unsigned int>;

    void initialize(const vertex_vector_t&,
        const element_vector_t&);

    GLKMesh_i() : NumberOfElements(0)
    {
    }
};

} // namespace glkit::mesh
