#pragma once

#include <game/presentation/renderpipeline.hpp>


namespace trailblazer::ball
{

class Ball_c
{
    float Diameter = 0.25F;
    trailblazer::presentation::BallPipeline_c PL;

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
        PL.ModelConfig.Position.Y += .01;
        PL.ModelConfig.Rotation.Angle -= 1;
        PL.run();
    }

    Ball_c()
    {
        PL.setup();
        PL.ModelConfig.Position.X = 2;
        PL.ModelConfig.Position.Y = Diameter;
        PL.ModelConfig.Position.Z = Diameter;
        PL.ModelConfig.Scale.X = Diameter;
        PL.ModelConfig.Scale.Y = Diameter;
        PL.ModelConfig.Scale.Z = Diameter;
        PL.ModelColorConfig.Color.R = 1.F;
        PL.ModelColorConfig.Color.G = 0.F;
        PL.ModelColorConfig.Color.B = 0.F;
    }

};

} // namespace trailblazer::ball