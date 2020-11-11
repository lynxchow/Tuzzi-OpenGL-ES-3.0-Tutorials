//
//  Mesh.h
//  Tuzzi
//
//  Created by Lyn on 2020/8/28.
//  Copyright © 2020 Vin-Ex. All rights reserved.
//

#ifndef _TUZZI_GRAPHICS_MESH_H_
#define _TUZZI_GRAPHICS_MESH_H_

#include "Object.h"
#include "math/Math.h"
#include "container/Vector.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

using VertexBufferHandle = void *;
using VertexArrayHandle = void *;
using IndexBufferHandle = void *;

struct Vertex
{
    Vector3f vertex;
    Vector2f uv;
};

struct Submesh
{
    uint32_t index_start;
    uint32_t index_count;
};

enum class PrimitiveType : uint8_t {
    POINTS      = 0,
    LINES       = 1,
    TRIANGLES   = 4,
    NONE        = 0xFF
};

class Mesh : public Object
{
public:
    Mesh(Vector<Vertex>&& vertices, Vector<uint32_t>&& indices, const Vector<Submesh>& submeshes = Vector<Submesh>(), bool uint32_index = false, bool dynamic = false);
    
    virtual ~Mesh();
    
    static const SharedPtr<Mesh>& getSharedQuadMesh();
    
    void update(Vector<Vertex>&& vertices, Vector<unsigned int>&& indices, const Vector<Submesh>& submeshes);
    
    const Vector<Vertex>& getVertices() const;
    
    const Vector<uint32_t>& getIndices() const;
    
    const Vector<Submesh>& getSubmeshes() const;
    
    VertexArrayHandle getVertexArrayHandle() const;
    
    VertexBufferHandle getVertexBufferHandle() const;
    
    IndexBufferHandle getIndexBufferHandle() const;
    
    
private:
    static SharedPtr<Mesh> m_shared_quad_mesh;
    Vector<Vertex> m_vertices;
    Vector<uint32_t> m_indices;
    Vector<Submesh> m_submeshes;
    Vector<PrimitiveType> m_primitives;
    VertexArrayHandle m_vao;
    VertexBufferHandle m_vbo;
    IndexBufferHandle m_ibo;
    
};

NAMESPACE_TUZZI_ENGINE_END

#endif /* Mesh_h */
