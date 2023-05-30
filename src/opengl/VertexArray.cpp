#include <opengl/VertexArray.hpp>

namespace texplr {

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::loadMeshData(const MeshData& meshData)
{
    loadVertices(meshData.vertices);
    loadIndices(meshData.indices);
}

void VertexArray::loadVertices(const std::vector<Vertex>& vertices)
{
    bind();
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
}

void VertexArray::loadIndices(const std::vector<uint32_t>& indices)
{
    bind();
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), indices.data(), GL_STATIC_DRAW);

    m_vertexCount = indices.size();
}

void VertexArray::bind()
{
    glBindVertexArray(m_id);
}

void VertexArray::draw()
{
    bind();
    glDrawElements(GL_TRIANGLES, m_vertexCount, GL_UNSIGNED_INT, (void*)0);
}

} // namespace texplr
