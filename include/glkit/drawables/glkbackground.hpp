#pragma once

#include <string>
#include <glkit/drawables/glkdrawable.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
/// A background object is basically a special case of a a fixed, 2D rectangle (aka. quad)
/// to be rendered behind the whole scene.

class GLKBackground_c : public drawables::GLKDrawable_i
{      
    GLuint TextureID;
    std::string FileName;

public:
    void activateTexture() const;
    void draw() const override;

private:
    std::pair<GLKDrawable_i::vertex_vector_t,
        GLKDrawable_i::element_vector_t> constructVertexData();

    virtual void initialize(const vertex_vector_t&,
        const element_vector_t&) override;

public:
    GLKBackground_c(std::string fileName);
};

} // namespace glkit::drawables
