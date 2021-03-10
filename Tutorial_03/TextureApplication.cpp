//
//  TextureApplication.cpp
//  TuzziApp
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "TextureApplication.h"
#include "Tuzzi.h"
#include "gl/gl.h"
#include "graphics/Texture.h"
#include "ResourceManager.h"
#include "math/Math.h"

NAMESPACE_TUZZI_ENGINE_USING

TextureApplication::TextureApplication()
{
    
}

TextureApplication::~TextureApplication()
{
    
}

void TextureApplication::onInit()
{
    SharedPtr<Shader> shader = getTuzzi()->getResourceManager()->loadShader("shader/texture.vert", "shader/texture.frag");
    m_material = MakeShared<Material>(shader);
    
    Vector<Vertex> vertices(4);
    vertices[0].vertex = Vector3f(0.6866f, 1.0f, 0.0f);
    vertices[1].vertex = Vector3f(0.6866f, -1.0f, 0.0f);
    vertices[2].vertex = Vector3f(-0.6866f, -1.0f, 0.0f);
    vertices[3].vertex = Vector3f(-0.6866f,  1.0f, 0.0f);
    vertices[0].uv = Vector2f(1.0f, 1.0f);
    vertices[1].uv = Vector2f(1.0f, 0.0f);
    vertices[2].uv = Vector2f(0.0f, 0.0f);
    vertices[3].uv = Vector2f(0.0f, 1.0f);
                        
    Vector<uint32_t> indices =
    {
        3, 1, 0,
        3, 2, 1
    };
    
    m_mesh = MakeShared<Mesh>(std::move(vertices), std::move(indices));
    
    m_texture_dark_magican = getTuzzi()->getResourceManager()->loadTexture("yugioh/dark_magican.png", FilterMode::Linear, WrapMode::Repeat, true);
    m_texture_dark_magican_girl = getTuzzi()->getResourceManager()->loadTexture("yugioh/dark_magican_girl.png", FilterMode::Linear, WrapMode::Repeat, true);
    m_texture_buster_blader = getTuzzi()->getResourceManager()->loadTexture("yugioh/buster_blader.png", FilterMode::Linear, WrapMode::Repeat, true);
    m_texture_exodia = getTuzzi()->getResourceManager()->loadTexture("yugioh/exodia.png", FilterMode::Linear, WrapMode::Repeat, true);
    m_texture_black_luster_soldier = getTuzzi()->getResourceManager()->loadTexture("yugioh/black_luster_soldier.png", FilterMode::Linear, WrapMode::Repeat, true);
    m_texture_kuriboh = getTuzzi()->getResourceManager()->loadTexture("yugioh/kuriboh.png", FilterMode::Linear, WrapMode::Repeat, true);
    m_texture_back_card = getTuzzi()->getResourceManager()->loadTexture("yugioh/back_card.png", FilterMode::Linear, WrapMode::Repeat, true);
}

void TextureApplication::drawCard(const Vector3f& position, const Vector3f& rotation, float speed, SharedPtr<Texture> texture)
{
    Matrix4x4f p = Matrix4x4f::perspective(45.0f, static_cast<float>(getWidth()) / getHeight(), 0.1f, 1000.0f);
    Vector3f eye = Vector3f(0.0f, 2, 10);
    Vector3f target = Vector3f(0.0f, 0.0, 2.0);
    Matrix4x4f v = Matrix4x4f::lookTo(eye, target - eye, Vector3f(0.0f, 1.0, 0.0));
    Matrix4x4f m = Matrix4x4f::rotation(Quaternionf::euler(Vector3f(0.0f, speed, 0.0f))) * Matrix4x4f::translation(position) * Matrix4x4f::rotation(Quaternionf::euler(rotation)) * Matrix4x4f::rotation(Quaternionf::euler(0.0f, 0.0f, 20.0f));

    Matrix4x4f mvp = p * v * m;
    
    m_material->setMatrix("u_MVP", mvp);
    m_material->setTexture("faceTexture", texture);
    m_material->setTexture("backTexture", m_texture_back_card);
    m_material->prepare();
    
    // 因为我们的三角形的顶点数据绑定解析已经全部配置到VAO啦
    // glBindVertexArray绑定可以将下面的绘制操作制定之前设置的三角形
    glBindVertexArray(*static_cast<GLuint *>(m_mesh->getVertexArrayHandle()));
    // 调用glDrawElements绘制方法，
    // 第一个参数代表，绘制图元是三角形，还有点，线，扇形可选择
    // 第二个参数代表需要绘制的顶点，因为我们的绘制两个三角形，所以这里要填6
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}

void TextureApplication::onUpdate()
{
    // 需要设置窗口的位置和大小，如果错误设置将会导致位置不对，或者图形的比例不对
    glViewport(0, 0, getWidth(), getHeight());
    
    // 先设置窗口的清屏颜色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // 参数传GL_COLOR_BUFFER_BIT，代表glClear清除的是颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    static float angle1 = 0.0;
    static float angle2 = 0.0;
    angle1 += 2.5;
    angle2 -= 0.5;
    
    glEnable(GL_DEPTH_TEST);
    
    float d = 4.0;
    drawCard(Vector3f(0.0f * d, 0.0f, 1.0f * d), Vector3f(0, angle1 + 0.1666*0.0, 0.0f), angle2, m_texture_dark_magican);
    
    drawCard(Vector3f(0.8660f * d, 0.0f, -0.5f * d), Vector3f(0, angle1 + 0.1666*1.0, 0.0f), angle2, m_texture_dark_magican_girl);
    
    drawCard(Vector3f(-0.8660f * d, 0.0f, -0.5f * d), Vector3f(0, angle1 + 0.1666*2.0, 0.0f), angle2, m_texture_buster_blader);
    
    drawCard(Vector3f(0.0f * d, 0.0f, -1.0f * d), Vector3f(0, angle1 + 0.1666*3.0, 0.0f), angle2, m_texture_black_luster_soldier);
    
    drawCard(Vector3f(-0.8660f * d, 0.0f, 0.5f * d), Vector3f(0, angle1 + 0.1666*4.0, 0.0f), angle2, m_texture_exodia);
    
    drawCard(Vector3f(0.8660f * d, 0.0f, 0.5f * d), Vector3f(0, angle1 + 0.1666*5.0, 0.0f), angle2, m_texture_kuriboh);
}

void TextureApplication::onDestroy()
{
    m_material = nullptr;
    m_mesh = nullptr;
}
