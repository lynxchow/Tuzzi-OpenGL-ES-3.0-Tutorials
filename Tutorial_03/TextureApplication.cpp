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

    // 设置3个顶点，每个顶点有1个vec3的位置信息和1个vec3的颜色信息
    float vertices[] =
    {
        // positions              // texture coords
         0.5f * 0.5625,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f * 0.5625, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f * 0.5625, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f * 0.5625,  0.5f, 0.0f,   0.0f, 1.0f  // top left
    };

    // 三角形面片的顶点序号，从0开始的
    unsigned int indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    // 分配VAO对象
    glGenVertexArrays(1, &VAO);
    // 分配VBO对象，专门存储顶点数据
    glGenBuffers(1, &VBO);
    // 分配EBO对象，专门存储顶点的索引值
    glGenBuffers(1, &EBO);

    // 先绑定VAO对象，由这个VAO对象来记录VBO操作
    glBindVertexArray(VAO);

    // 先绑定VBO对象到GL_ARRAY_BUFFER这个target上，后续对GL_ARRAY_BUFFER的操作都会修改VBO这个对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 绑定具体的顶点内存数据到GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // 绑定EBO对象到GL_ELEMENT_ARRAY_BUFFER这个target上，后续对GL_ELEMENT_ARRAY_BUFFER的操作都会修改EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 绑定顶点索引数据到GL_ELEMENT_ARRAY_BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // 通过下面的方法告诉OpenGL如何解析顶点数据的postion信息
    // 第一个参数，0，数据解析对应到顶点着色器中的layout(location = 0)
    // 第二个参数，3，表示顶点数据的大小，因为顶点是vec3，所以这里是3
    // 第三个参数，GL_FLOAT，表示我们的数据是float类型的
    // 第四个参数，GL_FALSE，表示是否需要归一化
    // 第五个参数，一个顶点数据的是多少，我们一个顶点包含3个float的position，3个float的color，所以这里是6 * sizeof(float)
    // 第六个参数，(void*)0，表示位置信息在一个顶点数据的偏移值是多少。因为每组数据开头就是position信息，所以这里填0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    // 解析顶点数据的uv信息，因为uv在顶点布局的1号位置，所以第一个参数是1
    // 第六个参数是sizeof(float) * 3，因为一组顶点数据开头要偏移3个float数据才是color值
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    // 启动传输layout 0
    glEnableVertexAttribArray(0);
    // 启动传输layout 1
    glEnableVertexAttribArray(1);

    // 因为之前需要绑定VBO来绑定顶点数据，那么处理完之后解绑GL_ARRAY_BUFFER
    // 免得后面误操作了VBO，毕竟OpenGL是个状态机。
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 但是却不能在VAO绑定的过程中解绑EBO，因为EBO需要存储在VAO的，很怪的规定，反正别解绑EBO就是了- -

    // 终于处理完VAO的配置了，这个时候就可以解除绑定VAO啦，免得后面又不小心误操作了VAO
    glBindVertexArray(0);
    
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

//    // bind Texture
//    glBindTexture(GL_TEXTURE_2D, *static_cast<GLuint *>(m_texture->getHandle()));
    
    // 使用我们的shader
    m_shader->use();
    // 因为我们的三角形的顶点数据绑定解析已经全部配置到VAO啦
    // glBindVertexArray绑定可以将下面的绘制操作制定之前设置的三角形
    glBindVertexArray(VAO);
    // 调用glDrawElements绘制方法，
    // 第一个参数代表，绘制图元是三角形，还有点，线，扇形可选择
    // 第二个参数代表需要绘制的顶点，因为我们的绘制两个三角形，所以这里要填6
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureApplication::onDestroy()
{
    m_shader = nullptr;
    // 最后需要释放VAO，VBO，EBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
