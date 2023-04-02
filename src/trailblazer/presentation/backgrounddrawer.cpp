#include <trailblazer/presentation/backgrounddrawer.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// BackgroundDrawer_c implementation

void BackgroundDrawer_c::FadeIn(float duration_seconds)
{
    static int ticks = static_cast<int>(duration_seconds / GameClock_c::TimePeriodSec);
    float step = 1.F / ticks;

    if (0 < ticks--)
    {
        Alpha += step;
        PipelinePtr->AlphaConfig.Value = Alpha;
    }
}

void BackgroundDrawer_c::sendMessage(msg_t m)
{
    if (isMessageType<msgRedrawTrigger_s>(m))
    {
        PipelinePtr->run();
    }
}

void BackgroundDrawer_c::setup(std::string fileName)
{
    PipelinePtr = std::make_unique<trailblazer::pipelines::BackgroundPipeline_c>(fileName, Alpha);
}

BackgroundDrawer_c::BackgroundDrawer_c(messaging::PostOffice_c* po, FadeInEnabled_e fadeInEnabled) :
    MessageRecipient_i(po),
    Alpha((fadeInEnabled == FadeInEnabled_e::YES ? 0.F : 1.F))
{   
    // Manage subscriptions
    PO->subscribeRecipient<msgRedrawTrigger_s>(this);
}

} // namespace trailblazer::presentation
