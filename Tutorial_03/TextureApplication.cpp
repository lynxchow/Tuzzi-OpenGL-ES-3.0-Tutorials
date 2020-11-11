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

NAMESPACE_TUZZI_ENGINE_USING

TextureApplication::TextureApplication()
{
    
}

TextureApplication::~TextureApplication()
{
    
}

void TextureApplication::onInit()
{
    m_shader = getTuzzi()->getResourceManager()->loadShader("shader/texture.vert", "shader/texture.frag");
    
    Vector<Vertex> vertices(4);
    vertices[0].vertex = Vector3f(0.5f * 0.5625, 0.5f, 0.0f);
    vertices[1].vertex = Vector3f(0.5f * 0.5625, -0.5f, 0.0f);
    vertices[2].vertex = Vector3f(-0.5f * 0.5625, -0.5f, 0.0f);
    vertices[3].vertex = Vector3f(-0.5f * 0.5625,  0.5f, 0.0f);
    vertices[0].uv = Vector2f(1.0f, 1.0f);
    vertices[1].uv = Vector2f(1.0f, 0.0f);
    vertices[2].uv = Vector2f(0.0f, 0.0f);
    vertices[3].uv = Vector2f(0.0f, 1.0f);
                        
    Vector<uint32_t> indices =
    {
        0, 1, 3,
        1, 2, 3
    };
    
    m_mesh = MakeShared<Mesh>(std::move(vertices), std::move(indices));
    
    m_texture = getTuzzi()->getResourceManager()->loadTexture("image/box.jpg", FilterMode::Linear, WrapMode::Repeat, true);
}

void TextureApplication::onUpdate()
{
    // 需要设置窗口的位置和大小，如果错误设置将会导致位置不对，或者图形的比例不对
    glViewport(0, 0, getWidth(), getHeight());
    
    // 先设置窗口的清屏颜色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 参数传GL_COLOR_BUFFER_BIT，代表glClear清除的是颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    
    // 使用我们的shader
    m_shader->use();
    // 因为我们的三角形的顶点数据绑定解析已经全部配置到VAO啦
    // glBindVertexArray绑定可以将下面的绘制操作制定之前设置的三角形
    glBindVertexArray(*static_cast<GLuint *>(m_mesh->getVertexArrayHandle()));
    // 调用glDrawElements绘制方法，
    // 第一个参数代表，绘制图元是三角形，还有点，线，扇形可选择
    // 第二个参数代表需要绘制的顶点，因为我们的绘制两个三角形，所以这里要填6
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureApplication::onDestroy()
{
    m_shader = nullptr;
    m_mesh = nullptr;
}
