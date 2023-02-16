#pragma once

#include "globject.hpp"
#include <string>


/////////////////////////////////////////////////////////////////////////////////////////
// Type safe wrapper of OpenGL shader types

enum class ShaderType_e
{
    VertexShader = GL_VERTEX_SHADER,
    TesselationControlShader = GL_TESS_CONTROL_SHADER,
    TesselationEvaluationShader = GL_TESS_EVALUATION_SHADER,
    GeometryShader = GL_GEOMETRY_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER
};


/////////////////////////////////////////////////////////////////////////////////////////
// Represents a shader source file, responsible for reading GLSL files and store contents
 
class ShaderFile_c
{
    std::string FileName;
    std::string Source;

public:
    std::string fileName() const;
    std::string source() const;

    explicit ShaderFile_c(const std::string& fileName);
};


/////////////////////////////////////////////////////////////////////////////////////////
// Class representing a shader code, responsible for shader compilation 
// Designed as per the RAII principles, glDeleteShader is automatically called to free
// resources when the object lifetime is over.

class Shader_c : public GLObject_i
{
    ShaderFile_c SourceFile;
    
public:
    void compile(ShaderType_e);

    explicit Shader_c(std::string fileName);

    ~Shader_c();
};
