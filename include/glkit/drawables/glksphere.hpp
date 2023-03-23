#pragma once

#include <utility>
#include <glkit/drawables/glkdrawable.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////////////
// Represents a sphere mesh. The number of stacks/segments (U/V) are specified in the constructor

class GLKSphere_c : public GLKDrawable_i
{
    std::pair<GLKDrawable_i::vertex_vector_t, GLKDrawable_i::element_vector_t>
    constructSphereVertexData(unsigned int u, unsigned int v);

public:
    GLKSphere_c(unsigned int u, unsigned int v);
};

} // namespace glkit::drawables
