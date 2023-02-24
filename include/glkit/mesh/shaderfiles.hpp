#pragma once
#include <glkit/core/shaderprogram.hpp>


namespace glkit::mesh::shader_config
{

static const core::ShaderSourceList_s CubeShaderSources = 
{
    .VertexShaderPath = "./assets/shaders/v_perspective.glsl",
    .FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl"
};

static const core::ShaderSourceList_s SphereShaderSources = 
{
    .VertexShaderPath = "./assets/shaders/v_perspective.glsl",
    .FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl"
};

} // namespace glkit::mesh::shader_config