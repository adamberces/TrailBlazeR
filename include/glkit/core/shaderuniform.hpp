#pragma once

#include <string>
#include "shaderuniform.hpp"


namespace glkit::core
{

using uniform_types_t = std::variant<
    glm::vec3,
    glm::vec4,
    glm::mat4
>;


class ShaderUniform_c
{
    std::string UniformName;

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

    inline ShaderUniform_c(const std::string& uniformName) :
        UniformName(uniformName)
    {
    }
};

} // namespace glkit::core
