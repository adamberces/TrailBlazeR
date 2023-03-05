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
        RenderPipeline_i::CameraConfig.Position.X = 2;
        RenderPipeline_i::CameraConfig.Position.Y = -5;
        RenderPipeline_i::CameraConfig.Position.Z = 1.5;
        RenderPipeline_i::CameraConfig.Direction.X = 2;
        RenderPipeline_i::CameraConfig.Direction.Y = 5;
        RenderPipeline_i::CameraConfig.Direction.Z = .5;
        RenderPipeline_i::CameraPositionConfig.Position = RenderPipeline_i::CameraConfig.Position;

        RenderPipeline_i::ProjectionConfig.FOV = 45.F;
        RenderPipeline_i::ProjectionConfig.ScreenWidth = 640;
        RenderPipeline_i::ProjectionConfig.ScreenHeight = 480;
        RenderPipeline_i::ProjectionConfig.NearPlane = 0.1F;
        RenderPipeline_i::ProjectionConfig.FarPlane = 100.F;

        RenderPipeline_i::LightningColorConfig.Color.R = .5F;
        RenderPipeline_i::LightningColorConfig.Color.G = .5F;
        RenderPipeline_i::LightningColorConfig.Color.B = 1.F;
        RenderPipeline_i::LightningPositionConfig.Position.X = 2;
        RenderPipeline_i::LightningPositionConfig.Position.Y = 0.25F;
        RenderPipeline_i::LightningPositionConfig.Position.Z = 0.5F;


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
            RenderPipeline_i::LightningPositionConfig.Position.Z += .05;
        }
        else if (isPressed(GLFW_KEY_S))
        {
            RenderPipeline_i::LightningPositionConfig.Position.Z -= .05;
        }
        else if (isPressed(GLFW_KEY_A))
        {
            RenderPipeline_i::LightningPositionConfig.Position.Y -= .05;
        }
        else if (isPressed(GLFW_KEY_D))
        {
            RenderPipeline_i::LightningPositionConfig.Position.Y += .05;
        }
        else if (isPressed(GLFW_KEY_E))
        {
            RenderPipeline_i::LightningPositionConfig.Position.X -= .05;
        }
          else if (isPressed(GLFW_KEY_R))
        {
            RenderPipeline_i::LightningPositionConfig.Position.X += .05;
        }
        printf("%f %f %f\n", RenderPipeline_i::LightningPositionConfig.Position.X,
        RenderPipeline_i::LightningPositionConfig.Position.Y, RenderPipeline_i::LightningPositionConfig.Position.Z);
    }
};

} // namespace trailblazer::gfx