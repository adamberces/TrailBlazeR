#pragma once

#include <any>


namespace trailblazer::messaging
{

class PostOffice_c;

/*
class MessageProvider_i
{
public:
    virtual void sendMessage(std::any) = 0;
};*/

class MessageRecipient_i
{
protected:
    PostOffice_c* PO;

public:
    virtual void sendMessage(std::any) = 0;

    MessageRecipient_i(PostOffice_c* postOfficeAddress) :
        PO(postOfficeAddress)
    {
    }
};

} // namespace trailblazer::messaging