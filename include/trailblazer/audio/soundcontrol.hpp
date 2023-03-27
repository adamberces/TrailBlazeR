#pragma once

#include <string>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

#include <SFML/Audio.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/game/constants.hpp>

namespace trailblazer::audio
{

class SoundControl_c : public messaging::MessageRecipient_i
{
    sf::Sound Sound;
    std::unordered_map<msgSoundEvent_e, sf::SoundBuffer> SoundBuffers;

    float Timeout = 0;

    sf::SoundBuffer loadSound(std::string fileName)
    {
        sf::SoundBuffer buffer;
        std::string path = Files_s::AUDIO_PATH.data() + fileName;

        if (!(buffer.loadFromFile(path)))
        {
            throw std::runtime_error("SoundControl_c::loadSound: cannot open " + fileName);
        }

        std::cout << "Sound found: " << fileName << std::endl;

        return buffer;
    }

    void loadSounds()
    {
        SoundBuffers[msgSoundEvent_e::JUMP] = loadSound("jump.ogg");
        SoundBuffers[msgSoundEvent_e::BOUNCE] = loadSound("bounce.ogg");
        SoundBuffers[msgSoundEvent_e::SPEEDUP] = loadSound("speedup.ogg");
        SoundBuffers[msgSoundEvent_e::BALL_LOST] = loadSound("lost.ogg");
        SoundBuffers[msgSoundEvent_e::LEVEL_WON] = loadSound("cleared.ogg");
        SoundBuffers[msgSoundEvent_e::GAME_OVER] = loadSound("gameover.ogg");
        SoundBuffers[msgSoundEvent_e::GAME_WON] = loadSound("win.ogg");
    }

    void playSound(msgSoundEvent_e event)
    {
        if (Sound.getStatus() != sf::Sound::Status::Playing)
        {
            Sound.setBuffer(SoundBuffers[event]);
            Sound.play();
        }
    }

public:
    void sendMessage(msg_t m)
    {
        if (isMessageType<msgSoundEvent_e>(m))
        {
            msgSoundEvent_e e = msg_cast<msgSoundEvent_e>(m);
            playSound(e);
        }
    }

    SoundControl_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po)
    {
        loadSounds();

        // Manage subscriptions
        PO->subscribeRecipient<msgSoundEvent_e>(this);
    }    

};

}