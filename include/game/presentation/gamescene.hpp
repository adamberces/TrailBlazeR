#pragma once

#include <glkit/window/scene.hpp>

#include <game/map/map.hpp>
#include <game/ball/ball.hpp>
#include <game/presentation/renderpipeline.hpp>


namespace trailblazer::presentation
{

class GameScene_c : public glkit::window::Scene_i
{
    map::Map_c& Map;
    ball::Ball_c& Ball;

    // Updates the scene's globals (camera and lightning uniforms)
    // to follow the movement of the ball
    void updateGlobals(glkit::functors::point3d_t ballPos)
    {
        // Update lightning position

        RenderPipeline_i::LightningPositionConfig.Position.X =
            ballPos.X;
        RenderPipeline_i::LightningPositionConfig.Position.Y =
            ballPos.Y - Ball.diameter();
        RenderPipeline_i::LightningPositionConfig.Position.Z = 0.5F;

        // Update camera positions

        RenderPipeline_i::CameraConfig.Position.X = 2;
        RenderPipeline_i::CameraConfig.Position.Y = ballPos.Y - 5;
        RenderPipeline_i::CameraConfig.Position.Z = 1.5;

        RenderPipeline_i::CameraConfig.Direction.X = 2;
        RenderPipeline_i::CameraConfig.Direction.Y = ballPos.Y + 5;
        RenderPipeline_i::CameraConfig.Direction.Z = .5;

        RenderPipeline_i::CameraPositionConfig.Position =
            RenderPipeline_i::CameraConfig.Position;
    }

public:
    // Redraw the scene

    void draw()
    {
        // Update positions in the global uniforms (camera, lightning)
        updateGlobals(Ball.getPosition());

        // Redraw scene
        Map.draw();
        Ball.draw();
    }

    // Setup the uniforms of the render pipeline, which won't change
    // during the lifetime of the scene: projection matrix, lighning color
    void setup()
    {
        // Setup projection matrix
        RenderPipeline_i::ProjectionConfig.FOV = 45.F;
        RenderPipeline_i::ProjectionConfig.ScreenWidth = 640;
        RenderPipeline_i::ProjectionConfig.ScreenHeight = 480;
        RenderPipeline_i::ProjectionConfig.NearPlane = 0.1F;
        RenderPipeline_i::ProjectionConfig.FarPlane = 100.F;

        // Setup lightning color
        RenderPipeline_i::LightningColorConfig.Color.R = .5F;
        RenderPipeline_i::LightningColorConfig.Color.G = .5F;
        RenderPipeline_i::LightningColorConfig.Color.B = 1.F;
    }

    GameScene_c(map::Map_c& map, ball::Ball_c& ball) :
        Map(map),
        Ball(ball)
    {
        setup();

        // Setup the initial positions according to the ball's properties
        updateGlobals(Ball.getPosition());
    }

};

} // namespace trailblazer::presentation