#pragma once

#include <list>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <messaging/recipient.hpp>


namespace messaging
{

/////////////////////////////////////////////////////////////////////////////////////////
// This small framework realizes the Observer pattern (with a little twist).
// It serves as the core event handling mechanism of the Trailblazer game, which helps
// much in decreasing the coupling between the classes which drives the game's specific parts.
// 
// Most classes inherits from MessageRecipient_i and so they can subscribe to messages of
// specific types. PostOffice is the main facility for routing these messages.
// If a new message is broadcasted by one of the Recipients it is sent to every
// other Recipient which has been previously subscribed.
//
// Thanks to this mechanism all components which is needed to realize such a complex SW
// as a video game are only need to know the message types they need to handle/send
// and does not needs any pointers, references &c. of other classes so they can be
// as independent from each other as possible.
//
// This class is also incorporates the power of templates and std::any
// for a concise and expressive syntax and compile time type safety.

class PostOffice_c
{
    std::unordered_map<std::type_index, std::list<MessageRecipient_i*>> Recipients;

public:
    // This function can be used by the Recipients to
    // subscribe themselves to a message of a given type
    template <typename MessageType>
    void subscribeRecipient(MessageRecipient_i* r)
    {
        std::cout << "New subscriber to type " << typeid(MessageType).name() << ": " << r << std::endl;
        Recipients[ std::type_index(typeid(MessageType)) ].push_back(r);
    }

    // Broadcast a message of a given type for all subscribers
    template <typename MessageType>
    void broadcastMessage(MessageType message)
    {
        //std::cout << "New message available of type " << typeid(MessageType).name() << std::endl;
        for (auto& r : Recipients[ std::type_index(typeid(MessageType)) ])
        {
            r->sendMessage(message);
        }
    }
    
    // Clear subscriber list, useful if the PO object needs to be reused
    void unsubscribeAll()
    {
        Recipients.clear();
    }
};

} // namespace messaging