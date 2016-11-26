//
//  TriangleApplication.cpp
//  Triangle
//
//  Created by Pocoyo Chow on 25/11/2016.
//  Copyright © 2016 pocoyo. All rights reserved.
//

#include "TriangleApplication.hpp"

TriangleApplication::TriangleApplication() : GLApplication("shader.vsh", "shader.fsh")
{
    
}

bool TriangleApplication::init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.2, 0.3, 1);
    return true;
}

void TriangleApplication::render(GLuint x, GLuint y, GLuint width, GLuint height)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // 清除颜色缓冲和深度缓冲
    glUseProgram(programObject);                                // 使用shader
    
    float vec[3][3] = {                                         // 三角形顶点
        { 0.0,  0.5,  0.5},
        {-0.5, -0.5,  0.5},
        { 0.5, -0.5, -0.5}
    };
    glEnableVertexAttribArray(0);                               // 启用这个索引
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vec);    // 设置这个索引需要填充的内容
    glDrawArrays(GL_TRIANGLES, 0, 3);                           // 绘制三角形
}
