#include <cstring>
#include <stdexcept>

#include <png.h>
#include <png/pngimage.hpp>


namespace png
{

/////////////////////////////////////////////////////////////////////////////////////////
// PngImage_c implementation

bool PngImage_c::loadPNG(std::string fileName)
{
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;

    FILE* fp;
    if ((fp = fopen(fileName.c_str(), "rb")) == NULL)
    {
        return false;
    }
        
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
    {
        fclose(fp);
        return false;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return false;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, sig_read);
    png_read_png(png_ptr, info_ptr,
        PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
        &color_type, &interlace_type, NULL, NULL);
    this->Width = width;
    this->Height = height;

    this->HasAlpha = (color_type & PNG_COLOR_MASK_ALPHA);

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    this->Data = (unsigned char*)malloc(row_bytes * this->Height);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    for (int i = 0; i < this->Height; i++)
    {
        memcpy(this->Data + (row_bytes * (this->Height - 1 - i)), row_pointers[i], row_bytes);
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);

    return true;
}

std::shared_ptr<PngImage_c> PngImage_c::crop(int x, int y, int w, int h) const
{
    std::shared_ptr<PngImage_c> cropped = std::make_shared<PngImage_c>();
    cropped->Width = w;
    cropped->Height = h;
    cropped->HasAlpha = HasAlpha;

    int bpp = (HasAlpha ? 4 : 3);
    cropped->Data = (unsigned char*)malloc(w * h * bpp);

    unsigned char* p;
    unsigned char* original_ptr = Data;
    unsigned char* cropped_ptr = cropped->Data;
    
    int stride = Width * bpp;
    int start = stride * y + x * bpp;

    for (int i = 0; i < h; i++)
    {
        p = original_ptr + start;
        start += stride;
        for (int j = 0; j < w; j++)
        {
            memcpy(cropped_ptr, p, bpp);
            cropped_ptr += bpp;
            p += bpp;
        }
    }

    return cropped;
}


PngImage_c::PngImage_c(std::string fileName)
{
    if (!loadPNG(fileName))
    {
        throw std::runtime_error("Unable to load PNG file " + fileName);
    }
}

PngImage_c::PngImage_c()
{

}

PngImage_c::~PngImage_c()
{
    free(Data);
}

} // namespace png



