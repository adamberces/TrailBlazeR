#pragma once

#include <vector>
#include "tile.hpp"

#include <game/gfx/renderpipeline.hpp>

namespace trailblazer::gfx
{



class Map_c
{
    unsigned Width = 5;

    std::vector<Tile_t> Tiles;
    trailblazer::gfx::TilePipeline_c ppl;
    trailblazer::gfx::BallPipeline_c b;

public:
    void draw()
    {
        ppl.ModelConfig.Position.X = -1;
        ppl.ModelConfig.Position.Y = 0;
        ppl.ModelConfig.Position.Z = 0;

        b.ModelConfig.Position.X = 2;
        b.ModelConfig.Position.Y = .5;
        b.ModelConfig.Position.Z = .25;
        b.ModelConfig.Scale.X = .25;
        b.ModelConfig.Scale.Y = .25;
        b.ModelConfig.Scale.Z = .25;
        b.ModelColorConfig.Color.R = 1.F;
        b.ModelColorConfig.Color.G = 0.F;
        b.ModelColorConfig.Color.B = 0.F;
        b.ModelConfig.Rotation.Angle -= 5;


        std::size_t row_cnt = 1;
        for (const auto& t : Tiles)
        {
            if (t.Color == RED)
            {
                ppl.ModelColorConfig.Color.R = 1.F;
                ppl.ModelColorConfig.Color.G = 0.F;
                ppl.ModelColorConfig.Color.B = 0.F;
            }
            else if (t.Color == BLUE)
            {
                ppl.ModelColorConfig.Color.R = 0.F;
                ppl.ModelColorConfig.Color.G = 0.F;
                ppl.ModelColorConfig.Color.B = 1.F;
            }
            else if (t.Color == GREEN)
            {
                ppl.ModelColorConfig.Color.R = 0.F;
                ppl.ModelColorConfig.Color.G = 1.F;
                ppl.ModelColorConfig.Color.B = 0.F;
            }

            if (row_cnt > Width)
            {
                // shift to next row
                ppl.ModelConfig.Position.X = 0.F;
                ppl.ModelConfig.Position.Y += 1.F;
                row_cnt = 1;
            }
            else
            {
                // draw next tile in the row            
                ppl.ModelConfig.Position.X += 1.F;
            }

            ppl.run();
            b.run();
            row_cnt++;
        }
    }

    Map_c()
    {
        b.setup();
        ppl.setup();
        Tiles =
        {
            { NORMAL, GREEN }, { NORMAL, GREEN }, { NORMAL, GREEN }, { NORMAL, GREEN }, { NORMAL, GREEN },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },      
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            
        };
    }
};

}