#pragma once

#include <png/pngimage.hpp>

#include <glkit/core/ogl_headers.hpp>
#include <glkit/drawables/font.hpp>


namespace glkit::drawables
{

/////////////////////////////////////////////////////////////////////////////////////////
// Implementation for Font_c

void Font_c::loadFont(std::string fileName)
{
    png::PngImage_c im(fileName + ".png");

    FILE *f;
    std::string fntFile = fileName + ".fnt";
    f = fopen(fntFile.c_str(), "r");

    int n;
    fscanf(f, "chars count=%d\n", &n);
    for (int i = 0; i < n; i++)
    {
        int x;
        int y;
        int Id;
        Character_s c;
        fscanf(f, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d\n",
            &Id, &x, &y, &(c.Width), &(c.Height), &(c.XOffset), &(c.YOffset), &(c.XAdvance));

        auto cropped = im.crop(x, y, c.Width, c.Height);

        // generate texture
        glGenTextures(1, &(c.TextureId));
        glBindTexture(GL_TEXTURE_2D, c.TextureId);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            (cropped->hasAlpha() ? GL_RGBA : GL_RGB),
            c.Width,
            c.Height,
            0,
            (cropped->hasAlpha() ? GL_RGBA : GL_RGB),
            GL_UNSIGNED_BYTE,
            cropped->data()
        );

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        Characters[Id] = c;
    }
}

Font_c::Font_c(std::string fileName)
{
    loadFont(fileName);
}

} // glkit::window