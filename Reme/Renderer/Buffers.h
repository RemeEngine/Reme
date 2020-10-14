#pragma once

#include <Reme/Core/Asset.h>
#include <Reme/Core/Core.h>
#include <Reme/Renderer/ShaderDataLayout.h>

namespace Reme {

class VertexBuffer : public Asset {
public:
    static RefPtr<VertexBuffer> create(u32 byte_size, bool is_static = true);

    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void set_data(float* data, u32 byte_offset, u32 byte_size) = 0;

    const BufferLayout& layout() const { return m_layout; }
    void set_layout(const BufferLayout& layout) { m_layout = layout; }

private:
    BufferLayout m_layout;
};

class IndexBuffer : public Asset {
public:
    static RefPtr<IndexBuffer> create(u32 byte_size, bool is_static = true);

    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void set_data(u32* data, u32 byte_offset, u32 byte_size) = 0;
};

} // namespace Reme
