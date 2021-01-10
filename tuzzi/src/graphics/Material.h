//
//  Material.h
//  Tuzzi
//
//  Created by Lyn on 2020/11/20.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_GRAPHICS_MATERIAL_H_
#define _TUZZI_GRAPHICS_MATERIAL_H_

#include "Object.h"
#include "math/Math.h"
#include "math/Matrix4x4f.h"
#include "graphics/Color.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "container/Vector.h"
#include "container/Map.h"
#include "string/String.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

struct MaterialProperty
{
    enum class Type
    {
        Color,
        Vector,
        Float,
        Texture,
        Matrix,
        Int,
    };
    
    union Data
    {
        float matrix[16];
        float vector[4];
        float color[4];
        float float_value;
        int int_value;
    };
    
    String name;
    Type type;
    Data data;
    SharedPtr<Texture> texture;
    int size = 0;
    bool dirty;
};

class Material : public Object
{
public:
    Material(const SharedPtr<Shader>& shader);
    virtual ~Material();
    const Matrix4x4f* getMatrix(const String& name) const;
    void setMatrix(const String& name, const Matrix4x4f& value);
    const Vector4f *getVector(const String& name) const;
    void setVector(const String& name, const Vector4f& value);
    void setColor(const String& name, const Color& value);
    void setFloat(const String& name, float value);
    void setInt(const String& name, int value);
    SharedPtr<Texture> getTexture(const String& name) const;
    void setTexture(const String& name, const SharedPtr<Texture>& texture);
    void prepare();
    
private:
    template <class T>
    const T *getProperty(const String& name, MaterialProperty::Type type) const
    {
        auto it = m_properties.find(name);
        if (it != m_properties.end())
        {
            const MaterialProperty *property_ptr = &it->second;
            if (property_ptr->type == type)
            {
                return (const T*) &property_ptr->data;
            }
        }
        
        return nullptr;
    }
    
    template <class T>
    void setProperty(const String& name, const T& value, MaterialProperty::Type type)
    {
        auto it = m_properties.find(name);
        if (it != m_properties.end())
        {
            MaterialProperty *property_ptr = &it->second;
            property_ptr->type = type;
            memcpy(&property_ptr->data, &value, sizeof(value));
            property_ptr->dirty = true;
        }
        else
        {
            MaterialProperty property;
            property.name = name;
            property.type = type;
            memcpy(&property.data, &value, sizeof(value));
            property.size = sizeof(value);
            property.dirty = true;
            m_properties[name] = property;
        }
    }
    
    Map<String, MaterialProperty> m_properties;
    SharedPtr<Shader> m_shader;
};

NAMESPACE_TUZZI_ENGINE_END



#endif /* Material_h */
