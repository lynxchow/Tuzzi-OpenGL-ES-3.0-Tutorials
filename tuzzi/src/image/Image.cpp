//
//  Image.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/5/6.
//

#include "image/Image.h"
#include "io/File.h"
#include "Log.h"

extern "C"
{
#include "jpeg/jpeglib.h"
#include "png/png.h"
#include "png/pngstruct.h"
}

NAMESPACE_TUZZI_ENGINE_BEGIN

struct PNGData
{
    char* buffer;
    int size;
};

SharedPtr<Image> Image::loadFromFile(const String& path)
{
    SharedPtr<Image> image;
    
    if (File::exist(path))
    {
        if (path.endsWith(".png"))
        {
            ByteBuffer png = File::readAllBytes(path);
            image = Image::loadPNG(png);
        }
        else if (path.endsWith(".jpg"))
        {
            ByteBuffer jpg = File::readAllBytes(path);
            image = Image::loadJPEG(jpg);
        }
        else
        {
            assert(!"image file format not support");
        }
    }
    else
    {
        TZ_LOGI("IMAGE" ,"image file not exist: %s", path.str());
    }
    
    return image;
}

SharedPtr<Image> Image::loadJPEG(const ByteBuffer& jpeg)
{
    SharedPtr<Image> image = MakeShared<Image>();

    //use lib jpeg
    jpeg_decompress_struct cinfo;
    jpeg_error_mgr jerr;
    JSAMPARRAY buffer;        /* Output row buffer */
    int row_stride;        /* physical row width in output buffer */

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    jpeg_mem_src(&cinfo, jpeg.bytes(), jpeg.size());
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)
        ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    image->width = cinfo.output_width;
    image->height = cinfo.output_height;
    int bpp = cinfo.output_components * 8;
    switch (bpp)
    {
        case 8:
            image->format = ImageFormat::R8;
            break;
        case 24:
            image->format = ImageFormat::R8G8B8;
            break;
        case 32:
            image->format = ImageFormat::R8G8B8A8;
            break;
    }

    image->data = ByteBuffer(image->width * image->height * cinfo.output_components);

    unsigned char* pPixel = image->data.bytes();

    while (cinfo.output_scanline < cinfo.output_height)
    {
        jpeg_read_scanlines(&cinfo, buffer, 1);

        unsigned char *pixel_data = buffer[0];

        for (int j = 0; j < image->width; ++j)
        {
            memcpy(pPixel, pixel_data, cinfo.output_components);

            pPixel += cinfo.output_components;
            pixel_data += cinfo.output_components;
        }
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return image;
}

static void PngRead(png_structp png_ptr, png_bytep data, png_size_t length)
{
    memcpy(data, png_ptr->io_ptr, length);
    png_ptr->io_ptr = (char*) png_ptr->io_ptr + length;
}

static void PngWrite(png_structp png_ptr, png_bytep data, png_size_t length)
{
    PNGData* png = (PNGData*) png_get_io_ptr(png_ptr);

    if (png->buffer == nullptr)
    {
        png->buffer = (char*) malloc(length);
    }
    else
    {
        png->buffer = (char*) realloc(png->buffer, png->size + length);
    }

    memcpy(&png->buffer[png->size], data, length);
    png->size += (int) length;
}

static void PngFlush(png_structp png_ptr)
{

}

SharedPtr<Image> Image::loadPNG(const ByteBuffer& png)
{
    SharedPtr<Image> image = MakeShared<Image>();

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    setjmp(png_jmpbuf(png_ptr));

    png_set_read_fn(png_ptr, png.bytes(), PngRead);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

    image->width = png_get_image_width(png_ptr, info_ptr);
    image->height = png_get_image_height(png_ptr, info_ptr);

    int color_type = png_get_color_type(png_ptr, info_ptr);
    if (color_type == PNG_COLOR_TYPE_RGBA)
    {
        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

        image->data = ByteBuffer(image->width * image->height * 4);
        image->format = ImageFormat::R8G8B8A8;

        unsigned char* pPixel = image->data.bytes();

        for (int i = 0; i < image->height; ++i)
        {
            memcpy(pPixel, row_pointers[i], image->width * 4);
            pPixel += image->width * 4;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_RGB)
    {
        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

        image->data = ByteBuffer(image->width * image->height * 3);
        image->format = ImageFormat::R8G8B8;

        unsigned char* pPixel = image->data.bytes();

        for (int i = 0; i < image->height; ++i)
        {
            memcpy(pPixel, row_pointers[i], image->width * 3);
            pPixel += image->width * 3;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_GRAY)
    {
        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

        image->data = ByteBuffer(image->width * image->height);
        image->format = ImageFormat::R8;

        unsigned char* pPixel = image->data.bytes();

        for (int i = 0; i < image->height; ++i)
        {
            memcpy(pPixel, row_pointers[i], image->width * 1);
            pPixel += image->width * 1;
        }
    }
    else if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

        image->data = ByteBuffer(image->width * image->height * 4);
        image->format = ImageFormat::R8G8B8A8;

        byte* pPixel = image->data.bytes();

        for (int i = 0; i < image->height; ++i)
        {
            for (int j = 0; j < image->width; ++j)
            {
                png_byte g = row_pointers[i][j * 2];
                png_byte a = row_pointers[i][j * 2 + 1];
                pPixel[0] = g;
                pPixel[1] = g;
                pPixel[2] = g;
                pPixel[3] = a;

                pPixel += 4;
            }
        }
    }
    else
    {
        assert(!"color type not support");
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, 0);

    return image;
}

void Image::encodeToPNG(const String& file)
{
    int color_type = -1;
    int bpp;
    switch (this->format)
    {
        case ImageFormat::R8G8B8A8:
            color_type = PNG_COLOR_TYPE_RGBA;
            bpp = 32;
            break;
        case ImageFormat::R8G8B8:
            color_type = PNG_COLOR_TYPE_RGB;
            bpp = 24;
            break;
        case ImageFormat::R8:
            color_type = PNG_COLOR_TYPE_GRAY;
            bpp = 8;
            break;
        default:
            return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    setjmp(png_jmpbuf(png_ptr));

    PNGData png_data;
    png_data.buffer = 0;
    png_data.size = 0;

    png_set_write_fn(png_ptr, &png_data, PngWrite, PngFlush);

    png_set_IHDR(png_ptr, info_ptr, width, height,
        8, color_type, PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);

    png_bytepp row_pointers = new png_bytep[height];
    for (int i = 0; i < height; ++i)
    {
        row_pointers[i] = (png_bytep) &this->data[i * width * bpp / 8];
    }
    png_write_image(png_ptr, row_pointers);
    delete[] row_pointers;

    png_write_end(png_ptr, 0);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    char* data = png_data.buffer;
    int size = png_data.size;

    ByteBuffer file_buffer(size);
    memcpy(file_buffer.bytes(), data, size);

    File::writeAllBytes(file, file_buffer);

    free(data);
}

NAMESPACE_TUZZI_ENGINE_END
