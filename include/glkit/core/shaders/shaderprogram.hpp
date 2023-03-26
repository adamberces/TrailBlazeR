#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glkit/core/globject.hpp>
#include <glkit/core/shaders/shader.hpp>


namespace glkit::core::shaders
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Struct to specify paths of GLSL source files to be compiled and linked to
/// an OpenGL Shader program. Note, that defining VertexShaderPath and FragmentShaderPath
/// is mandatory, the rest can be left empty optionally.

struct ShaderSourceList_s
{
    std::string VertexShaderPath;
    std::string TesselationControlShaderPath;
    std::string TesselationEvaluationShaderPath;
    std::string GeometryShaderPath;
    std::string FragmentShaderPath;
};


/////////////////////////////////////////////////////////////////////////////////////////
/// Class representing a shader program, responsible for calling the compilation of
/// individual shader sources (wrapped in Shader_c instances) and linking them together.
/// Designed as per the RAII principles, glDeleteProgram is automatically called to free
/// resources when the object lifetime is over.

class ShaderProgram_c : public GLObject_i
{
    std::vector<std::shared_ptr<Shader_c>>
        compileShaderProgram(const ShaderSourceList_s&) const;

    void linkShaderProgram
        (const std::vector<std::shared_ptr<Shader_c>>&);

public:
    void use() const;

    explicit ShaderProgram_c(const ShaderSourceList_s&);

    ~ShaderProgram_c();
};

} // namespace glkit::core::shaders