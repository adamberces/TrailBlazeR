#include <trailblazer/presentation/backgrounddrawer.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// BackgroundDrawer_c implementation

void BackgroundDrawer_c::sendMessage(msg_t m)
{
    if (isMessageType<msgRedrawTrigger_s>(m))
    {
        Pipeline.run();
    }
}

BackgroundDrawer_c::BackgroundDrawer_c(messaging::PostOffice_c* po, std::string fileName) :
    MessageRecipient_i(po),
    Pipeline(fileName)
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger_s>(this);
}

} // namespace trailblazer::presentation
