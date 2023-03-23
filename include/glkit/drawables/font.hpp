#pragma once

#include <string>
#include <unordered_map>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
// Represents a character in a character set,
// bound to an OpenGL texture 

struct Character_s
{
    int Width;
    int Height;
    int XOffset;
    int YOffset;
    int XAdvance;

    unsigned int TextureId;
};

/////////////////////////////////////////////////////////////////////////////////////////
// The constuctor loads a font bitmap with it's FNT descriptor file,
// crops the image to individual images of characters and creates OpenGL
// textures from them. The characters are stored in a map which can be used to
// access the texture IDs and the characters' geometrical properties

class Font_c 
{
    std::unordered_map<char, Character_s> Characters;

    void loadFont(std::string fileName);

public:
    inline decltype(Characters) const& characters() const
    {
        return Characters;
    }

    Font_c(std::string fileName);
};

} // namespace glkit::drawables