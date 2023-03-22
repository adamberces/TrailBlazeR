#pragma once

#include <memory>
#include <vector>

#include <glkit/core/buffers/vertexarray.hpp>


namespace glkit::mesh
{

/////////////////////////////////////////////////////////////////////////////////////////
// Interface class for drawing 3D objects using GLKit
// Maintains a VAO (with VBO and EBO) and provides a draw function
class GLKMesh_i
{
protected:
    unsigned int NumberOfElements;
    std::unique_ptr<core::buffers::StaticVertexArrayObject_c<float>> VertexArrayObject;

public:
    virtual void draw() const;

protected:
    using vertex_vector_t = std::vector<float>;
    using element_vector_t = std::vector<unsigned int>;

    virtual void initialize(const vertex_vector_t&,
        const element_vector_t&);

    GLKMesh_i() : NumberOfElements(0)
    {
    }
};

} // namespace glkit::mesh
