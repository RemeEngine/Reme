#include <Reme/Renderer/Renderer.h>

#include <Reme/Renderer/Renderer2D.h>
#include <Reme/Renderer/RendererAPI.h>

namespace Reme {
void Renderer::initialize()
{
    // The order of these is important
    RenderCommand::initialize();
    Renderer2D::initialize();
    Texture::initialize();
}

void Renderer::shutdown()
{
    Renderer2D::shutdown();

    Texture::DEFAULT.reset();
    Texture::WHITE.reset();
}

void Renderer::on_window_resize(float width, float height)
{
    RenderCommand::set_viewport(0, 0, width, height);
}

} // namespace Reme
