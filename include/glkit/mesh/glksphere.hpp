#pragma once

#include <utility>
#include <glkit/mesh/glkmesh.hpp>


namespace glkit::mesh
{

/////////////////////////////////////////////////////////////////////////////////////////////////
// Represents a sphere mesh. The number of stacks/segments (U/V) are specified in the constructor

class GLKSphere_c : public GLKMesh_i
{
    std::pair<GLKMesh_i::vertex_vector_t, GLKMesh_i::element_vector_t>
    constructSphereVertexData(unsigned int u, unsigned int v);

public:
    GLKSphere_c(unsigned int u, unsigned int v);
};

} // namespace glkit::mesh
