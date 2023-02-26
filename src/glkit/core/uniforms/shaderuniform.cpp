#include <glkit/core/uniforms/shaderuniform.hpp>


namespace glkit::core::uniforms
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for ShaderUniform_c

void ShaderUniform_c::setData(GLuint shaderProgramId, uniform_args_ptr_t uniformArguments) const 
{
    // Try to find the uniform's location in the given shader program
    const GLint location = glGetUniformLocation(shaderProgramId, UniformName.c_str());

    // Test if the uniform exists
    if (location == -1)
    {
        throw std::runtime_error("ShaderUniform_c::setData: Uniform name not found in program" +
            std::to_string(shaderProgramId));
    }

    // Call the uniform functor
    uniform_types_t value = UniformFunctor(uniformArguments);

    // Determine the return value type and call OpenGL API accordingly
    if (std::holds_alternative<glm::vec3>(value))
    {
        glm::vec3 v = std::get<glm::vec3>(value);
        glUniform3fv(location, 1, &v[0]);
    }
    else if (std::holds_alternative<glm::vec4>(value))
    {
        glm::vec4 v = std::get<glm::vec4>(value);
        glUniform4fv(location, 1, &v[0]);
    }
    else if (std::holds_alternative<glm::mat4>(value))
    {
        glm::mat4 v = std::get<glm::mat4>(value);
        glUniformMatrix4fv(location, 1, GL_FALSE, &v[0][0]);
    }
    else
    {
        throw std::runtime_error("ShaderUniform_c::setData: unset/unknown type error in ShaderUniform_c");
    }
}

ShaderUniform_c::ShaderUniform_c
    (const uniform_name_t& uniformName,
        const uniform_functor_t& uniformFunctor) :
    UniformName(uniformName),
    UniformFunctor(uniformFunctor)
{
}

} // namespace glkit::core::uniforms
