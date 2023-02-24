#pragma once

#include <utility>
#include "glmesh.hpp"
#include "shaderfiles.hpp"


namespace glkit::mesh
{

class GLCube_c : public GLMesh_i
{
    std::pair<GLMesh_i::vertex_vector_t, GLMesh_i::element_vector_t>
    constructCubeVertexData(
        float width_ratio,
        float height_ratio,
        float depth_ratio);

public:
    GLCube_c(float width_ratio,
        float height_ratio,
        float depth_ratio);
};

} // namespace glkit::mesh
