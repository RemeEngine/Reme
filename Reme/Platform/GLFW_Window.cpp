#include <Reme/Platform/GLFW_Window.h>

#include <GLFW/glfw3.h>
#include <Reme/Core/Core.h>
#include <Reme/Events/ApplicationEvent.h>
#include <Reme/Events/KeyEvent.h>
#include <Reme/Events/MouseEvent.h>

namespace Reme {

static u8 s_glfw_window_count = 0;

static void GLFWErrorCallback(int error, const char* description)
{
    CORE_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}

GLFW_Window::GLFW_Window(const WindowProps& props)
{
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;

    CORE_LOG_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

    if (s_glfw_window_count == 0) {
        int success = glfwInit();
        CORE_ASSERT(success, "Could not intialize GLFW!");
        glfwSetErrorCallback(GLFWErrorCallback);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

    m_window = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
    s_glfw_window_count++;

    if (!m_window) {
        glfwTerminate();
        CORE_LOG_ERROR("Failed to create GLFW window!");
        exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(m_window, &m_data);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
        data->width = width;
        data->height = height;

        WindowResizeEvent e(width, height);
        data->on_event(e);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data->on_event(event);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, MAYBE_UNUSED int scancode, int action, MAYBE_UNUSED int mods) {
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
            KeyDownEvent event(static_cast<KeyCode>(key), 0);
            data->on_event(event);
            break;
        }

        case GLFW_RELEASE: {
            KeyUpEvent event(static_cast<KeyCode>(key));
            data->on_event(event);
            break;
        }

        case GLFW_REPEAT: {
            KeyDownEvent event(static_cast<KeyCode>(key), 1);
            data->on_event(event);
            break;
        }
        }
    });

    glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
        KeyPressEvent event(static_cast<KeyCode>(keycode));
        data->on_event(event);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);
        MouseMoveEvent event((float)xpos, (float)ypos);
        data->on_event(event);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int) {
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
        case GLFW_PRESS: {
            MouseDownEvent event(static_cast<MouseCode>(button));
            data->on_event(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseUpEvent event(static_cast<MouseCode>(button));
            data->on_event(event);
            break;
        }
        }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

        MouseScrollEvent event((float)xOffset, (float)yOffset);
        data->on_event(event);
    });

    glfwSetWindowUserPointer(m_window, &m_data);
    make_context_current();
}

GLFW_Window::~GLFW_Window()
{
    glfwDestroyWindow(m_window);
    s_glfw_window_count--;

    if (s_glfw_window_count == 0) {
        glfwTerminate();
    }
}

void GLFW_Window::poll_event()
{
    glfwPollEvents();
}

void GLFW_Window::swap_buffers()
{
    glfwSwapBuffers(m_window);
}

void GLFW_Window::make_context_current()
{
    glfwMakeContextCurrent(m_window);
}

u32 GLFW_Window::width() const
{
    return m_data.width;
}

u32 GLFW_Window::height() const
{
    return m_data.height;
}

void GLFW_Window::set_size(u32 width, u32 height)
{
    m_data.width = width;
    m_data.height = height;
    glfwSetWindowSize(m_window, width, height);
}

const std::string& GLFW_Window::title() const
{
    return m_data.title;
}

void GLFW_Window::set_title(const std::string& title)
{
    m_data.title = title;
    glfwSetWindowTitle(m_window, title.c_str());
}

void GLFW_Window::enable_VSync(bool enabled)
{
    m_data.is_VSync = enabled;

    if (enabled) {
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
}

bool GLFW_Window::is_VSync() const
{
    return m_data.is_VSync;
}

} // namespace Reme
