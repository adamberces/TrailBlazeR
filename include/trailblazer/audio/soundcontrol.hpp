#pragma once

#include <SFML/Audio.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>


namespace trailblazer::audio
{

class SoundControl_c : public messaging::MessageRecipient_i
{

public:
    void sendMessage(msg_t m)
    {
        if (isMessageType<msgSoundEvent_e>(m))
        {
            msgSoundEvent_e e = msg_cast<msgSoundEvent_e>(m);
            switch (e)
            {
                case msgSoundEvent_e::BOUNCE:
                    sf::SoundBuffer buffer;
                    buffer.loadFromFile("./assets/audio/bounce.ogg");
                    sf::Sound sound;
                    sound.setBuffer(buffer);
                    sound.play();
                    break;
            }
   
        }
    }

    SoundControl_c(messaging::PostOffice_c* po) :
        MessageRecipient_i(po)
    {   
        // Manage subscriptions
        PO->subscribeRecipient<msgSoundEvent_e>(this);
    }    

};

}