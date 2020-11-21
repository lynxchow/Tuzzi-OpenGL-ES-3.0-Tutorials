//
//  Texture.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/5/25.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "graphics/Texture.h"
#include "image/Image.h"
#include "gl/gl.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Texture::Texture():
    m_width(0),
    m_height(0),
    m_mipmap_level_count(0),
    m_array_size(0),
    m_format(TextureFormat::None),
    m_filter_mode(FilterMode::None),
    m_wrap_mode(WrapMode::None),
    m_handle(new GLuint(0))
{
    
}

Texture::~Texture()
{
    GLuint texture_id = *static_cast<GLuint *>(m_handle);
    if (texture_id != 0)
    {
        glDeleteTextures(1, &texture_id);
    }
    
    delete static_cast<GLuint *>(m_handle);
}

SharedPtr<Texture> Texture::loadTexture2DFromFile(
    const String& path,
    FilterMode filter_mode,
    WrapMode wrap_mode,
    bool gen_mipmap)
{
    SharedPtr<Texture> texture;
    
    auto image = Image::loadFromFile(path);
    if (image)
    {
        TextureFormat format;
        
        switch (image->format)
        {
            case ImageFormat::R8:
                format = TextureFormat::R8;
                break;
            case ImageFormat::RGB888:
                format = TextureFormat::RGB888;
                break;
            case ImageFormat::RGBA8888:
                format = TextureFormat::RGBA8888;
                break;
            default:
                format = TextureFormat::None;
                break;
        }
        
        if (format != TextureFormat::None)
        {
            texture = Texture::createTexture2DFromMemory(
                image->data,
                image->width,
                image->height,
                format,
                filter_mode,
                wrap_mode,
                gen_mipmap);
        }
    }
    
    return texture;
}

SharedPtr<Texture> Texture::createTexture2DFromMemory(
    const ByteBuffer& pixels,
    int width,
    int height,
    TextureFormat format,
    FilterMode filter_mode,
    WrapMode wrap_mode,
    bool gen_mipmap)
{
    SharedPtr<Texture> texture = Texture::createTexture2D(
        width,
        height,
        format,
        filter_mode,
        wrap_mode,
        gen_mipmap);
    
    texture->updateTexture(pixels, 0, 0, 0, 0, width, height);
    
    if (gen_mipmap)
    {
        texture->genMipmaps();
    }
    
    return texture;
}

SharedPtr<Texture> Texture::createTextureFromHandle(int width,
                                                    int height,
                                                    TextureHandle handle,
                                                    TextureFormat format,
                                                    FilterMode filter_mode,
                                                    WrapMode wrap_mode,
                                                    bool mipmap)
{
    SharedPtr<Texture> texture = SharedPtr<Texture>(new Texture());
    texture->m_width = width;
    texture->m_height = height;
    texture->m_array_size = 1;
    texture->m_format = format;
    texture->m_filter_mode = filter_mode;
    texture->m_wrap_mode = wrap_mode;
    texture->m_handle = handle;
    
    glBindTexture(GL_TEXTURE_2D, *static_cast<GLuint *>(texture->m_handle));
    
    switch (filter_mode)
    {
        case FilterMode::Nearest:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case FilterMode::Linear:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        default:
            break;
    }
    
    switch (wrap_mode)
    {
        case WrapMode::Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case WrapMode::ClampToEdge:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case WrapMode::Mirror:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        default:
            break;
    }

    return texture;
    
}

SharedPtr<Texture> Texture::createTexture2D(
    int width,
    int height,
    TextureFormat format,
    FilterMode filter_mode,
    WrapMode wrap_mode,
    bool mipmap)
{
    SharedPtr<Texture> texture;

    int mipmap_level_count = 1;
//    if (mipmap)
//    {
//        mipmap_level_count = (int) floor(Mathf::log2((float) Mathf::Max(width, height))) + 1;
//    }

    texture = SharedPtr<Texture>(new Texture());
    texture->m_width = width;
    texture->m_height = height;
    texture->m_mipmap_level_count = mipmap_level_count;
    texture->m_array_size = 1;
    texture->m_format = format;
    texture->m_filter_mode = filter_mode;
    texture->m_wrap_mode = wrap_mode;
    
    glGenTextures(1, static_cast<GLuint *>(texture->m_handle));
    glBindTexture(GL_TEXTURE_2D, *static_cast<GLuint *>(texture->m_handle));
    
    switch (filter_mode)
    {
        case FilterMode::Nearest:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case FilterMode::Linear:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        default:
            break;
    }
    
    switch (wrap_mode)
    {
        case WrapMode::Repeat:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case WrapMode::ClampToEdge:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case WrapMode::Mirror:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        default:
            break;
    }

    return texture;
}

void Texture::updateTexture(const ByteBuffer& pixels, int layer, int level, int x, int y, int w, int h)
{
    int format_type = 0;
    switch (m_format)
    {
        case TextureFormat::RGB888:
            format_type = GL_RGB;
            break;
        case TextureFormat::RGBA8888:
            format_type = GL_RGBA;
            break;
        default:
            break;
    }
    
    glTexImage2D(GL_TEXTURE_2D, 0, format_type, w, h, 0, format_type, GL_UNSIGNED_BYTE, pixels.bytes());
}


void Texture::genMipmaps()
{
    glGenerateMipmap(GL_TEXTURE_2D);
}

NAMESPACE_TUZZI_ENGINE_END
