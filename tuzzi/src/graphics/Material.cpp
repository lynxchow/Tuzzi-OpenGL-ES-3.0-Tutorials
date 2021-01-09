//
//  Material.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/11/20.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "Material.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

Material::Material(const SharedPtr<Shader>& shader) : m_shader(shader)
{
    
}

Material::~Material()
{
    
}

const Matrix4x4f* Material::getMatrix(const String& name) const
{
    return this->getProperty<Matrix4x4f>(name, MaterialProperty::Type::Matrix);
}

void Material::setMatrix(const String& name, const Matrix4x4f& value)
{
    this->setProperty(name, value, MaterialProperty::Type::Matrix);
}

const Vector4f* Material::getVector(const String& name) const
{
    return this->getProperty<Vector4f>(name, MaterialProperty::Type::Vector);
}

void Material::setVector(const String& name, const Vector4f& value)
{
    this->setProperty(name, value, MaterialProperty::Type::Vector);
}

void Material::setColor(const String& name, const Color& value)
{
    this->setProperty(name, value, MaterialProperty::Type::Color);
}

void Material::setFloat(const String& name, float value)
{
    this->setProperty(name, value, MaterialProperty::Type::Float);
}

void Material::setInt(const String& name, int value)
{
    this->setProperty(name, value, MaterialProperty::Type::Int);
}

SharedPtr<Texture> Material::getTexture(const String& name) const
{
    auto it = m_properties.find(name);
    if (it != m_properties.end())
    {
        const MaterialProperty *property_ptr = &it->second;
        if (property_ptr->type == MaterialProperty::Type::Texture)
        {
            return property_ptr->texture;
        }
    }
    
    return nullptr;
}

void Material::setTexture(const String& name, const SharedPtr<Texture>& texture)
{
    auto it = m_properties.find(name);
    if (it != m_properties.end())
    {
        MaterialProperty *property_ptr = &it->second;
        property_ptr->type = MaterialProperty::Type::Texture;
        property_ptr->texture = texture;
        property_ptr->dirty = true;
    }
    else
    {
        MaterialProperty property;
        property.name = name;
        property.type = MaterialProperty::Type::Texture;
        property.texture = texture;
        property.dirty = true;
        m_properties[name] = property;
    }
}

void Material::prepare()
{
    
    
}

void Material::updateUniformMember(const String& name, const void* data, int size)
{
    
}

void Material::updateUniformTexture(const String& name, const SharedPtr<Texture>& texture)
{
    
}

NAMESPACE_TUZZI_ENGINE_END
