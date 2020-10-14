#pragma once

#include <Reme/Renderer/Buffers.h>
#include <Reme/Renderer/ShaderDataLayout.h>

namespace Reme {
class OpenGL_VertexBuffer : public VertexBuffer {
public:
    OpenGL_VertexBuffer(u32 byte_size, bool is_static);
    ~OpenGL_VertexBuffer();

    void bind() override;
    void unbind() override;
    void set_data(float* data, u32 offset, u32 byte_size) override;

private:
    u32 m_internal_id;
};

class OpenGL_IndexBuffer : public IndexBuffer {
public:
    OpenGL_IndexBuffer(u32 byte_size, bool is_static);
    ~OpenGL_IndexBuffer();

    void bind() override;
    void unbind() override;
    void set_data(u32* data, u32 offset, u32 byte_size) override;

private:
    u32 m_internal_id;
};
} // namespace Reme
