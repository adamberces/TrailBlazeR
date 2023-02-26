#include <glkit/mesh/glkcube.hpp>


namespace glkit::mesh
{

std::pair<GLKMesh_i::vertex_vector_t, GLKMesh_i::element_vector_t>
GLKCube_c::constructCubeVertexData
    (float width_ratio,
     float height_ratio,
     float depth_ratio)
{
    width_ratio  = std::min(width_ratio,  1.F);
    height_ratio = std::min(height_ratio, 1.F);
    depth_ratio  = std::min(depth_ratio,  1.F);

    width_ratio  /= 2.F;
    height_ratio /= 2.F;
    depth_ratio  /= 2.F;

    vertex_vector_t v =
    {
        // TOP PLANE
        -width_ratio, -height_ratio,  depth_ratio, // 0
        -width_ratio,  height_ratio,  depth_ratio, // 1
         width_ratio,  height_ratio,  depth_ratio, // 2
         width_ratio, -height_ratio,  depth_ratio, // 3

        // BOTTOM PLANE
        -width_ratio, -height_ratio, -depth_ratio, // 4
        -width_ratio,  height_ratio, -depth_ratio, // 5
         width_ratio,  height_ratio, -depth_ratio, // 6
         width_ratio, -height_ratio, -depth_ratio  // 7
    };

    element_vector_t e =
    {
        // TOP PLANE
        0, 1, 2,
        0, 2, 3,

        // BOTTOM PLANE
        4, 5, 6,
        4, 6, 7,

        // LEFT PLANE
        4, 0, 1,
        4, 1, 5,

        // RIGHT PLANE
        7, 3, 2,
        7, 2, 6,

        // FRONT PLANE
        4, 0, 3,
        4, 3, 7,

        // BACK PLANE
        5, 1, 2,
        5, 2, 6
    };

    return std::make_pair(v, e);
}

GLKCube_c::GLKCube_c(float width_ratio,
    float height_ratio,
    float depth_ratio)
{
    auto data = constructCubeVertexData
        (width_ratio, height_ratio, depth_ratio);
        
    initialize(data.first, data.second);
}

} // namespace glkit::mesh