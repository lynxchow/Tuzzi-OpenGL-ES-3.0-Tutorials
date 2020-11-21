//
//  ByteBuffer.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/5/6.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "memory/ByteBuffer.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

ByteBuffer::ByteBuffer(int size):
    m_size(size),
    m_bytes(nullptr),
    m_weak_ref(false)
{
    if (m_size > 0)
    {
        m_ref_count = MakeShared<bool>(true);
        m_bytes = (byte *) malloc(m_size);
    }
    else
    {
        m_size = 0;
    }
}

ByteBuffer::ByteBuffer(const ByteBuffer& buffer)
{
    m_size = buffer.m_size;
    m_bytes = buffer.m_bytes;
    m_ref_count = buffer.m_ref_count;
    m_weak_ref = buffer.m_weak_ref;
}

ByteBuffer::ByteBuffer(byte* bytes, int size):
    m_size(size),
    m_bytes(bytes),
    m_weak_ref(true)
{
}

ByteBuffer& ByteBuffer::operator =(const ByteBuffer& buffer)
{
    free();

    m_size = buffer.m_size;
    m_bytes = buffer.m_bytes;
    m_ref_count = buffer.m_ref_count;
    m_weak_ref = buffer.m_weak_ref;

    return *this;
}

ByteBuffer::~ByteBuffer()
{
    free();
}

void ByteBuffer::free()
{
    if (!m_weak_ref)
    {
        if (m_ref_count && m_ref_count.use_count() == 1)
        {
            if (m_bytes != nullptr)
            {
                ::free(m_bytes);
            }
        }
    }
}

byte* ByteBuffer::bytes() const
{
    return m_bytes;
}

int ByteBuffer::size() const
{
    return m_size;
}

byte& ByteBuffer::operator [](int index)
{
    return m_bytes[index];
}

const byte& ByteBuffer::operator [](int index) const
{
    return m_bytes[index];
}

NAMESPACE_TUZZI_ENGINE_END
