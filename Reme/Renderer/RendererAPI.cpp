#include <Reme/Renderer/RendererAPI.h>

#include <Reme/Platform/OpenGL/OpenGL_RendererAPI.h>

namespace Reme {

RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;
RendererAPI* RenderCommand::s_renderer_api = RendererAPI::create();

RendererAPI* RendererAPI::create()
{
    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return new OpenGL_RendererAPI();
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

} // namespace Reme
