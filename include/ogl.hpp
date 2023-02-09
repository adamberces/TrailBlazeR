#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class GLWrapper_i
{
protected:
    unsigned int Id;
    static const size_t INFOLOG_BUFSZ = 0x200;

    GLWrapper_i() : Id(0U)
    {}
};

