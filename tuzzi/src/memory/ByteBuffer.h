//
//  ByteBuffer.h
//  Tuzzi
//
//  Created by Lyn on 2020/5/6.
//  Copyright © 2020 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_BYTE_BUFFER_H_
#define _TUZZI_BYTE_BUFFER_H_

#include "Common.h"
#include "SharedPtr.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

typedef unsigned char byte;

class ByteBuffer
{
public:
    ByteBuffer(int size = 0);
    ByteBuffer(const ByteBuffer& buffer);
    ByteBuffer(byte* bytes, int size);
    ~ByteBuffer();

    byte* bytes() const;
    int size() const;

    ByteBuffer& operator =(const ByteBuffer& buffer);
    byte& operator [](int index);
    const byte& operator [](int index) const;

private:
    void free();

    int m_size;
    byte* m_bytes;
    SharedPtr<bool> m_ref_count;
    bool m_weak_ref;
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* ByteBuffer_h */
