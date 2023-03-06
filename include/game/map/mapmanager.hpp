#pragma once

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
        for (const auto& f : std::filesystem::directory_iterator(dir_path))
        {
            if (f.is_regular_file() &&
                f.path().extension() == std::string(MapFile_c::EXTENSION))
            {
                // Construct Map objects from the filename
                std::string tmf = entry.path().filename().string();
                Maps.push_back(std::make_shared<Map_c>(tmf));
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
