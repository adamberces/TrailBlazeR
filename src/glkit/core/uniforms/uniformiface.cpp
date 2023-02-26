#include <glkit/core/uniforms/uniformiface.hpp>


namespace glkit::core::uniforms
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for ShaderUniformInterface_c

bool ShaderUniformInterface_c::isUniformOnList(const uniform_name_t& name) const 
{
    auto it = UniformList.find(name);
    if (it == UniformList.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ShaderUniformInterface_c::update(const uniform_name_t& name, const uniform_args_ptr_t argsPtr) const
{
    if (!(isUniformOnList(name)))
    {
        throw std::runtime_error("ShaderUniformInterface_c::update: "
            "Uniform name not found in UniformList:" + name);
    }

    auto& uniform = (*(UniformList.find(name))).second;
    uniform->setData(ProgramId, argsPtr);
}

void ShaderUniformInterface_c::add(const uniform_name_t& name, const uniform_functor_t& func)
{
    if (isUniformOnList(name))
    {
        throw std::runtime_error("ShaderUniformInterface_c::add: "
            "Uniform name already registered in UniformList:" + name);
    }

    UniformList[name] = std::make_unique<ShaderUniform_c>(name, func);
}

ShaderUniformInterface_c::ShaderUniformInterface_c(GLuint programId) :
    ProgramId(programId)
{
}

} // namespace glkit::core::uniforms
