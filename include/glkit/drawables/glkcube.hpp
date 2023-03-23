#pragma once

#include <utility>
#include <glkit/drawables/glkdrawable.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a cube mesh. The ratio of the sides can be specified in the constructor
class GLKCube_c : public GLKDrawable_i
{
    std::pair<GLKDrawable_i::vertex_vector_t, GLKDrawable_i::element_vector_t>
    constructCubeVertexData
        (float width_ratio,
         float height_ratio,
         float depth_ratio);

public:
    GLKCube_c(float width_ratio,
        float height_ratio,
        float depth_ratio);
};

} // namespace glkit::drawables
