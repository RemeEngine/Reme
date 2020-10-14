#include <Reme/Core/Window.h>

#include <Reme/Core/Core.h>
#include <Reme/Impl/GLFW_Window.h>

namespace Reme
{
    OwnPtr<Window> Window::construct(const WindowProps& props)
    {
        return make_own<GLFW_Window>(props);
    }
}
