#include <memory>
#include <vector>

#include "shader.hpp"
#include "shaderprogram.hpp"


#include <iostream>


/////////////////////////////////////////////////////////////////////////////////////////
// This funny little facilty lets us "iterate" tru the ShaderSourceList struct
// with a for loop and a homebrew "traits" struct (thru template specializations)
// which provides type information of the corresponding shader code class to construct,
// in the order of the OpenGL pipeline

using ShaderSourcePtr_t = std::string ShaderSourceList_s::*;

ShaderSourcePtr_t ShaderSourceListMember[] = {
    &ShaderSourceList_s::VertexShader,
    &ShaderSourceList_s::TesselationControlShader,
    &ShaderSourceList_s::TesselationEvaluationShader,
    &ShaderSourceList_s::GeometryShader,
    &ShaderSourceList_s::FragmentShader,
};


template<size_t Index>
struct ShaderSourceListTrait
{
};

template<>
struct ShaderSourceListTrait<0>
{
    using type = VertexShader_c;
};

template<>
struct ShaderSourceListTrait<1>
{
    using type = TesselationControlShader_c;
};

template<>
struct ShaderSourceListTrait<2>
{
    using type = TesselationEvaluationShader_c;
};

template<>
struct ShaderSourceListTrait<3>
{
    using type = GeometryShader_c;
};

template<>
struct ShaderSourceListTrait<4>
{
    using type = FragmentShader_c;
};

template struct ShaderSourceListTrait<0>;

ShaderProgram_c::ShaderProgram_c(ShaderSourceList_s& ssl)
{
    std::vector<std::unique_ptr<Shader_i>> shaders;
    
    auto l = [&](const size_t index) -> std::unique_ptr<Shader_i>
    {
        std::string sourceFileName = ssl.*ShaderSourceListMember[index];
        auto s = std::make_unique<ShaderSourceListTrait<index>::type>(sourceFileName);
    };

    for (size_t i = 0; i < 5; i++)
    {
        shaders.push_back(l(i));
    }

}