#pragma once

#include <memory>
#include <trailblazer/game/gameconfig.hpp>

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/pipeline_bkg.hpp>


namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Draws the background image of the scene
//
/// Inherits from MessageRecipient_i:
/// Receives the msgRedrawTrigger_s message from Game Scene

class BackgroundDrawer_c : public messaging::MessageRecipient_i
{
public:
    enum class FadeInEnabled_e : bool
    {
        NO = false,
        YES = true
    };

private:
    /// Alpha value passed to the shader uniform interface
    float Alpha;

    std::unique_ptr<trailblazer::pipelines::BackgroundPipeline_c> PipelinePtr;

public:
    /// Provides a nice fade-in animation for the title screen
    void FadeIn(float duration_seconds);

    /// We have to call a setup explicitly, where we need to specify the image
    /// because the order of subscriptions matters in Game_c. If we create and subscribe
    /// Background after we know the file name from the Map object, the background will
    /// be drawed over the map which will ultimately hide it.
    void setup(std::string fileName);

    void sendMessage(msg_t) override;

    /// If fade-in is enabled, the background pipeline's alpha uniform
    /// will have an initial value of 0.F, so initially the image won't be
    /// displayed, until FadeIn function gradually increases this value
    explicit BackgroundDrawer_c(messaging::PostOffice_c*, FadeInEnabled_e);
};

} // namespace trailblazer::presentation