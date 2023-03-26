#pragma once

#include <cmath>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/map/mapfile.hpp>
#include <trailblazer/pipelines/pipeline_tile.hpp>


namespace trailblazer::map
{
    
/////////////////////////////////////////////////////////////////////////////////////////
/// Represents a game map (aka. stage), contains a mapfile and a drawing pipeline
/// which renders the tiles contained in the MapFile

class Map_c : public messaging::MessageRecipient_i
{
    MapFile_c MapFile;
    trailblazer::pipelines::TilePipeline_c Pipeline;

    /// Returns the tile type of a tile of the given position,
    /// where x = 0; y = 0 is the bottom left of the map
    TileType_e getTile(int x, int y);

public:
    const inline MapMetadata_s& mapMetaData() const
    {
        return MapFile.mapMetadata();
    }

    void sendMessage(msg_t m) override;

    /// Redraw the map on the screen using the render pipeline
    void draw();

    /// Constructs the map from a map file name (TMF)
    explicit Map_c(messaging::PostOffice_c* po, 
                   const std::string& mapFile);
};

} /// trailblazer::map
