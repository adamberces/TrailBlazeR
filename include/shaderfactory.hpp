#pragma once

#include <map>
#include <string>
#include <filesystem>

#include "shader.hpp"


static const std::string GLSL_EXTENSION = ".glsl";

class ShaderRepository_c
{


public:
    ShaderFactory_c(std::string Path)
    {
        for (const auto& file :
             std::filesystem::recursive_directory_iterator)
        {
            if (file.path().extension() == GLSL_EXTENSION)
            {
                
            }
        }
    }
};