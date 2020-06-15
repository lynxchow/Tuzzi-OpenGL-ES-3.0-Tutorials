//
//  Image.h
//  Tuzzi
//
//  Created by Lyn on 2020/5/6.
//  Copyright © 2020 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_IMAGE_H_
#define _TUZZI_IMAGE_H_

#include "Object.h"
#include "memory/ByteBuffer.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

enum class ImageFormat
{
    None = 0,
    R8,
    R8G8B8,
    R8G8B8A8,
};

class Image : public Object
{
public:
    static SharedPtr<Image> loadFromFile(const String& path);
    static SharedPtr<Image> loadJPEG(const ByteBuffer& jpeg);
    static SharedPtr<Image> loadPNG(const ByteBuffer& png);
    void encodeToPNG(const String& file);

    int width = 0;
    int height = 0;
    ImageFormat format = ImageFormat::None;
    ByteBuffer data;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Image_h */
