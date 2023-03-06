#pragma once

#include <vector>
#include <string>
#include <memory>
#include <ifstream>
#include <game/map/tile.hpp>
#include <game/gfx/renderpipeline.hpp>


namespace trailblazer::map
{

class MapFile_c
{
    // Creating an alias for prettier code
    using buffer_t = std::vector<unsigned char>;

    // Number of tiles in a row
    unsigned short Width;

    // The tile data, which is served for the main Map_c class
    std::vector<Tile_t> Tiles;

public:
    decltype(Width) width() const
    {
        return Width;
    }

    decltype(Tiles) tiles() const
    {
        return Tiles;
    }


    void readHeader(buffer_t buf)
    {
        if (buf.size() < 5)
        {
            throw std::runtime_error("MapFile_c::readHeader: "
                "file too short to contain header or at least one tile data!");
        }
        
        // Validate 'MAP' header, which sould be the first 3 bytes
        if (buf.at(0) != 0x4D ||
            buf.at(1) != 0x41 ||
            buf.at(2) != 0x50)
        {
            throw std::runtime_error("MapFile_c::readHeader: "
                "no 'MAP' header found.");
        }

        // Read Width data
        Width = static_cast<unsigned short>(buf.at(3));
    }

    void readTileData(buffer_t buf)
    {
        for (size_t i = 4; i < buf.size(); i++)
        {
            TileType_e t = TileType_e::NORMAL;
            Color_e c = static_cast<Color_e>(buf.at(i));

            // Validate the color code
            if (c > = Color_e::COLOR_COUNT)
            {
                throw std::runtime_error("MapFile_c::readTileData: "
                "Invalid color code " + std::to_string(c) + 
                " at position: " + std::to_string(id_t));
            }
            
            // Check if the color has a corresponding special type
            if (SpecialRules.contains(c))
            {
                t = SpecialRules[c];
            }

            Tiles.push_back({ t, c });
        }
    }

    void loadMap(std::string fileName)
    {
        std::ifstream if(fileName);
        if.seekg(0, std::ios::end);
        size_t sz = if.tellg();
        if.seekg(0, std::ios::beg);

        buffer_t buf = buffer_t(sz);
        readHeader(buf);
        readTileData(buf);
    }

    explicit MapFile_c(std::string fileName)
    {
       loadMap(fileName);
    }
};

class Map_c
{
    MapFile_c MapFile;
    trailblazer::gfx::TilePipeline_c PL;

public:
    void draw()
    {
        // Setup initial position
        PL.ModelConfig.Position.X = -1.F;
        PL.ModelConfig.Position.Y =  0.F;
        PL.ModelConfig.Position.Z = -0.05F;

        // Set up counter to know when to start the next row
        std::size_t row_cnt = 1;

        for (const Tile_s& t : MapFile.tiles())
        {
            PL.ModelColorConfig.Color = ColorCodes[static_cast<size_t>(t.Color)];

            if (row_cnt > MapFile.width())
            {
                // Shift to next row
                PL.ModelConfig.Position.X = 0.F;
                PL.ModelConfig.Position.Y += 1.F;
                row_cnt = 1;
            }
            else
            {
                // Draw next tile in the row            
                PL.ModelConfig.Position.X += 1.F;
            }

            // Don't render anything if the tile type is a gap
            if (t.Type != TileType_e::GAP)
            {
                PL.run();
            }

            row_cnt++;
        }
    }

    explicit Map_c(std::string mapFile) :
        MapFile(mapFile)
    {
        PL.setup();
    }
};

} // trailblazer::map
