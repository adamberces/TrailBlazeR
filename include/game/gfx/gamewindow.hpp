#pragma once

#include <memory>

#include <glkit/window/glwindow.hpp>
#include <game/gfx/renderpipeline.hpp>
#include <game/map/map.hpp>

namespace trailblazer::gfx
{

class GameWindow_c : public glkit::window::GLWindow_i
{
public:
    using glkit::window::GLWindow_i::GLWindow_i;

    enum class KeyEvents_e
    {
        NONE,
        LEFT,
        RIGHT,
        JUMP
    };

private:
    KeyEvents_e LastKeyEvent;
    
    shared_ptr<map::Map_c> Map;
    shared_ptr<ball::Ball_c> Ball;

public:
    void setBall(shared_ptr<ball::Ball_c>& ball)
    {
        Ball = ball;
    }

    void setMap(shared_ptr<map::Map_c>& map)
    {
        Map = map;
    }

    KeyEvents_e lastKeyEvent() const
    {
        return LastKeyEvent;
    }

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
    }

    void drawEvents() override
    {
        Map->draw();
        Ball->draw();
    }

    void keypressEvents() override
    {
        LastKeyEvent = KeyEvent_e::NONE;

        if (isPressed(GLFW_KEY_A))
        {
            LastKeyEvent = KeyEvent_e::LEFT;
        }
        else if (isPressed(GLFW_KEY_D))
        {
            LastKeyEvent = KeyEvent_e::RIGHT;
        }
        else if (isPressed(GLFW_KEY_SPACE))
        {
            LastKeyEvent = KeyEvent_e::JUMP;
        }
    }
};

} // namespace trailblazer::gfx