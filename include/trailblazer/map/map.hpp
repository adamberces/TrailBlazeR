#pragma once

#include <cmath>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/map/mapfile.hpp>
#include <trailblazer/pipelines/pipeline_tile.hpp>


namespace trailblazer::map
{

class Map_c : public messaging::MessageRecipient_i
{
    MapFile_c MapFile;
    trailblazer::pipelines::TilePipeline_c Pipeline;

    // Returns the tile type of a tile of the given position,
    // where x = 0; y = 0 is the bottom left of the map
    TileType_e getTile(int x, int y)
    {
        int index = MapFile.width() * y + x;
        return MapFile.tiles().at(index).Type;
    }

public:
    void sendMessage(msg_t m) override
    {
        if (isMessageType<msgRedrawTrigger>(m))
        {
            draw();
        }
        else if (isMessageType<msgBallPosition>(m))
        {
            // Calculate the tile's index on which the ball
            // can be actually found and return it's tile type
            // for collision detection in the game control
            msgBallPosition p = msg_cast<msgBallPosition>(m);
            int x = static_cast<int>(::floor(p.Position.X + 0.5F));
            int y = static_cast<int>(::floor(p.Position.Y + 0.5F));
            msgActualTileType tiletype({ getTile(x, y) });
            PO->broadcastMessage(tiletype);
        }
    }

    // Redraw the map on the screen using the render pipeline

    void draw()
    {
        // Setup initial position
        Pipeline.ModelConfig.Position.X = -1.F;
        Pipeline.ModelConfig.Position.Y =  0.F;
        Pipeline.ModelConfig.Position.Z =  -.25F - .1F;

        // We will never render the whole map for each frame,
        // so we shall discard some rows both from the beginning
        // and from the end based on the camera's Y position
        int cameraPosY = static_cast<int>(
            ::floor(pipelines::RenderPipeline_i::CameraConfig.Position.Y)
        );
        int firstRow = std::max(cameraPosY - 2, 0);
        int lastRow = std::min(cameraPosY + 20, static_cast<int>(MapFile.tiles().size()));

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

    // Constructs the map from a map file name (TMF)

    explicit Map_c(messaging::PostOffice_c* po, 
        const std::string& mapFile) :
        MessageRecipient_i(po),
        MapFile(mapFile)
    {
        Pipeline.setup();
        PO->subscribeRecipient<msgRedrawTrigger>(this);
        PO->subscribeRecipient<msgBallPosition>(this);
    }
};

} // trailblazer::map
