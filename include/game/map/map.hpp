#pragma once

#include <vector>
#include "tile.hpp"

#include <game/gfx/renderpipeline.hpp>


class Map_c
{
    unsigned Width = 3;
    unsigned Height = 8;

    std::vector<Tile_t> Tiles;
    trailblazer::gfx::TilePipeline_c ppl;

public:
    void draw()
    {
        ppl.ModelConfig.Position.X = 0;
        ppl.ModelConfig.Position.Y = 0;
        ppl.ModelConfig.Position.Z = 0;
        ppl.ModelConfig.Rotation.X = 1;
        ppl.ModelConfig.Rotation.Y = 0;
        ppl.ModelConfig.Rotation.Z = 0;
        ppl.ModelConfig.Rotation.Angle = 0;

        std::size_t row_cnt = 0;
        for (const auto& t : Tiles)
        {
            if (row_cnt > Width)
            {
                // shift to next row
                ppl.ModelConfig.Position.X = 0.F;
                ppl.ModelConfig.Position.Y += 1.F;
                row_cnt = 0;
            }
            else
            {
                // draw next tile in the row            
                ppl.ModelConfig.Position.X += 1.F;
            }

            ppl.run();
            row_cnt++;
        }
    }

    Map_c()
    {
        ppl.setup();
        Tiles =
        {
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },

            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },
            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },

            { NORMAL, BLUE }, { NORMAL, RED }, { NORMAL, BLUE },
            { NORMAL, RED }, { NORMAL, BLUE }, { NORMAL, RED },

        };
    }
};