//
//  TextureApplication.h
//  TuzziApp
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#ifndef _TEXTURE_APPLICATION_H_
#define _TEXTURE_APPLICATION_H_

#include "Application.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"

NAMESPACE_TUZZI_ENGINE_USING

class TextureApplication : public Application
{
public:
    TextureApplication();
    
    virtual ~TextureApplication();
    
private:
    virtual void onInit() override;
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    void drawCard(const Vector3f& position, const Vector3f& rotation, float speed, SharedPtr<Texture> texture);
    
    SharedPtr<Texture> m_texture_dark_magican;
    SharedPtr<Texture> m_texture_dark_magican_girl;
    SharedPtr<Texture> m_texture_buster_blader;
    SharedPtr<Texture> m_texture_exodia;
    SharedPtr<Texture> m_texture_black_luster_soldier;
    SharedPtr<Texture> m_texture_kuriboh;
    SharedPtr<Texture> m_texture_back_card;
    
    SharedPtr<Mesh> m_mesh;
    SharedPtr<Material> m_material;
};

#endif /* TextureApplication_h */
