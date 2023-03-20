#pragma once

#include <utility>
#include <glkit/mesh/glkmesh.hpp>


namespace glkit::mesh
{

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a cube mesh. The ratio of the sides can be specified in the constructor
class GLKCube_c : public GLKMesh_i
{
    std::pair<GLKMesh_i::vertex_vector_t, GLKMesh_i::element_vector_t>
    constructCubeVertexData
        (float width_ratio,
         float height_ratio,
         float depth_ratio);

public:
    GLKCube_c(float width_ratio,
        float height_ratio,
        float depth_ratio);
};

} // namespace glkit::mesh
