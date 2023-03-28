#pragma once

#include <string>
#include <SFML/Audio.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/game/constants.hpp>


namespace trailblazer::audio
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Manages a map of sound effects and plays them when a specific event is triggered
//
/// Inherits from MessageRecipient_i:
/// Receives the msgSoundEvent_e message from Ball Control
/// Receives the msgSoundEvent_e message from Game Control  (when the game is over)
/// Receives the msgSoundEvent_e message from the main Game class (when the game is won)

class SoundControl_c : public messaging::MessageRecipient_i
{
    using priority_t = int;

    /// SFML sound player object
    sf::Sound Sound;

    /// Stores the priority value of the last played sound
    /// Which is compared to the priority of the current sound 
    /// to be played and a new sound is only started if it's
    /// priority is bigger.
    priority_t LastSoundPriority;

    std::unordered_map<msgSoundEvent_e, std::pair<sf::SoundBuffer, priority_t>> SoundBuffers;


    /// Contructs a full path of the sound effect and loads it to a SoundBuffer
    sf::SoundBuffer loadSound(std::string fileName);

    /// Loads all sound effects used in the game and set their priorities
    void loadSounds();

    /// Play a sound effect
    void playSound(msgSoundEvent_e);

public:
    void sendMessage(msg_t);
    explicit SoundControl_c(messaging::PostOffice_c*);
};

} // trailblazer::audio