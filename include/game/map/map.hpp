#pragma once

#include <cmath>

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

    void draw(glkit::functors::point3d_t ballPosition)
    {
        // Setup initial position
        Pipeline.ModelConfig.Position.X = -1.F;
        Pipeline.ModelConfig.Position.Y =  0.F;
        Pipeline.ModelConfig.Position.Z = -0.05F;

        // We will never render the whole map for each frame,
        // so we shall discard some rows both from the beginning
        // and from the end based on the ball's Y position
        int ballPosY = static_cast<int>(::floor(ballPosition.Y));
        int firstRow = std::max(ballPosY - 2, 0);
        int lastRow = std::min(ballPosY + 20,static_cast<int>(MapFile.tiles().size()));

        // Set up counter to know when to stop drawing
        std::size_t rowCnt = 0;

        // Set up counter to know when to start the next row
        std::size_t colCnt = 1;

        for (const Tile_s& t : MapFile.tiles())
        {
            Pipeline.ModelColorConfig.Color = ColorCodes[static_cast<size_t>(t.Color)];

            if (colCnt > MapFile.width())
            {
                // Shift to next row
                Pipeline.ModelConfig.Position.X = 0.F;
                Pipeline.ModelConfig.Position.Y += 1.F;
                rowCnt++;
                colCnt = 1;
            }
            else
            {
                // Draw next tile in the row            
                Pipeline.ModelConfig.Position.X += 1.F;
            }

            // Don't render anything if the tile type is a gap
            if (t.Type != TileType_e::GAP &&
                rowCnt >= firstRow &&
                rowCnt <= lastRow )
            {
                Pipeline.run();
            }

            colCnt++;
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
