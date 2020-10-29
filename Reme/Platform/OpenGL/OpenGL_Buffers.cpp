#include <Reme/Platform/OpenGL/OpenGL_Buffers.h>

#include <glad/glad.h>

namespace Reme {
// VERTEX BUFFER
OpenGL_VertexBuffer::OpenGL_VertexBuffer(u32 byte_size, bool is_static)
{
    glGenBuffers(1, &m_internal_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_internal_id);
    glBufferData(GL_ARRAY_BUFFER, byte_size, nullptr, is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
{
    glDeleteBuffers(1, &m_internal_id);
}

void OpenGL_VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_internal_id);
}

void OpenGL_VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGL_VertexBuffer::set_data(float* data, u32 byte_offset, u32 byte_size)
{
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, byte_offset, byte_size, data);
}

// INDEX BUFFER
OpenGL_IndexBuffer::OpenGL_IndexBuffer(u32 byte_size, bool is_static)
{
    glGenBuffers(1, &m_internal_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_internal_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_size, nullptr, is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
{
    glDeleteBuffers(1, &m_internal_id);
}

void OpenGL_IndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_internal_id);
}

void OpenGL_IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGL_IndexBuffer::set_data(u32* data, u32 byte_offset, u32 byte_size)
{
    bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, byte_offset, byte_size, data);
}

} // namespace Reme
