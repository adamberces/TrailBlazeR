#pragma once

#include <glkit/core/uniformfunctor.hpp>


namespace glkit::functors
{

auto UniformColor_f =
    [](core::uniforms::uniform_args_ptr_t ptr) -> core::uniforms::uniform_types_t
{
    //ProjectionConfig_s* cfg = dynamic_cast<ProjectionConfig_s*>(ptr);

    glm::vec4 color(1.F, 0.F, 0.F, 1.F);
        
    return { color };
};

} // namespace glkit::functors