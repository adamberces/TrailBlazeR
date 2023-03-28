#pragma once

#include <stdexcept>
#include <SFML/Audio.hpp>


namespace trailblazer::audio
{

/////////////////////////////////////////////////////////////////////////////////////////
// A minimalistic class which starts and loops the background music with SFML
class Music_c
{
    sf::Music Music;

public:
    explicit Music_c(std::string fileName);
    ~Music_c();
};

} // trailblazer::audio