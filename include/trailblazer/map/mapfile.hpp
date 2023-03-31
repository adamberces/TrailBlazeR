#pragma once

#include <vector>
#include <string>

#include <trailblazer/map/tile.hpp>
#include <trailblazer/game/gameconfig.hpp>
#include <glkit/functors/functor_types.hpp>

namespace trailblazer::map
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Contains all the data stored in the TMF file which is not the actual tile data

struct MapMetadata_s
{
    glkit::functors::rgb_t ColorTheme;
    std::string MapTitle;
    std::string BackgroundFileName;
    int TileCount = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////
/// Reads and stores the data of a TMF mapfile

class MapFile_c
{
public:
    static constexpr size_t HEADER_SIZE = 6;
    static constexpr char EXTENSION[] = "TMF";

private:
    /// Creating an alias for prettier code
    using buffer_t = std::vector<char>;

    /// The tile data, which is served for the main Map_c class
    std::vector<Tile_s> Tiles;

    /// Stores the map's metadata (eg. title, background image)
    MapMetadata_s MapMetadata;

    /// Reads a NULL delimited string from the map header
    std::string readString(const buffer_t& buf, std::size_t& start);

    /// Reads and validates the TMF header
    void readHeader(const buffer_t& buf, std::size_t& bufPtr);

    /// Reads the actual map data, where each byte stands for a title
    void readTileData(const buffer_t& buf, std::size_t& bufPtr);

    /// The main map reading method
    void loadMap(const std::string& fileName);

public:
    const inline decltype(Tiles)& tiles() const
    {
        return Tiles;
    }

    const inline MapMetadata_s& mapMetadata() const
    {
        return MapMetadata;
    }

    explicit MapFile_c(const std::string& fileName);
};

} /// trailblazer::map
