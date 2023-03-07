#pragma once

#include <iostream>
#include <filesystem>
#include <game/map/map.hpp>


namespace trailblazer::map
{

class MapManager_c
{
    int ActualMapIndex;
    std::vector<std::shared_ptr<Map_c>> Maps;

    void collectMapFiles(std::string path)
    {
        // Parse the maps directory and look for TMF files
        for (const auto& f : std::filesystem::directory_iterator(path))
        {
            // Get extension in upper case
            std::string ext = f.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c){ return std::toupper(c); });

            // Remove dot from the beginning
            ext.erase(0, 1);

            std::cout <<ext << std::endl;

            if (f.is_regular_file() &&
                ext.compare(std::string(MapFile_c::EXTENSION)) == 0)
            {
                // Construct Map objects from the filename
                std::string tmf = f.path().filename().string();
                
                Maps.push_back(std::make_shared<Map_c>(path + "/" + tmf));
                std::cout << "Mapfile " << tmf << " found." << std::endl;
            }
        }
    }

public:
    std::shared_ptr<Map_c> getNextMap()
    {
        ActualMapIndex++;
        return Maps.at(ActualMapIndex);
    }

    MapManager_c(std::string path) :
        ActualMapIndex(-1)
    {
        collectMapFiles(path);
    }

};

} // trailblazer::map
