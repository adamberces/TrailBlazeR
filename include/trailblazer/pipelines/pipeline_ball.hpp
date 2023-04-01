#pragma once

#include <trailblazer/pipelines/renderpipeline.hpp>


namespace trailblazer::pipelines
{

class BallPipeline_c : public RenderPipeline_i
{
    inline void setupSSL() override
    {
        SSL.VertexShaderPath = Files_s::SHADER_PATH.data() + "v_perspective.glsl";
        SSL.GeometryShaderPath = Files_s::SHADER_PATH.data() + "g_normalcalculator.glsl";
        SSL.FragmentShaderPath = Files_s::SHADER_PATH.data() + "f_blinnphong.glsl";
    }

    inline void constructMesh() override
    {
        Mesh = std::make_unique<glkit::drawables::GLKSphere_c>(10, 10);
    }
};

} // namespace trailblazer::pipelines