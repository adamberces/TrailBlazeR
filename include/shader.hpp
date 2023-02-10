#pragma once

#include "ogl.hpp"
#include <string>


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
// Abstract class representing a shader code, responsible for calling shader compilation 

class Shader_i : public GLWrapper_i
{
protected:
    ShaderFile_c SourceFile;

    virtual void createShaderObject() = 0;
    
public:
    void compile();

    explicit Shader_i(std::string fileName);
};

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a Vertex shader code

class VertexShader_c : public Shader_i
{
    void createShaderObject() override; 
     
public:
    using Shader_i::Shader_i;
};

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a Tesselation Control Shader shader code

class TesselationControlShader_c : public Shader_i
{
    void createShaderObject() override;
     
public:
    using Shader_i::Shader_i;
};

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a Tesselation Evaluation Shader shader code

class TesselationEvaluationShader_c : public Shader_i
{
    void createShaderObject() override;
     
public:
    using Shader_i::Shader_i;
};

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a Geometry shader code

class GeometryShader_c : public Shader_i
{
    void createShaderObject() override;
     
public:
    using Shader_i::Shader_i;
};

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a Fragment shader code

class FragmentShader_c : public Shader_i
{
    void createShaderObject() override;

public:
    using Shader_i::Shader_i;
};
