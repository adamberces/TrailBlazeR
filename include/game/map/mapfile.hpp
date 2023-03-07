#pragma once

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <game/map/tile.hpp>


namespace trailblazer::map
{

class MapFile_c
{
public:
    static constexpr size_t HEADER_SIZE = 4;
    static constexpr char EXTENSION[] = "TMF";

private:
    // Creating an alias for prettier code
    using buffer_t = std::vector<char>;

    // Number of tiles in a row
    unsigned short Width;

    // The tile data, which is served for the main Map_c class
    std::vector<Tile_s> Tiles;

public:
    decltype(Width) width() const
    {
        return Width;
    }

    decltype(Tiles) tiles() const
    {
        return Tiles;
    }


    void readHeader(const buffer_t& buf)
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

        // Read Width data
        Width = static_cast<unsigned short>(buf.at(3));
    }

    void readTileData(const buffer_t& buf)
    {
        for (size_t i = HEADER_SIZE; i < buf.size(); i++)
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

        readHeader(buf);
        readTileData(buf);
    }

    explicit MapFile_c(const std::string& fileName)
    {
       loadMap(fileName);
    }
};

} // trailblazer::map
