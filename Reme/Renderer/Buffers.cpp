#include <Reme/Renderer/Buffers.h>
#include <Reme/Renderer/RendererAPI.h>

#include <Reme/Impl/OpenGL/OpenGL_Buffers.h>

namespace Reme {

RefPtr<VertexBuffer> VertexBuffer::create(u32 byte_size, bool is_static)
{
    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return make<OpenGL_VertexBuffer>(byte_size, is_static);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

RefPtr<IndexBuffer> IndexBuffer::create(u32 byte_size, bool is_static)
{
    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return make<OpenGL_IndexBuffer>(byte_size, is_static);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Reme
