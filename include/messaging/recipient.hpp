#pragma once

#include <any>


namespace messaging
{

class PostOffice_c;

class MessageRecipient_i
{
protected:
    PostOffice_c* PO;

    template<typename MessageType>
    inline bool isMessageType(std::any message)
    {
        return (message.type() == typeid(MessageType));
    }

public:
    virtual void sendMessage(std::any) = 0;

    MessageRecipient_i(PostOffice_c* postOfficeAddress) :
        PO(postOfficeAddress)
    {
    }
};

} // namespace messaging