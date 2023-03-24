#pragma once

#include <vector>
#include <string>
#include <memory>
#include <fstream>

#include <trailblazer/map/tile.hpp>
#include <trailblazer/game/constants.hpp>
#include <glkit/functors/functor_types.hpp>

namespace trailblazer::map
{

struct MapMetadata_s
{
    glkit::functors::rgb_t ColorTheme;
    std::string MapTitle;
    std::string BackgroundFileName;
};

class MapFile_c
{
public:
    static constexpr size_t HEADER_SIZE = 6;
    static constexpr char EXTENSION[] = "TMF";

private:
    // Creating an alias for prettier code
    using buffer_t = std::vector<char>;

    // The tile data, which is served for the main Map_c class
    std::vector<Tile_s> Tiles;

    MapMetadata_s MapMetadata;

public:

    const decltype(Tiles)& tiles() const
    {
        return Tiles;
    }

    // Reads a NULL delimited string from the map header
    std::string readString(const buffer_t& buf, std::size_t& start)
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
    // byte 3: describes the width of a row

    void readHeader(const buffer_t& buf, std::size_t& bufPtr)
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

        // Read metadata
        MapMetadata.ColorTheme.R = static_cast<unsigned char>(buf.at(3));
        MapMetadata.ColorTheme.G = static_cast<unsigned char>(buf.at(4));
        MapMetadata.ColorTheme.B = static_cast<unsigned char>(buf.at(5));

        MapMetadata.MapTitle  = readString(buf, bufPtr);
        MapMetadata.BackgroundFileName = readString(buf, ++bufPtr);
    }

    void readTileData(const buffer_t& buf, std::size_t& bufPtr)
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
        }

        // Let's see if the last row is complete or not
        if (Tiles.size() % Constants_s::MAP_WIDTH != 0)
        {
            throw std::runtime_error("MapFile_c::readTileData: "
                "The last row in incomplete, expecting " + std::to_string(Constants_s::MAP_WIDTH) +
                "tiles, got " + std::to_string(Tiles.size() % Constants_s::MAP_WIDTH));
        }
    }

    void loadMap(const std::string& fileName)
    {
        std::ifstream ifs(fileName);

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

    explicit MapFile_c(const std::string& fileName)
    {
       loadMap(fileName);
    }
};

} // trailblazer::map
