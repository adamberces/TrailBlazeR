#pragma once

#include <glkit/core/ogl_headers.hpp>


namespace glkit::core
{

/////////////////////////////////////////////////////////////////////////////////////////
// Common ancestor for all objects wrapping OpenGL features, providing the unique ID

class GLObject_i
{
protected:
    GLuint Id;
    static const size_t INFOLOG_BUFSZ = 0x200;

    inline GLObject_i() : Id(0U)
    {}

public:
    inline decltype(Id) getId() const
    {
        return Id;
    }
};

} // namespace glkit::core
