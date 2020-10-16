#include <Reme/Renderer/Renderer.h>

#include <Reme/Core/Application.h>
#include <Reme/Renderer/OrthographicCamera.h>
#include <Reme/Renderer/Renderer2D.h>
#include <Reme/Renderer/RendererAPI.h>

namespace Reme {

RefPtr<OrthographicCamera> OrthographicCamera::DEFAULT;

void Renderer::initialize()
{
    // The order of these is important
    RenderCommand::initialize();
    Renderer2D::initialize();
    Texture::initialize();

    auto& window = Application::the().window();
    OrthographicCamera::DEFAULT = make<OrthographicCamera>(0, window.width(), window.height(), 0);
}

void Renderer::shutdown()
{
    Renderer2D::shutdown();

    Texture::DEFAULT.reset();
    Texture::WHITE.reset();
    OrthographicCamera::DEFAULT.reset();
}

void Renderer::on_window_resize(float width, float height)
{
    RenderCommand::set_viewport(0, 0, width, height);
    OrthographicCamera::DEFAULT->set_projection(0, width, height, 0);
}

} // namespace Reme
