#include <Reme/Renderer/VertexArray.h>

#include <Reme/Debug/Instrumentor.h>
#include <Reme/Platform/OpenGL/OpenGL_VertexArray.h>
#include <Reme/Renderer/RendererAPI.h>

namespace Reme {

RefPtr<VertexArray> VertexArray::create()
{
    PROFILE_FUNCTION();

    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return Asset::make<OpenGL_VertexArray>();
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Reme
