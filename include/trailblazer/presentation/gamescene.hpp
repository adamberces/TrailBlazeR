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
// Provides the msgRedrawTrigger_s message, which causes the redraw of the scene's 3D elements
// Receives the msgBallPosition_s message, from which it updates the global uniform variables


// Import RenderPipeline_i to current namespace 
// as it is used all the time in the class
using pipelines::RenderPipeline_i;

class GameScene_c : public messaging::MessageRecipient_i
{
    // Updates the shader uniforms used in the scene
    // (camera and lightning) to follow the movement of the ball.
    // Of course per definition, all uniforms are globals in the
    // shader programs, but we make distinction in the RenderPipeline 
    // interface between the uniform variables which are used with 
    // the same values when rendering all meshes on the scene
    // and they are called as "globals" here
    void updateGlobals(glkit::functors::point3d_t ballPos);

    // Get the msgBallPosition_s message, then call updateGlobals
    void sendMessage(msg_t m) override;

public:
    // Setup the uniforms of the render pipeline, which won't change
    // during the lifetime of the scene: projection matrix, lightning color
    void setup(glkit::functors::rgb_t lightColor);

    GameScene_c(messaging::PostOffice_c* po, glkit::functors::rgb_t lightColor);
};

} // namespace trailblazer::presentation