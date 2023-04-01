#include <messaging/recipient.hpp>
#include <messaging/postoffice.hpp>


namespace messaging
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for MessageRecipient_i
//
// This one is defined here as it needs the full class declaration of PostOffice
// to be able to call unsubscribeRecipient

MessageRecipient_i::~MessageRecipient_i()
{
    PO->unsubscribeRecipient(this);
}

} // namespace messaging