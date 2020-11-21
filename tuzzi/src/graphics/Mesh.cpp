//
//  Mesh.cpp
//  Tuzzi
//
//  Created by Lyn on 2020/8/28.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "graphics/Mesh.h"
#include "gl/gl.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

SharedPtr<Mesh> Mesh::m_shared_quad_mesh = nullptr;

Mesh::Mesh(Vector<Vertex>&& vertices, Vector<uint32_t>&& indices, const Vector<Submesh>& submeshes, bool uint32_index, bool dynamic): m_vao(new GLuint(0)), m_vbo(new GLuint(0)), m_ibo(new GLuint(0))
{
    update(std::move(vertices), std::move(indices), submeshes);
    
    GLuint& vao = *static_cast<GLuint *>(m_vao);
    GLuint& vbo = *static_cast<GLuint *>(m_vbo);
    GLuint& ibo = *static_cast<GLuint *>(m_ibo);
    
    glGenVertexArrays(1, &vao);
    
    glGenBuffers(1, &vbo);
    
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glEnableVertexAttribArray(0);
    
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    GLuint& vao = *static_cast<GLuint *>(m_vao);
    GLuint& vbo = *static_cast<GLuint *>(m_vbo);
    GLuint& ibo = *static_cast<GLuint *>(m_ibo);
    if (vao != 0)
    {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo != 0)
    {
        glDeleteBuffers(1, &vbo);
    }
    if (ibo != 0)
    {
        glDeleteBuffers(1, &ibo);
    }
    
    delete static_cast<GLuint *>(m_vao);
    delete static_cast<GLuint *>(m_vbo);
    delete static_cast<GLuint *>(m_ibo);
}

const SharedPtr<Mesh>& Mesh::getSharedQuadMesh()
{
    if (!m_shared_quad_mesh)
    {
        Vector<Vertex> vertices(4);
        vertices[0].vertex = Vector3f(-1, 1, 0);
        vertices[1].vertex = Vector3f(-1, -1, 0);
        vertices[2].vertex = Vector3f(1, -1, 0);
        vertices[3].vertex = Vector3f(1, 1, 0);
        vertices[0].uv = Vector2f(0, 0);
        vertices[1].uv = Vector2f(0, 1);
        vertices[2].uv = Vector2f(1, 1);
        vertices[3].uv = Vector2f(1, 0);
        Vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3
        };
        m_shared_quad_mesh = MakeShared<Mesh>(std::move(vertices), std::move(indices));
    }

    return m_shared_quad_mesh;
}

void Mesh::update(Vector<Vertex>&& vertices, Vector<unsigned int>&& indices, const Vector<Submesh>& submeshes)
{
    m_vertices = vertices;
    m_indices = indices;
    m_submeshes = submeshes;
    
    if (m_submeshes.empty())
    {
        m_submeshes.push_back(Submesh({0, static_cast<uint32_t>(m_indices.size())}));
    }
}

const Vector<Vertex>& Mesh::getVertices() const
{
    return m_vertices;
}

const Vector<uint32_t>& Mesh::getIndices() const
{
    return m_indices;
}

const Vector<Submesh>& Mesh::getSubmeshes() const
{
    return m_submeshes;
}

VertexArrayHandle Mesh::getVertexArrayHandle() const
{
    return m_vao;
}

VertexBufferHandle Mesh::getVertexBufferHandle() const
{
    return m_vbo;
}

IndexBufferHandle Mesh::getIndexBufferHandle() const
{
    return m_ibo;
}

NAMESPACE_TUZZI_ENGINE_END
