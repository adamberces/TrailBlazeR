#pragma once
#include <glkit/core/shaderprogram.hpp>


namespace trailblazer::gfx
{

static const glkit::core::shaders::ShaderSourceList_s CubeShaderSources = 
{
    .VertexShaderPath = "./assets/shaders/v_perspective.glsl",
    .FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl"
};

static const glkit::core::shaders::ShaderSourceList_s SphereShaderSources = 
{
    .VertexShaderPath = "./assets/shaders/v_perspective.glsl",
    .FragmentShaderPath = "./assets/shaders/f_uniformcolor.glsl"
};

} // namespace trailblazer::gfx