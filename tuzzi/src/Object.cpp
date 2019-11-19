//
//  Object.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/7/10.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "Object.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Object::Object()
{
    static unsigned int s_uuid = 0;
    m_uuid = ++s_uuid;
}

Object::~Object()
{
    
}

const String& Object::getName() const
{
    return m_name;
}

void Object::setName(const String& name)
{
    m_name = name;
}

unsigned int Object::getUUID() const
{
    return m_uuid;
}

NAMESPACE_TUZZI_ENGINE_END
