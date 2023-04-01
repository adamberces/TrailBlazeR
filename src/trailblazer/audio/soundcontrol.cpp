#include <stdexcept>
#include <trailblazer/audio/soundcontrol.hpp>


namespace trailblazer::audio
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for SoundControl_c

sf::SoundBuffer SoundControl_c::loadSound(std::string fileName)
{
    sf::SoundBuffer buffer;
    std::string path = Files_s::AUDIO_PATH.data() + fileName;

    if (!(buffer.loadFromFile(path)))
    {
        throw std::runtime_error("SoundControl_c::loadSound: cannot open " + fileName);
    }

    std::cout << "Sound loaded: " << path << std::endl;

    return buffer;
}

void SoundControl_c::loadSounds()
{
    SoundBuffers[msgSoundEvent_e::BOUNCE]    = { loadSound("bounce.ogg"),   0 };
    SoundBuffers[msgSoundEvent_e::JUMP]      = { loadSound("jump.ogg"),     1 };
    SoundBuffers[msgSoundEvent_e::SPEEDUP]   = { loadSound("speedup.ogg"),  2 };
    SoundBuffers[msgSoundEvent_e::BALL_LOST] = { loadSound("lost.ogg"),     3 };
    SoundBuffers[msgSoundEvent_e::LEVEL_WON] = { loadSound("cleared.ogg"),  3 };
    SoundBuffers[msgSoundEvent_e::GAME_OVER] = { loadSound("gameover.ogg"), 4 };
    SoundBuffers[msgSoundEvent_e::GAME_WON]  = { loadSound("win.ogg"),      4 };
}

void SoundControl_c::playSound(msgSoundEvent_e event)
{
    // Playing sound in reaction to the current event is only
    // allowed, if a sound is not played currently, or the
    // sound which is already playing has lower priority
    priority_t SoundPriority = SoundBuffers[event].second;

    bool soundAllowed =
        (Sound.getStatus() != sf::Sound::Status::Playing) ||
        (LastSoundPriority  < SoundPriority);

    if (soundAllowed)
    {
        Sound.setBuffer(SoundBuffers[event].first);
        Sound.play();
    }
    
    LastSoundPriority = SoundPriority;
}

void SoundControl_c::sendMessage(msg_t m)
{
    if (isMessageType<msgSoundEvent_e>(m))
    {
        msgSoundEvent_e e = msg_cast<msgSoundEvent_e>(m);
        playSound(e);
    }
}

SoundControl_c::SoundControl_c(messaging::PostOffice_c* po) :
    MessageRecipient_i(po),
    LastSoundPriority(-1)
{
    loadSounds();

    // Manage subscriptions
    PO->subscribeRecipient<msgSoundEvent_e>(this);
}    

} // trailblazer::audio