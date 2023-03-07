#pragma once

#include <game/gfx/renderpipeline.hpp>


namespace trailblazer::ball
{

class Ball_c
{
    float Diameter = 0.25F
    trailblazer::gfx::BallPipeline_c PL;

public:
    float diameter()
    {
        return Diameter;
    }

    void moveLeft();

    void moveRight();

    void jump();

    glkit::functors::point3d_t getPosition()
    {
        return PL.ModelConfig.Position;
    }

    void draw()
    {
        PL.ModelConfig.Position.X = 2;
        PL.ModelConfig.Position.Y = .5;
        PL.ModelConfig.Position.Z = .25;
        PL.ModelConfig.Scale.X = Diameter;
        PL.ModelConfig.Scale.Y = Diameter;
        PL.ModelConfig.Scale.Z = Diameter;
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