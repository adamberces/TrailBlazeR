#pragma once

#include <trailblazer/map/map.hpp>


namespace trailblazer::map
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Reads TMF files from a given folder and keeps a storage of maps

class MapManager_c
{
    std::vector<std::string> MapFiles;

    void collectMapFiles(std::string path);

public:
    const std::vector<std::string>& mapFiles() const
    {
        return MapFiles;
    }

    explicit MapManager_c(std::string path);
};

} /// trailblazer::map
