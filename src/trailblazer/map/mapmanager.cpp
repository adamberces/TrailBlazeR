#include <trailblazer/map/mapmanager.hpp>

#include <iostream>
#include <memory>
#include <filesystem>


namespace trailblazer::map
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for MapManager_c

void MapManager_c::collectMapFiles(std::string path)
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

        if (f.is_regular_file() &&
            ext.compare(std::string(MapFile_c::EXTENSION)) == 0)
        {
            // Construct Map objects from the filename
            std::string tmf = f.path().filename().string();
            
            MapFiles.push_back(std::string(path + "/" + tmf));
            std::cout << "Mapfile " << tmf << " found." << std::endl;
        }
    }
}


MapManager_c::MapManager_c(std::string path)
{
    collectMapFiles(path);
}

} // trailblazer::map
