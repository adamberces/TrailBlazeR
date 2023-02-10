#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>


/////////////////////////////////////////////////////////////////////////////////////////
// ShaderFile_c implementation

std::string ShaderFile_c::fileName() const
{
    return FileName;
}

std::string ShaderFile_c::source() const
{
    return Source;
}

ShaderFile_c::ShaderFile_c(const std::string& fileName) :
    FileName(fileName)
{
    std::size_t size = std::filesystem::file_size(FileName);
    Source = std::string(size + 1U, '\0');
    std::ifstream file(FileName);

    if (!file.read(Source.data(), size))
    {
        throw std::runtime_error("Loading GLSL file failed: " + FileName);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
// Shader_i implementation

void Shader_i::compile()
{
    std::string source = SourceFile.source();
    const char* sourcebuf = source.data();

    createShaderObject();
    glShaderSource(Id, 1, &sourcebuf, NULL);
    glCompileShader(Id);

    // check for compile errors
    int success;
    char infoLog[INFOLOG_BUFSZ];
    glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(Id, INFOLOG_BUFSZ, NULL, infoLog);
        std::cout << "Shader file (" << SourceFile.fileName() << ") compilation failed: ";
        std::cout << std::endl << infoLog << std::endl;
        throw std::runtime_error("Shader compilation failed!");
    }
}

Shader_i::Shader_i(std::string fileName) :
    SourceFile(ShaderFile_c(fileName))
{  
}


/////////////////////////////////////////////////////////////////////////////////////////
// VertexShader_c implementation

void VertexShader_c::createShaderObject()
{
    Id = glCreateShader(GL_VERTEX_SHADER);
}


/////////////////////////////////////////////////////////////////////////////////////////
// TesselationControlShader_c implementation

void TesselationControlShader_c::createShaderObject()
{
    Id = glCreateShader(GL_TESS_CONTROL_SHADER);
}


/////////////////////////////////////////////////////////////////////////////////////////
// TesselationEvaluationShader_c implementation

void TesselationEvaluationShader_c::createShaderObject()
{
    Id = glCreateShader(GL_TESS_EVALUATION_SHADER);
}


/////////////////////////////////////////////////////////////////////////////////////////
// GeometryShader_c implementation

void GeometryShader_c::createShaderObject()
{
    Id = glCreateShader(GL_GEOMETRY_SHADER);
}


/////////////////////////////////////////////////////////////////////////////////////////
// FragmentShader_c implementation

void FragmentShader_c::createShaderObject()
{
    Id = glCreateShader(GL_FRAGMENT_SHADER);
}
