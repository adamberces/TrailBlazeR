#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

using Id_t = unsigned int;

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a shader source
 
class ShaderFile_c
{
    std::string FileName;
    std::string Source;

public:
    std::string fileName() const
    {
        return FileName;
    }

    std::string source() const
    {
        return Source;
    }

    explicit ShaderFile_c(std::string fileName) :
        FileName(fileName)
    {
        std::size_t size = std::filesystem::file_size(FileName);
        std::string buffer(size + 1U, '\0');
        std::ifstream file(FileName);

        if (!file.read(buffer.data(), size))
        {
            throw std::runtime_error("Loading GLSL file failed: " + FileName);
        }
        std::cout << buffer << std::endl;
    }
};

class Shader_c
{
    static constexpr size_t INFOLOG_BUFSZ = 0x200;

protected:
    Id_t Id;
    ShaderFile_c SourceFile;

    virtual void createShaderObject() = 0;
    
public:
    void compile()
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

    Shader_c(std::string fileName) :
        Id(0),
        SourceFile(ShaderFile_c(fileName))
    {  
    }
};

class VertexShader_c : public Shader_c
{
public:
    using Shader_c::Shader_c;

private:
    void createShaderObject() override
    {
        Id = glCreateShader(GL_VERTEX_SHADER);
    }
};


class FragmentShader_c : public Shader_c
{
public:
    using Shader_c::Shader_c;

private:
    void createShaderObject() override
    {
        Id = glCreateShader(GL_FRAGMENT_SHADER);
    }
};