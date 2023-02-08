#pragma once
#include "ogl.hpp"

class ShaderProgram_c : public GLWrapper_i
{
public:
    explicit ShaderProgram_c(const char** shaderSourceList);
};