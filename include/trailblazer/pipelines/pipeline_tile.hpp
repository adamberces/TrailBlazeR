#pragma once

#include <trailblazer/pipelines/renderpipeline.hpp>


namespace trailblazer::pipelines
{

class TilePipeline_c : public RenderPipeline_i
{
    inline void setupSSL() override
    {
        SSL.VertexShaderPath = std::string(Files_s::SHADER_PATH) + "v_perspective.glsl";
        SSL.GeometryShaderPath = std::string(Files_s::SHADER_PATH) + "g_normalcalculator.glsl";
        SSL.FragmentShaderPath = std::string(Files_s::SHADER_PATH) + "f_blinnphong.glsl";
    }

    inline void constructMesh() override
    {
        Mesh = std::make_unique<glkit::drawables::GLKCube_c>(1, 1, Constants_s::TILE_HEIGHT);
    }
};

} // namespace trailblazer::pipelines