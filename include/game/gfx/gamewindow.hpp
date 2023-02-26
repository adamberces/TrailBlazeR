#pragma once

#include <glkit/window/glwindow.hpp>
#include <game/gfx/renderpipeline.hpp>


namespace trailblazer::gfx
{

class GameWindow_c : public glkit::window::GLWindow_i
{
public:
    using glkit::window::GLWindow_i::GLWindow_i;

protected:
    trailblazer::gfx::TilePipeline_c ppl;

    void initEvents() override
    {
        ppl.config().CameraConfig.Position.X = -3;
        ppl.config().CameraConfig.Position.Y = 0;
        ppl.config().CameraConfig.Position.Z = 0;

        ppl.config().ProjectionConfig.FOV = 45.F;
        ppl.config().ProjectionConfig.ScreenWidth = 640;
        ppl.config().ProjectionConfig.ScreenHeight = 480;
        ppl.config().ProjectionConfig.NearPlane = 0.1F;
        ppl.config().ProjectionConfig.FarPlane = 100.F;

        ppl.config().ModelConfig.Rotation.Angle = 0;

        ppl.setup();
    }

    void drawEvents() override
    {
        ppl.config().CameraConfig.Direction.X = 1;
        ppl.config().CameraConfig.Direction.Y = 0;
        ppl.config().CameraConfig.Direction.Z = 0;

        ppl.config().ModelConfig.Position.X = .1;
        ppl.config().ModelConfig.Position.Y = .2;
        ppl.config().ModelConfig.Position.Z = .3;
        ppl.config().ModelConfig.Rotation.X = 1;
        ppl.config().ModelConfig.Rotation.Y = 0;
        ppl.config().ModelConfig.Rotation.Z = 0;
        ppl.config().ModelConfig.Rotation.Angle += 1;

        ppl.run();
    }

    void keypressEvents() override
    {
        if (isPressed(GLFW_KEY_W))
        {
            ppl.config().CameraConfig.Position.Z += .05;
        }
        else if (isPressed(GLFW_KEY_S))
        {
            ppl.config().CameraConfig.Position.Z -= .05;
        }
        else if (isPressed(GLFW_KEY_A))
        {
            ppl.config().CameraConfig.Position.Y -= .05;
        }
        else if (isPressed(GLFW_KEY_D))
        {
            ppl.config().CameraConfig.Position.Y += .05;
        }
    }
};

} // namespace trailblazer::gfx