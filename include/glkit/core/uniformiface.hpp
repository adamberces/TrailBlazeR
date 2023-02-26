#pragma once

#include <memory>
#include <unordered_map>
#include "shaderuniform.hpp"


namespace glkit::core::uniforms
{

/////////////////////////////////////////////////////////////////////////////////////////
// This class maintains a list of ShaderUniform_c's and provides a convient interface
// to assign the uniform values for a given Shader Program

struct FunctorNameArgumentPair_s
{
    uniform_name_t& Name;
    uniform_args_ptr_t& ArgsPtr;
};

class ShaderUniformInterface_c
{
    GLuint ProgramId;
    std::unordered_map<uniform_name_t, std::unique_ptr<ShaderUniform_c>> UniformList;

    bool isUniformOnList(const uniform_name_t& name) const 
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

public:
    void update(const uniform_name_t& name, const uniform_args_ptr_t argsPtr) const
    {
        if (!(isUniformOnList(name)))
        {
            throw std::runtime_error("ShaderUniformInterface_c::update: "
                "Uniform name not found in UniformList:" + name);
        }

        auto& uniform = (*(UniformList.find(name))).second;
        printf("%s\n", name.c_str());
        uniform->setData(ProgramId, argsPtr);
    }

    void add(const uniform_name_t& name, const uniform_functor_t& func)
    {
        if (isUniformOnList(name))
        {
            throw std::runtime_error("ShaderUniformInterface_c::add: "
                "Uniform name already registered in UniformList:" + name);
        }

        UniformList[name] = std::make_unique<ShaderUniform_c>(name, func);
    }

    ShaderUniformInterface_c(GLuint programId) :
        ProgramId(programId)
    {
    }
};


} // namespace glkit::core
