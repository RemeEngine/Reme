#include <Reme/Renderer/RendererAPI.h>
#include <Reme/Renderer/Shader.h>

#include <Reme/Impl/OpenGL/OpenGL_Shader.h>

namespace Reme {

RefPtr<Shader> Shader::create(const std::string& filepath)
{
    PROFILE_FUNCTION();

    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return Asset::make<OpenGL_Shader>(filepath);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

RefPtr<Shader> Shader::create(const std::string& name, const std::string& vertex_shader, const std::string& fragment_shader)
{
    PROFILE_FUNCTION();

    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return Asset::make<OpenGL_Shader>(name, vertex_shader, fragment_shader);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace Reme
