#pragma once

#include <any>


namespace messaging
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Interface for message recipient/sender classes.

/// Forward declare for pointer type
class PostOffice_c;

class MessageRecipient_i
{
protected:
    /// convenient alias, represents a message of any type
    using msg_t = std::any;

    /// Pointer to the Post Office (so the child classes can
    /// call subscribeRecipient and broadcastMessage)
    PostOffice_c* PO;


    /// Test if the actual message if of the given type
    template<typename MessageType>
    inline bool isMessageType(msg_t message)
    {
        return (message.type() == typeid(MessageType));
    }

    /// Wrapper for any_cast for more readable code when
    /// dealing with messages
    template<typename MessageType>
    inline MessageType msg_cast(msg_t message)
    {
        return (std::any_cast<MessageType>(message));
    }

public:
    /// This function shall handle the received messages
    /// with the helper functions above
    virtual void sendMessage(msg_t) = 0;

    /// Constructor, sets the PO address
    MessageRecipient_i(PostOffice_c* postOfficeAddress) :
        PO(postOfficeAddress)
    {
    }

    /// This is only a declaration, as the definition needs
    /// PostOffice header to be included, as the destructor
    /// calls the unsubscribe function
    ~MessageRecipient_i();
};

} // namespace messaging