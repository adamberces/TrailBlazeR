#pragma once

#include <string>
#include <glkit/drawables/glkdrawable.hpp>
#include <glkit/drawables/font.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
/// Text objects are the most special case for GLKDrawable_i, as it holds a Dynamic VAO
/// and also not one, but many OpenGL textures (in a Font_c object).
/// Also the draw method is not trivial, as it is not only just controlled by uniforms,
/// but has an API where the user has to specify the text to be drawn. Also a main difference
/// compared to other drawables that it draws not just one, but many individual quads,
/// based on the number of characters to be drawn. I've been thinking of creating a class
/// representing a quad (which could be used with the Background drawable too), but for the sake
/// of brevity I have created this special class instead, trying to use as much from the base
/// class as possible, but it might need refactor in the future.

class GLKText_c : public drawables::GLKDrawable_i
{      
    Font_c Font;

    void drawCharacter(const Character_s& ch, float x, float y) const;

public:
    void drawText(std::string text, int x, int y) const;
    GLKText_c(std::string fontFileName);
};

} // namespace glkit::drawables
