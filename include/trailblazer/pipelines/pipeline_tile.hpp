#pragma once

#include <trailblazer/pipelines/renderpipeline.hpp>


namespace trailblazer::pipelines
{

class TilePipeline_c : public RenderPipeline_i
{
    inline void setupSSL() override
    {
        SSL.VertexShaderPath = Files_s::SHADER_PATH.data() + "v_perspective.glsl";
        SSL.GeometryShaderPath = Files_s::SHADER_PATH.data() + "g_normalcalculator.glsl";
        SSL.FragmentShaderPath = Files_s::SHADER_PATH.data() + "f_blinnphong.glsl";
    }

    inline void constructMesh() override
    {
        Mesh = std::make_unique<glkit::drawables::GLKCube_c>(1, 1, .1);
    }
};

} // namespace trailblazer::pipelines