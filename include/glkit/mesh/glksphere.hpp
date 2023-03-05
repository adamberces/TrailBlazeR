#pragma once

#include <utility>
#include <glkit/mesh/glkmesh.hpp>


namespace glkit::mesh
{

class GLKSphere_c : public GLKMesh_i
{
    std::pair<GLKMesh_i::vertex_vector_t, GLKMesh_i::element_vector_t>
    constructSphereVertexData(unsigned int u, unsigned int v);

public:
    GLKSphere_c(unsigned int u, unsigned int v);
};

} // namespace glkit::mesh
