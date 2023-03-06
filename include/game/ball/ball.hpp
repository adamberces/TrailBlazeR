#pragma once

#include <game/gfx/renderpipeline.hpp>


namespace trailblazer::ball
{

class Ball_c
{
    trailblazer::gfx::BallPipeline_c PL;

public:
    void moveLeft();

    void moveRight();

    void jump();

    point3d_t getPosition();

    void draw()
    {
        PL.ModelConfig.Position.X = 2;
        PL.ModelConfig.Position.Y = .5;
        PL.ModelConfig.Position.Z = .25;
        PL.ModelConfig.Scale.X = .25;
        PL.ModelConfig.Scale.Y = .25;
        PL.ModelConfig.Scale.Z = .25;
        PL.ModelColorConfig.Color.R = 1.F;
        PL.ModelColorConfig.Color.G = 0.F;
        PL.ModelColorConfig.Color.B = 0.F;
        PL.ModelConfig.Rotation.Angle -= 5;
    }

    Ball_c()
    {
        PL.setup();
    }

};

} // namespace trailblazer::ball