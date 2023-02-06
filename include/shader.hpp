#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <GLFW/glfw3.h>


using UID = unsigned int;

static constexpr size_t INFOLOG_BUFSZ = 0x200;

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a shader source
 
class Shader_c
{
protected:
    UID Id;

    virtual void createShaderObject(ShaderType_e) = 0

    void compileShader(std::string FileName, std::string Source)
    {
        createShaderObject();
        glShaderSource(Id, 1, &Source, NULL);
        glCompileShader(Id);

        // check for compile errors
        int success;
        char infoLog[INFOLOG_BUFSZ];
        glGetShaderiv(Id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(Id, INFOLOG_BUFSZ, NULL, infoLog);
            std::cout << "Shader file (" << FileName << ") compilation failed: ";
            std::cout << std::endl; << infoLog << std::endl;
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

class VertexShader_c : public Shader_c
{
public:
    using Shader_c::Shader_c;

private:
    void createShaderObject(ShaderType_e) override
    {
        Id = glCreateShader(GL_VERTEX_SHADER);
    }
};


class FragmentShader_c : public Shader_c
{
public:
    using Shader_c::Shader_c;

private:
    void createShaderObject(ShaderType_e) override
    {
        Id = glCreateShader(GL_FRAGMENT_SHADER);
    }
};