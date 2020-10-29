#pragma once

#include <Reme/Renderer/VertexArray.h>

namespace Reme {
class OpenGL_VertexArray : public VertexArray {
public:
    OpenGL_VertexArray();
    virtual ~OpenGL_VertexArray() override;

    void bind() override;
    void unbind() override;

    void add_vertex_buffer(RefPtr<VertexBuffer> vertexBuf) override;
    void set_index_buffer(RefPtr<IndexBuffer> indexBuf) override;

    const std::vector<RefPtr<VertexBuffer>>& vertex_buffers() const override { return m_vertex_buffers; }
    const RefPtr<IndexBuffer>& index_buffer() const override { return m_index_buffer; }

private:
    u32 m_internal_id;
    u32 m_vertex_buffer_index;
    std::vector<RefPtr<VertexBuffer>> m_vertex_buffers;
    RefPtr<IndexBuffer> m_index_buffer;
};
} // namespace Reme
