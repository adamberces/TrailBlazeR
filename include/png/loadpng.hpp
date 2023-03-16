#pragma once

#include <string>


namespace png
{
    
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