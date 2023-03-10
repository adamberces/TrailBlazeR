#pragma once

#include <game/map/mapfile.hpp>
#include <game/presentation/tilepipeline.hpp>


namespace trailblazer::map
{

class Map_c
{
    MapFile_c MapFile;
    trailblazer::presentation::TilePipeline_c Pipeline;

public:
    // Returns the tile type of a tile of the given position,
    // where x = 0; y = 0 is the bottom left of the map
    TileType_e getTile(size_t x, size_t y)
    {
        size_t index = MapFile.width() * y + x;
        return MapFile.tiles().at(index).Type;
    }


    // Redraw the map on the screen using the render pipeline

    void draw()
    {
        // Setup initial position
        Pipeline.ModelConfig.Position.X = -1.F;
        Pipeline.ModelConfig.Position.Y =  0.F;
        Pipeline.ModelConfig.Position.Z = -0.05F;

        // Set up counter to know when to start the next row
        std::size_t row_cnt = 1;
        std::size_t firstRow = 0;
        std::size_t lastRow = std::max()

        for (const Tile_s& t : MapFile.tiles())
        {
            Pipeline.ModelColorConfig.Color = ColorCodes[static_cast<size_t>(t.Color)];

            if (row_cnt > MapFile.width())
            {
                // Shift to next row
                Pipeline.ModelConfig.Position.X = 0.F;
                Pipeline.ModelConfig.Position.Y += 1.F;
                row_cnt = 1;
            }
            else
            {
                // Draw next tile in the row            
                Pipeline.ModelConfig.Position.X += 1.F;
            }

            // Don't render anything if the tile type is a gap
            if (t.Type != TileType_e::GAP)
            {
                Pipeline.run();
            }

            row_cnt++;
        }
    }


    // Constructs the map from a map file (TMF)

    explicit Map_c(const std::string& mapFile) :
        MapFile(mapFile)
    {
        Pipeline.setup();
    }
};

} // trailblazer::map
