#pragma once

#include <stdexcept>
#include <SFML/Audio.hpp>


namespace trailblazer::audio
{

class Music_c
{
    sf::Music Music;

public:
    Music_c(std::string fileName)
    {   
        if (!(Music.openFromFile(fileName)))
        {
            throw std::runtime_error("Music_c::Music_c: cannot open " + fileName);
        }
        
        Music.setLoop(true);
        Music.setVolume(10);
        Music.play();
    }  

    ~Music_c()
    {
        Music.stop();
    }  
};

}