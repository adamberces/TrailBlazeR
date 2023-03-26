#pragma once

#include <memory>

#include <glkit/core/shaders/shaderprogram.hpp>
#include <glkit/core/uniforms/uniformiface.hpp>

#include <glkit/functors/camera.hpp>
#include <glkit/functors/model.hpp>
#include <glkit/functors/perspective.hpp>
#include <glkit/functors/color.hpp>
#include <glkit/functors/lightningposition.hpp>

#include <glkit/drawables/glkcube.hpp>
#include <glkit/drawables/glksphere.hpp>


namespace trailblazer::pipelines
{

class RenderPipeline_i
{
public:
    /// The static members here are the so-called "global" uniform variables.
    /// Of source in a shader program all uniforms are global in a sense,
    /// but these are the ones which shall hold the same value for every 3D mesh
    /// when rendering a frame (or some of them even for every frame of a scene).
    /// For that reason they are declared as static to be shared among all 
    /// child classes of RenderPipeline_i, and also they can be set from anywhere
    /// without actually instantiating any of them
    
    static glkit::functors::ProjectionConfig_s ProjectionConfig;
    static glkit::functors::CameraConfig_s CameraConfig;
    
    static glkit::functors::ColorConfig_s LightningColorConfig;
    static glkit::functors::LightningPositionConfig_s LightningPositionConfig;
    static glkit::functors::LightningPositionConfig_s CameraPositionConfig;
    
    glkit::functors::ModelConfig_s ModelConfig;
    glkit::functors::ColorConfig_s ModelColorConfig;

protected:
    glkit::core::shaders::ShaderSourceList_s SSL;
    
    std::unique_ptr<glkit::drawables::GLKDrawable_i> Mesh;
    std::unique_ptr<glkit::core::shaders::ShaderProgram_c> ShaderProgram;
    std::unique_ptr<glkit::core::uniforms::ShaderUniformInterface_c> Uniforms;
    
    /// The logic which of creating a unique_ptr to a GLKDrawable_i child class
    /// shall be defined here
    virtual void constructMesh() = 0;

    /// The logic of filling the ShaderSourceList struct with GLSL source file paths
    /// shall be defined here. Vertex and fragment shader is mandatory in the OpenGL
    /// core profile, GLKit API supports also geometry and tesselation shader
    virtual void setupSSL() = 0;

public:
    /// Updates all the global and mesh uniforms with the config values and redraws the mesh
    void run();

    /// Shader program compilation happens here and also calls constructMesh
    void setup();
};

} //trailblazer::pipelines