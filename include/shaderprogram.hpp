#pragma once
#include "ogl.hpp"
#include <string>

/*
static const char* test[] = {
    "f_uniformcolor.glsl", 
    "v_simple.glsl"
};*/

struct ShaderSourceList_s
{
    std::string VertexShader;
    std::string TesselationControlShader;
    std::string TesselationEvaluationShader;
    std::string GeometryShader;
    std::string FragmentShader;
};

class ShaderProgram_c : public GLWrapper_i
{
public:
    explicit ShaderProgram_c(ShaderSourceList_s&);
};