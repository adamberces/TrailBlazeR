#pragma once

#include <messaging/postoffice.hpp>
#include <messaging/recipient.hpp>
#include <trailblazer/game/messagetypes.hpp>

#include <trailblazer/pipelines/renderpipeline.hpp>
#include <trailblazer/pipelines/pipeline_bkg.hpp>
#include <trailblazer/pipelines/pipeline_text.hpp>

namespace trailblazer::presentation
{

/////////////////////////////////////////////////////////////////////////////////////////
// Represents the main game window.
//
// Inherits from MessageRecipient_i:
// Provides the msgRedrawTrigger message, which causes the redraw of the scene's 3D elements
// Receives the msgBallPosition message, from which it updates the global uniform variables


// Import RenderPipeline_i to current namespace 
// as it is used all the time in the class
using pipelines::RenderPipeline_i;

class GameScene_c : public messaging::MessageRecipient_i
{
    std::unique_ptr<pipelines::TextPipeline_c> TestText;

    // The background drawer pipeline object is owned by the scene
    // the rest of the objects (ball, tiles) are independent
    // and redrawn on the msgRedrawTrigger message
    std::unique_ptr<pipelines::BackgroundPipeline_c> Background;

    // Updates the shader uniforms used in the scene
    // (camera and lightning) to follow the movement of the ball.
    // Of course per definition, all uniforms are globals in the
    // shader programs, but we make distinction in the RenderPipeline 
    // interface between the uniform variables which are used with 
    // the same values when rendering all meshes on the scene
    // and they are called as "globals" here
    void updateGlobals(glkit::functors::point3d_t ballPos);

    // Get the msgBallPosition message, then call updateGlobals
    void sendMessage(msg_t m) override;

public:
    // Redraw the scene and send redraw trigger to ball and map tiles
    void drawScene();

    // Setup the uniforms of the render pipeline, which won't change
    // during the lifetime of the scene: projection matrix, lightning color
    void setup();

    GameScene_c(messaging::PostOffice_c* po);
};

} // namespace trailblazer::presentation