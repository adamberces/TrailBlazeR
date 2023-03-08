#pragma once

#include <game/messaging/message.hpp>


namespace trailblazer::messaging
{

class Recipient_i
{
public:
    virtual void update(const Message_s&) const = 0;
};

} // namespace trailblazer::messaging