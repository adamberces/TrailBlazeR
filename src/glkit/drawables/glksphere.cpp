#include <cmath>
#include <iostream>
#include <glkit/drawables/glksphere.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
// GLKSphere_c implementation

static constexpr float Pi = 3.141592653589;

std::pair<GLKDrawable_i::vertex_vector_t, GLKDrawable_i::element_vector_t>
GLKSphere_c::constructSphereVertexData(unsigned int u_max, unsigned int v_max)
{
    vertex_vector_t v;
    element_vector_t e;

    float colored = 1.F;

    unsigned int ix = 0;
    float step_u = (Pi * 2) / u_max;
    float step_v = Pi / v_max;

    for (unsigned int i = 0; i < u_max; i++)
    {
        for (unsigned int j = 0; j < v_max; j++)
        {
            float u1 = i * step_u;
            float v1 = j * step_v;
            float u2 = (i + 1) * step_u;
            float v2 = (j + 1) * step_v;
    
            float x0 = ::cos(u1) * ::sin(v1);
            float y0 = ::sin(u1) * ::sin(v1);
            float z0 = ::cos(v1);

            float x1 = ::cos(u1) * ::sin(v2);
            float y1 = ::sin(u1) * ::sin(v2);
            float z1 = ::cos(v2);

            float x2 = ::cos(u2) * ::sin(v2);
            float y2 = ::sin(u2) * ::sin(v2);
            float z2 = ::cos(v2);

            float x3 = ::cos(u2) * ::sin(v1);
            float y3 = ::sin(u2) * ::sin(v1);
            float z3 = ::cos(v1);

            v.insert(v.end(),
            {
                x0, y0, z0, colored,
                x1, y1, z1, colored,
                x2, y2, z2, colored,
                x3, y3, z3, colored
            });

            e.insert(e.end(),
            {
                ix, ix + 1, ix + 3,    // triangle 1
                ix + 1, ix + 2, ix + 3 // triangle 2
            });

            ix += 4;
            colored *= -1.F;
        }
        colored *= -1.F;
    }

    return std::make_pair(v, e);
}

GLKSphere_c::GLKSphere_c(unsigned int u, unsigned int v)
{
    auto data = constructSphereVertexData(u, v);
        
    initialize(data.first, data.second);
}

} // namespace glkit::drawables