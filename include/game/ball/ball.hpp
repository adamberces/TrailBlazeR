#pragma once

#include <game/presentation/ballpipeline.hpp>


namespace trailblazer::ball
{

class Ball_c
{
    float Diameter = 0.25F;
    trailblazer::presentation::BallPipeline_c Pipeline;

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
        return Pipeline.ModelConfig.Position;
    }

    void draw()
    {
        Pipeline.ModelConfig.Position.Y += .01;
        Pipeline.ModelConfig.Rotation.Angle -= 1;
        Pipeline.run();
    }

    Ball_c()
    {
        Pipeline.setup();
        Pipeline.ModelConfig.Position.X = 2;
        Pipeline.ModelConfig.Position.Y = Diameter;
        Pipeline.ModelConfig.Position.Z = Diameter;
        Pipeline.ModelConfig.Scale.X = Diameter;
        Pipeline.ModelConfig.Scale.Y = Diameter;
        Pipeline.ModelConfig.Scale.Z = Diameter;
        Pipeline.ModelColorConfig.Color.R = 1.F;
        Pipeline.ModelColorConfig.Color.G = 0.F;
        Pipeline.ModelColorConfig.Color.B = 0.F;
    }

};

} // namespace trailblazer::ball