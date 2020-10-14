#pragma once

#include <Reme/Core/Asset.h>
#include <Reme/Renderer/Buffers.h>

namespace Reme {

class VertexArray : public Asset {
public:
    static RefPtr<VertexArray> create();

public:
    virtual void bind() = 0;
    virtual void unbind() = 0;

    virtual void add_vertex_buffer(RefPtr<VertexBuffer>) = 0;
    virtual void set_index_buffer(RefPtr<IndexBuffer>) = 0;

    virtual const std::vector<RefPtr<VertexBuffer>>& vertex_buffers() const = 0;
    virtual const RefPtr<IndexBuffer>& index_buffer() const = 0;
};

} // namespace Reme
