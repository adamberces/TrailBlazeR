#pragma once

using UID = unsigned int;

static constexpr size_t INFOLOG_BUFSZ = 0x200;

enum class ShaderType_e 
{
    VERTEX,
    FRAGMENT
};

template <ShaderType_e ShaderType>
class Shader_c
{
    UID Id;

    
    struct ShaderTypeTraits_s
    {

    }

public:
    Shader_c(const char* Source)
    {
        Id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
};