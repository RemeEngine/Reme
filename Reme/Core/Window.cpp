#include <Reme/Core/Window.h>

#include <Reme/Core/Core.h>
#include <Reme/Platform/GLFW_Window.h>

namespace Reme {

OwnPtr<Window> Window::create(const WindowProps& props)
{
    return make_own<GLFW_Window>(props);
}

} // namespace Reme
