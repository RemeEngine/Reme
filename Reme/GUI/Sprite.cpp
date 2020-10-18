#include <Reme/GUI/Sprite.h>

#include <Reme/Renderer/Renderer2D.h>

namespace Reme::GUI {

void Sprite::render()
{
    Renderer2D::draw_texture(m_texture);
}

} // namespace Reme::GUI
