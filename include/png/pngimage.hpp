#pragma once

#include <string>


namespace png
{

/////////////////////////////////////////////////////////////////////////////////////////
// Class for loading and handling PNG images using the official PNG reference library.
// Designed from the original C code examples, but according to the RAII pattern,
// so the resources are automatically freed up when the object is out of scope.
    
class PngImage_c
{
    int Width;
    int Height;
    bool HasAlpha;
    unsigned char* Data;

    bool loadPNG(std::string fileName);

public:
    inline int width() const
    {
        return Width;
    }

    inline int height() const
    {
        return Height;
    }

    inline bool hasAlpha() const
    {
        return HasAlpha;
    }

    inline unsigned char* data() const
    {
        return Data;
    }

    explicit PngImage_c(std::string fileName);

    ~PngImage_c();
};

} // namespace png