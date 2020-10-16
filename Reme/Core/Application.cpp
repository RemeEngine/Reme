#include <Reme/Core/Application.h>

#include <Reme/Events/Input.h>
#include <Reme/Renderer/OrthographicCamera.h>
#include <Reme/Renderer/Renderer.h>
#include <Reme/Renderer/Renderer2D.h>
#include <chrono>

namespace Reme {

Application* Application::s_instance = nullptr;

Application::Application(const WindowProps& props)
{
    CORE_ASSERT(!s_instance, "Application already exist!");
    s_instance = this;

    m_window = Window::create(props);
    m_window->enable_VSync(true);
    m_window->set_event_callback(BIND_EVENT_FN(Application::on_event));

    Renderer::initialize();
}

Application::~Application()
{
    Renderer::shutdown();
}

void Application::run()
{
    if (m_running)
        return;

    m_running = true;
    using TimeStamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

    TimeStamp current_time;
    TimeStamp last_time = std::chrono::high_resolution_clock::now();
    float elapsed_time;

    while (m_running) {
        m_window->poll_event();

        current_time = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration<float>(current_time - last_time).count();
        while (elapsed_time >= m_delta_time) {
            elapsed_time -= m_delta_time;

            AppUpdateEvent e(m_delta_time);
            on_event(e);
        }

        if (!m_minimized) {
            AppRenderEvent e;
            on_event(e);
        }

        last_time = current_time;
        m_window->swap_buffers();
    }
}

void Application::on_event(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::on_window_close));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::on_window_resize));

    Input::on_event(event);
    window().on_event(event);
}

bool Application::on_window_close(WindowCloseEvent)
{
    m_running = false;
    return false;
}

bool Application::on_window_resize(WindowResizeEvent e)
{
    if (e.width() == 0 || e.height() == 0) {
        m_minimized = true;
        return false;
    }

    m_minimized = false;
    Renderer::on_window_resize(e.width(), e.height());

    return false;
}

} // namespace Reme
