#include <iostream>
#include <glkit/core/shaderprogram.hpp>


/////////////////////////////////////////////////////////////////////////////////////////
// This funny little facilty lets us "iterate" tru the ShaderSourceList struct
// and assign a corresponding value from the ShaderType enum for correct compilation

using ShaderSourcePtr_t = std::string ShaderSourceList_s::*;

ShaderSourcePtr_t ShaderSourceListMember[] =
{
    &ShaderSourceList_s::VertexShaderPath,
    &ShaderSourceList_s::TesselationControlShaderPath,
    &ShaderSourceList_s::TesselationEvaluationShaderPath,
    &ShaderSourceList_s::GeometryShaderPath,
    &ShaderSourceList_s::FragmentShaderPath,
};

ShaderType_e ShaderSourceListType[] = 
{
    ShaderType_e::VertexShader,
    ShaderType_e::TesselationControlShader,
    ShaderType_e::TesselationEvaluationShader,
    ShaderType_e::GeometryShader,
    ShaderType_e::FragmentShader
};


/////////////////////////////////////////////////////////////////////////////////////////
// ShaderProgram_c implementation

std::vector<std::shared_ptr<Shader_c>>
    ShaderProgram_c::compileShaderProgram(const ShaderSourceList_s& ssl) const
{
    std::vector<std::shared_ptr<Shader_c>> shaders;
    size_t listsize = std::size(ShaderSourceListMember);

    for (size_t i = 0; i < listsize; i++)
    {
        std::string sourceFileName = ssl.*ShaderSourceListMember[i];
        if (!sourceFileName.empty())
        {
            auto s = std::make_shared<Shader_c>(sourceFileName);
            s->compile(ShaderSourceListType[i]);
            shaders.push_back(s);
        }
        else
        {
            if (i == 0 || i == listsize - 1)
            {
                throw std::runtime_error("Defining Vertex and Fragment shader"
                    "for a shader program is mandatory!");
            }
        }
    }

    return shaders;
}

void ShaderProgram_c::linkShaderProgram
    (const std::vector<std::shared_ptr<Shader_c>>& program)
{
    Id = glCreateProgram();

    for (const auto& p : program)
    {
        glAttachShader(Id, p->getId());
    }

    glLinkProgram(Id);

    // check for linking errors
    int success;
    char infoLog[INFOLOG_BUFSZ];
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(Id, INFOLOG_BUFSZ, NULL, infoLog);
        std::cout << "Shader program linking failed: ";
        std::cout << std::endl << infoLog << std::endl;
        throw std::runtime_error("Shader linking failed!");
    }
}

void ShaderProgram_c::use() const
{
    glUseProgram(Id);
}

ShaderProgram_c::ShaderProgram_c(const ShaderSourceList_s& ssl)
{
    auto program = compileShaderProgram(ssl);
    linkShaderProgram(program);
}

ShaderProgram_c::~ShaderProgram_c()
{
    glDeleteProgram(Id);
}