#pragma once

#include <list>
#include <unordered_map>
#include <typeindex>
#include <iostream>
#include <game/messaging/recipient.hpp>


namespace trailblazer::messaging
{

class PostOffice_c
{
    std::unordered_map<std::type_index, std::list<MessageRecipient_i*>> Recipients;

public:
    template <typename MessageType>
    void subscribeRecipient(MessageRecipient_i* r)
    {
        std::cout << "New subscriber to type " << typeid(MessageType).name() << ": " << r << std::endl;
        Recipients[ std::type_index(typeid(MessageType)) ].push_back(r);
    }

    template <typename MessageType>
    void broadcastMessage(MessageType message)
    {
        for (auto& r : Recipients[ std::type_index(typeid(MessageType)) ])
        {
            r->sendMessage(message);
        }
    }
};

} // namespace trailblazer::messaging