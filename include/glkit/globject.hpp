#pragma once
#include <glkit/glad/glad.h>
#include <GLFW/glfw3.h>


class GLObject_i
{
protected:
    unsigned int Id;
    static const size_t INFOLOG_BUFSZ = 0x200;

    GLObject_i() : Id(0U)
    {}

public:
    decltype(Id) getId() const
    {
        return Id;
    }
};

