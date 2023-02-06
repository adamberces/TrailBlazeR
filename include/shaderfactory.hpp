#pragma once

#include <string>
#include <memory>
#include <filesystem>
#include <unordered_map>

#include "shader.hpp"


static const std::string GLSL_PATH = "assets/shaders/";
static const std::string GLSL_EXTENSION = ".glsl";

class ShaderRepository_c
{
    std::unordered_map<std::string, std::shared_ptr<Shader_c>> Shaders;

public:
    ShaderFactory_c(std::string Path)
    {
        for (const auto& file :
             std::filesystem::recursive_directory_iterator(GLSL_PATH))
        {
            if (file.path().extension() == GLSL_EXTENSION)
            {

            }
        }
    }
};