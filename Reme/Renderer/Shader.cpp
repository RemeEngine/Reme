#include <Reme/Renderer/RendererAPI.h>
#include <Reme/Renderer/Shader.h>

#include <Reme/Impl/OpenGL/OpenGL_Shader.h>

namespace Reme {

RefPtr<Shader> Shader::create(const std::string& file_path)
{
    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return make<OpenGL_Shader>(file_path);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

RefPtr<Shader> Shader::create(const std::string& name, const std::string& vertex_shader, const std::string& fragment_shader)
{
    switch (RendererAPI::api()) {
    case RendererAPI::None:
        CORE_ASSERT(false, "RendererAPI::None is not supported!");
        return nullptr;
    case RendererAPI::OpenGL:
        return make<OpenGL_Shader>(name, vertex_shader, fragment_shader);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}
} // namespace Reme
