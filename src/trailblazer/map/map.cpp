#include <cmath>
#include <trailblazer/map/map.hpp>


namespace trailblazer::map
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for Map_c

TileType_e Map_c::getTile(int x, int y)
{
    int index = Constants_s::MAP_WIDTH * y + x;
    return MapFile.tiles().at(index).Type;
}

const MapMetadata_s& Map_c::mapMetaData() const
{
    return MapFile.mapMetadata();
}

void Map_c::sendMessage(msg_t m)
{
    if (isMessageType<msgRedrawTrigger_s>(m))
    {
        draw();
    }
    else if (isMessageType<msgBallPosition_s>(m))
    {
        // Calculate the tile's index on which the ball
        // can be actually found and return it's tile type
        // for collision detection in the game control
        msgBallPosition_s p = msg_cast<msgBallPosition_s>(m);
        int x = static_cast<int>(::floor(p.Position.X + 0.5F));
        int y = static_cast<int>(::floor(p.Position.Y + 0.5F));
        msgActualTileType_s tiletype({ getTile(x, y) });
        PO->broadcastMessage(tiletype);

        // Calculate the progress and transfer the map metadata for HUD
        PO->broadcastMessage<msgMapData_s>({ MapFile.mapMetadata(), y });
    }
}

void Map_c::draw()
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
    int rowCnt = 0;

    // Set up counter to know when to start the next row
    int colCnt = 1;

    for (const Tile_s& t : MapFile.tiles())
    {
        Pipeline.ModelColorConfig.Color = ColorCodes[static_cast<size_t>(t.Color)];

        if (colCnt > Constants_s::MAP_WIDTH)
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

Map_c::Map_c(messaging::PostOffice_c* po, 
    const std::string& mapFile) :
    MessageRecipient_i(po),
    MapFile(mapFile)
{
    Pipeline.setup();
    PO->subscribeRecipient<msgRedrawTrigger_s>(this);
    PO->subscribeRecipient<msgBallPosition_s>(this);
}


} // trailblazer::map
