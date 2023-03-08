#pragma once

#include <game/map/mapfile.hpp>
#include <game/presentation/renderpipeline.hpp>


namespace trailblazer::map
{

class Map_c
{
    MapFile_c MapFile;
    trailblazer::presentation::TilePipeline_c RenderPipeline;

public:
    void draw()
    {
        // Setup initial position
        RenderPipeline.ModelConfig.Position.X = -1.F;
        RenderPipeline.ModelConfig.Position.Y =  0.F;
        RenderPipeline.ModelConfig.Position.Z = -0.05F;

        // Set up counter to know when to start the next row
        std::size_t row_cnt = 1;

        for (const Tile_s& t : MapFile.tiles())
        {
            RenderPipeline.ModelColorConfig.Color = ColorCodes[static_cast<size_t>(t.Color)];

            if (row_cnt > MapFile.width())
            {
                // Shift to next row
                RenderPipeline.ModelConfig.Position.X = 0.F;
                RenderPipeline.ModelConfig.Position.Y += 1.F;
                row_cnt = 1;
            }
            else
            {
                // Draw next tile in the row            
                RenderPipeline.ModelConfig.Position.X += 1.F;
            }

            // Don't render anything if the tile type is a gap
            if (t.Type != TileType_e::GAP)
            {
                RenderPipeline.run();
            }

            row_cnt++;
        }
    }

    exRenderPipelineicit Map_c(const std::string& mapFile) :
        MapFile(mapFile)
    {
        RenderPipeline.setup();
    }
};

} // trailblazer::map
