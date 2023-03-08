#pragma once

#include <game/presentation/renderpipeline.hpp>


namespace trailblazer::presentation
{

class BallPipeline_c : public RenderPipeline_i
{
    void setupSSL() override
    {
        SSL.VertexShaderPath = "./assets/shaders/v_perspective.glsl";
        SSL.GeometryShaderPath = "./assets/shaders/g_normalcalculator.glsl";
        SSL.FragmentShaderPath = "./assets/shaders/f_blinnphong.glsl";
    }

    void constructMesh() override
    {
        Mesh = std::make_unique<glkit::mesh::GLKSphere_c>(10, 10);
    }
};

} // namespace trailblazer::presentation