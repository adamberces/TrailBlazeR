#pragma once

#include <list>
#include <unordered_map>
#include <typeindex>
#include <memory>

#include <game/messaging/message.hpp>
#include <game/messaging/recipient.hpp>


namespace trailblazer::messaging
{

class PostOffice_c
{
    std::unordered_map<std::type_index, std::list<std::shared_ptr<Recipient_i>>> Recipients;

    void broadcast(const Message_s& message) const
    {
        for (auto r : Recipients)
        {
            r->update(message);
        }
    }

public:
    template <typename MessageType>--
    void subscribeRecipient(const std::shared_ptr<Recipient_i>& r, )
    {
        Recipients.push_back(r);
    }

    void setMessage(const Message_s& message) const
    {
        broadcast(message);
    }
};

} // namespace trailblazer::messaging