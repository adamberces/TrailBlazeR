#pragma once

#include <vector>
#include <functional>

#include "globject.hpp"


namespace glkit::core
{

struct UniformFunctorArgs_i
{
    virtual ~UniformFunctorArgs_i() {};
}


using uniform_functor_t =
    std::function<uniform_types_t(UniformFunctorArgs_i*)>;

using shader_uniform_list_t = std::vector<ShaderUniform_c>;
using uniform_functor_list_t = std::vector<ShaderUniform_c>;

class ShaderUniformInterface_c
{
    GLuint ProgramId;
    shader_uniform_list_t UniformList;

public:
    inline void setData(GLuint shaderProgramId, uniform_types_t& value) const 
    {
        GLint location = glGetUniformLocation(shaderProgramId, UniformName.c_str());

        if (std::holds_alternative<glm::vec3>(value))
        {
            glUniform3fv(location, 1, &value[0]);
        }
        else if (std::holds_alternative<glm::vec4>(value))
        {
            glUniform4fv(location, 1, &value[0]);
        }
        else if (std::holds_alternative<glm::mat4>(value))
        {
            glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
        }
        else
        {
            throw std::runtime_error("Unset/Unknown type error in ShaderUniform_c")
        }
    }

    inline ShaderUniform_c(const std::vector<std::string>& uniformName) :
        UniformName(uniformName)
    {
    }
};

using shader_uniform_list_t = std::vector<ShaderUniform_c>;

} // namespace glkit::core
