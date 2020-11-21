//
//  Texture.h
//  Tuzzi
//
//  Created by Lyn on 2020/5/25.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_GRAPHICS_TEXTURE_H_
#define _TUZZI_GRAPHICS_TEXTURE_H_

#include "Object.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

enum class TextureFormat
{
    None,
    R8,
    RGB888,
    RGBA8888,
};

enum class FilterMode
{
    None = -1,
    Nearest,
    Linear,
};

enum class WrapMode
{
    None = -1,
    Repeat,
    ClampToEdge,
    Mirror,
    Border,
};

using TextureHandle = void *;

class Texture : public Object
{
public:
    static SharedPtr<Texture> loadTexture2DFromFile(const String& path,
                                                    FilterMode filter_mode,
                                                    WrapMode wrap_mode,
                                                    bool gen_mipmap);
    
    static SharedPtr<Texture> createTexture2DFromMemory(const ByteBuffer& pixels,
                                                        int width,
                                                        int height,
                                                        TextureFormat format,
                                                        FilterMode filter_mode,
                                                        WrapMode wrap_mode,
                                                        bool gen_mipmap);
    
    static SharedPtr<Texture> createTexture2D(int width,
                                              int height,
                                              TextureFormat format,
                                              FilterMode filter_mode,
                                              WrapMode wrap_mode,
                                              bool mipmap);
    
    static SharedPtr<Texture> createTextureFromHandle(int width,
                                                      int height,
                                                      TextureHandle handle,
                                                      TextureFormat format,
                                                      FilterMode filter_mode,
                                                      WrapMode wrap_mode,
                                                      bool mipmap);
    
    virtual ~Texture();
    
    void updateTexture(const ByteBuffer& pixels, int layer, int level, int x, int y, int w, int h);
    
    void genMipmaps();
    
    int getWidth() const { return m_width; }
    
    int getHeight() const { return m_height; }
    
    int getMipmapLevelCount() const { return m_mipmap_level_count; }
    
    int getArraySize() const { return m_array_size; }
    
    FilterMode getFilterMode() const { return m_filter_mode; }
    
    WrapMode getWrapMode() const { return m_wrap_mode; }
    
    TextureHandle getHandle() const { return m_handle; }

private:
    Texture();
    
private:
    int m_width;
    int m_height;
    int m_mipmap_level_count;
    int m_array_size;
    TextureFormat m_format;
    FilterMode m_filter_mode;
    WrapMode m_wrap_mode;
    TextureHandle m_handle;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Texture_h */
