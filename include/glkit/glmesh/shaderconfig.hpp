#pragma once
#include <glkit/core/shaderprogram.hpp>


namespace shader_config
{

static const ShaderSourceList_s CubeShaderSources = 
{
    .VertexShaderPath = "./assets/shaders/v_simple.glsl",
    .FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl"
};

static const ShaderSourceList_s SphereShaderSources = 
{
    .VertexShaderPath = "./assets/shaders/v_simple.glsl",
    .FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl"
};

} // namespace shader_config