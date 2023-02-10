#pragma once

#include "ogl.hpp"
#include "shader.hpp"

#include <string>
#include <vector>
#include <memory>


struct ShaderSourceList_s
{
    std::string VertexShaderPath;
    std::string TesselationControlShaderPath;
    std::string TesselationEvaluationShaderPath;
    std::string GeometryShaderPath;
    std::string FragmentShaderPath;
};

class ShaderProgram_c : public GLWrapper_i
{
    std::vector<std::shared_ptr<Shader_c>>
        compileShaderProgram(ShaderSourceList_s&) const;

    void linkShaderProgram
        (std::vector<std::shared_ptr<Shader_c>>&);

public:
    void use() const;

    explicit ShaderProgram_c(ShaderSourceList_s&);

    ~ShaderProgram_c();
};