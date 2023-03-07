#pragma once

#include <game/map/mapfile.hpp>
#include <game/presentation/renderpipeline.hpp>


namespace trailblazer::map
{

class Map_c
{
    MapFile_c MapFile;
    trailblazer::presentation::TilePipeline_c PL;

public:
    void draw()
    {
        // Setup initial position
        PL.ModelConfig.Position.X = -1.F;
        PL.ModelConfig.Position.Y =  0.F;
        PL.ModelConfig.Position.Z = -0.05F;

        // Set up counter to know when to start the next row
        std::size_t row_cnt = 1;

        for (const Tile_s& t : MapFile.tiles())
        {
            PL.ModelColorConfig.Color = ColorCodes[static_cast<size_t>(t.Color)];

            if (row_cnt > MapFile.width())
            {
                // Shift to next row
                PL.ModelConfig.Position.X = 0.F;
                PL.ModelConfig.Position.Y += 1.F;
                row_cnt = 1;
            }
            else
            {
                // Draw next tile in the row            
                PL.ModelConfig.Position.X += 1.F;
            }

            // Don't render anything if the tile type is a gap
            if (t.Type != TileType_e::GAP)
            {
                PL.run();
            }

            row_cnt++;
        }
    }

    explicit Map_c(const std::string& mapFile) :
        MapFile(mapFile)
    {
        PL.setup();
    }
};

} // trailblazer::map
