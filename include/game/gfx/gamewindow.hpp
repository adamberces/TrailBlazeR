#pragma once

#include <glkit/window/glwindow.hpp>
#include <game/gfx/renderpipeline.hpp>
#include <game/map/map.hpp>

namespace trailblazer::gfx
{

class GameWindow_c : public glkit::window::GLWindow_i
{
public:
    using glkit::window::GLWindow_i::GLWindow_i;
    Map_c map;

protected:
    trailblazer::gfx::TilePipeline_c ppl;

    void initEvents() override
    {
        RenderPipeline_i::CameraConfig.Position.X = -3;
        RenderPipeline_i::CameraConfig.Position.Y = 0;
        RenderPipeline_i::CameraConfig.Position.Z = 0;
        RenderPipeline_i::CameraConfig.Direction.X = 1;
        RenderPipeline_i::CameraConfig.Direction.Y = 0;
        RenderPipeline_i::CameraConfig.Direction.Z = 0;
        RenderPipeline_i::CameraPositionConfig.Position.X = RenderPipeline_i::CameraConfig.Position.X;
        RenderPipeline_i::CameraPositionConfig.Position.Y = RenderPipeline_i::CameraConfig.Position.Y;
        RenderPipeline_i::CameraPositionConfig.Position.Z = RenderPipeline_i::CameraConfig.Position.Z;

        RenderPipeline_i::ProjectionConfig.FOV = 45.F;
        RenderPipeline_i::ProjectionConfig.ScreenWidth = 640;
        RenderPipeline_i::ProjectionConfig.ScreenHeight = 480;
        RenderPipeline_i::ProjectionConfig.NearPlane = 0.1F;
        RenderPipeline_i::ProjectionConfig.FarPlane = 100.F;

        /*RenderPipeline_i::LightningColorConfig.Color.R = 1.F;
        RenderPipeline_i::LightningColorConfig.Color.G = 1.F;
        RenderPipeline_i::LightningColorConfig.Color.B = 1.F;*/
        RenderPipeline_i::LightningPositionConfig.Position.X = 1;
        RenderPipeline_i::LightningPositionConfig.Position.Y = 1;
        RenderPipeline_i::LightningPositionConfig.Position.Z = 1;

        ppl.setup();
    }

    void drawEvents() override
    {
        map.draw();
    }

    void keypressEvents() override
    {
        if (isPressed(GLFW_KEY_W))
        {
            RenderPipeline_i::CameraConfig.Position.Z += .05;
        }
        else if (isPressed(GLFW_KEY_S))
        {
            RenderPipeline_i::CameraConfig.Position.Z -= .05;
        }
        else if (isPressed(GLFW_KEY_A))
        {
            RenderPipeline_i::CameraConfig.Position.Y -= .05;
        }
        else if (isPressed(GLFW_KEY_D))
        {
            RenderPipeline_i::CameraConfig.Position.Y += .05;
        }
    }
};

} // namespace trailblazer::gfx