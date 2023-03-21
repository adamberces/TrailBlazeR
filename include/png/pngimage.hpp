#pragma once

#include <string>
#include <memory>


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
    std::string FileName;

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

    std::shared_ptr<PngImage_c> crop(int x, int y, int w, int h) const;

    explicit PngImage_c(std::string fileName);

    explicit PngImage_c();

    ~PngImage_c();
};

} // namespace png