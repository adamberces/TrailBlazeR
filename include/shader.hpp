#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <GLFW/glfw3.h>


using UID = unsigned int;

static constexpr size_t INFOLOG_BUFSZ = 0x200;

/////////////////////////////////////////////////////////////////////////////////////////
// Type safe wrapper for OpenGL shader program type macros
 
enum class ShaderType_e 
{
    VERTEX,
    FRAGMENT
};

template<ShaderType_e ShaderType>
struct shadertype_trait;

template<>
struct shadertype_trait<ShaderType_e::VERTEX>
{
    static constexpr int GLShaderType = GL_VERTEX_SHADER;
};

template<>
struct shadertype_trait<ShaderType_e::FRAGMENT>
{
    static constexpr int GLShaderType = GL_FRAGMENT_SHADER;
};

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a shader source
 
class Shader_c
{
    UID Id;

    virtual void createShaderObject(ShaderType_e) = 0

    void compileShader(std::string FileName, std::string Source)
    {
        Id = glCreateShader(shadertype_trait<ShaderType>::GLShaderType);
        glShaderSource(Id, 1, &Source, NULL);
        glCompileShader(Id);

        // check for compile errors
        int success;
        char infoLog[INFOLOG_BUFSZ];
        glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(Id, INFOLOG_BUFSZ, NULL, infoLog);
            std::cout << "Shader compilation failed: " << infoLog << std::endl;
        }
    }

public:
    Shader_c(std::string FileName)
    {
        std::uintmax_t = std::filesystem::file_size(FileName)
        std::string buffer(size);
        std::ifstream file(FileName);

        if (file.read(buffer.data(), size))
        {
            compileShader(FileName, buffer);
        }
        else
        {
            std::cout << "Loading GLSL file failed: " << FileName << std::endl;
        }
        
    }
};