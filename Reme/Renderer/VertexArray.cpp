#include <Reme/Renderer/VertexArray.h>

#include <Reme/Impl/OpenGL/OpenGL_VertexArray.h>
#include <Reme/Renderer/RendererAPI.h>

namespace Reme {

RefPtr<VertexArray> VertexArray::create()
{
    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return make_asset<OpenGL_VertexArray>();
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Reme
