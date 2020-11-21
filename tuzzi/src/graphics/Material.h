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
#include "math/Color.h"
#include "math/Matrix4x4f.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "container/Vector.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class Material : public Object
{
public:
    Material(const SharedPtr<Shader>& shader);
    virtual ~Material();
    
    const Matrix4x4f* getMatrix(const String& name) const;
    void setMatrix(const String& name, const Matrix4x4f& value);
    const Vector4f* getVector(const String& name) const;
    void setVector(const String& name, const Vector4f& value);
    void setColor(const String& name, const Color& value);
    void setFloat(const String& name, float value);
    void setInt(const String& name, int value);
    SharedPtr<Texture> getTexture(const String& name) const;
    void setTexture(const String& name, const SharedPtr<Texture>& texture);
    void setVectorArray(const String& name, const Vector<Vector4f>& array);
    void setMatrixArray(const String& name, const Vector<Matrix4x4f>& array);
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Material_h */
