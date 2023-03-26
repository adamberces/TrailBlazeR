#pragma once

#include <trailblazer/pipelines/renderpipeline.hpp>


namespace trailblazer::pipelines
{

class TilePipeline_c : public RenderPipeline_i
{
    inline void setupSSL() override
    {
        SSL.VertexShaderPath = "./assets/shaders/v_perspective.glsl";
        SSL.GeometryShaderPath = "./assets/shaders/g_normalcalculator.glsl";
        SSL.FragmentShaderPath = "./assets/shaders/f_blinnphong.glsl";
    }

    inline void constructMesh() override
    {
        Mesh = std::make_unique<glkit::drawables::GLKCube_c>(1, 1, .1);
    }
};

} // namespace trailblazer::pipelines