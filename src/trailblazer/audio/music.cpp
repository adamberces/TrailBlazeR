#include <stdexcept>

#include <trailblazer/audio/music.hpp>
#include <trailblazer/game/gameconfig.hpp>

namespace trailblazer::audio
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for Music_c

Music_c::Music_c(std::string fileName)
{   
    if (!(Music.openFromFile(fileName)))
    {
        throw std::runtime_error("Music_c::Music_c: cannot open " + fileName);
    }
    
    Music.setLoop(true);
    Music.setVolume(Constants_s::MUSIC_VOLUME);
    Music.play();
}  

Music_c::~Music_c()
{
    Music.stop();
}  

} // trailblazer::audio