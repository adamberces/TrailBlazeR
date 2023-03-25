#include <trailblazer/map/mapfile.hpp>

#include <memory>
#include <fstream>
#include <cstring>


namespace trailblazer::map
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for MapFile_c

std::string MapFile_c::readString(const buffer_t& buf, std::size_t& start)
{
    std::string out;

    char c = buf.at(start);
    while (c != '\0')
    {
        out += c;
        c = buf.at(++start);
    }

    return out;
}

// Reads and validates the TMF header, which is:
// bytes 0-2: characters 'TMF'
//
// Then comes a 3 byte which describes the map's color theme,
// which is used to colorize the HUD font and the fog in the fragment shader
//
// Then comes two null delimited strings with the map's title and
// the background image's filename

void MapFile_c::readHeader(const buffer_t& buf, std::size_t& bufPtr)
{
    if (buf.size() < HEADER_SIZE + 1)
    {
        throw std::runtime_error("MapFile_c::readHeader: "
            "file too short to contain header or at least one tile data!");
    }

    // Validate 'TMF' header, which sould be the first 3 bytes
    if (::memcmp(buf.data(), EXTENSION,
                    std::size(EXTENSION) != 0))
    {
        throw std::runtime_error("MapFile_c::readHeader: "
            "no 'TMF' header found.");
    }

    // Read color theme and convert to OpenGL float format
    MapMetadata.ColorTheme.R = static_cast<unsigned char>(buf.at(3)) / 255.F;
    MapMetadata.ColorTheme.G = static_cast<unsigned char>(buf.at(4)) / 255.F;
    MapMetadata.ColorTheme.B = static_cast<unsigned char>(buf.at(5)) / 255.F;

    // Read map title and background data
    MapMetadata.MapTitle  = readString(buf, bufPtr);
    MapMetadata.BackgroundFileName = readString(buf, ++bufPtr);
}

void MapFile_c::readTileData(const buffer_t& buf, std::size_t& bufPtr)
{
    for (size_t i = bufPtr; i < buf.size(); i++)
    {
        TileType_e t = TileType_e::NORMAL;
        Color_e c = static_cast<Color_e>(buf.at(i));

        // Validate the color code
        if (c >= Color_e::COLOR_COUNT)
        {
            throw std::runtime_error("MapFile_c::readTileData: "
                "Invalid color code " + std::to_string(static_cast<int>(c)) + 
                " at position: " + std::to_string(i));
        }
        
        // Check if the color has a corresponding special type
        if (SpecialRules.contains(c))
        {
            t = SpecialRules[c];
        }

        Tiles.push_back({ t, c });

        if (t != TileType_e::FINISH)
        {
            MapMetadata.TileCount++;
        }
    }

    // Let's see if the last row is complete or not
    if ((Tiles.size() % Constants_s::MAP_WIDTH) != 0)
    {
        throw std::runtime_error("MapFile_c::readTileData: "
            "The last row in incomplete, expecting " + std::to_string(Constants_s::MAP_WIDTH) +
            "tiles, got " + std::to_string(Tiles.size() % Constants_s::MAP_WIDTH));
    }

    // Set the correct number of tile rows
    MapMetadata.TileCount /= Constants_s::MAP_WIDTH;
}

void MapFile_c::loadMap(const std::string& fileName)
{
    std::ifstream ifs(fileName, std::ifstream::ate | std::ifstream::binary);

    if (!ifs.good())
    {
        throw std::runtime_error("MapFile_c::loadMap: "
            "Cannot open " + fileName);
    }

    ifs.seekg(0, std::ios::end);
    size_t sz = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    buffer_t buf = buffer_t(sz);
    ifs.read(buf.data(), sz);

    std::size_t bufPtr = HEADER_SIZE;
    readHeader(buf, bufPtr);
    readTileData(buf, ++bufPtr);
}

MapFile_c::MapFile_c(const std::string& fileName)
{
    loadMap(fileName);
}

} // trailblazer::map
