#include <Reme/Core/Application.h>

#include <Reme/Debug/Instrumentor.h>
#include <Reme/Events/Input.h>
#include <Reme/Renderer/OrthographicCamera.h>
#include <Reme/Renderer/Renderer.h>
#include <Reme/Renderer/Renderer2D.h>
#include <Reme/Renderer/RendererAPI.h>
#include <chrono>

namespace Reme {

Application* Application::s_instance = nullptr;

Application::Application(const WindowProps& props)
{
    PROFILE_FUNCTION();

    CORE_ASSERT(!s_instance, "Application already exist!");
    s_instance = this;

    m_window = Window::create(props);
    m_window->enable_VSync(true);
    m_window->set_event_callback(BIND_EVENT_FN(Application::on_event));

    Renderer::initialize();
}

Application::~Application()
{
    PROFILE_FUNCTION();

    Renderer::shutdown();
}

void Application::run()
{
    PROFILE_FUNCTION();

    if (m_running)
        return;

    m_running = true;
    using TimeStamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

    TimeStamp current_time;
    TimeStamp last_time = std::chrono::high_resolution_clock::now();
    float elapsed_time;

    while (m_running) {
        PROFILE_SCOPE("main_loop");

        {
            PROFILE_SCOPE("do_layout");
            if (m_should_do_layout && m_window && m_window->current_scene()) {
                m_window->current_scene()->do_layout();
                m_should_do_layout = false;
            }
        }

        m_window->poll_event();

        current_time = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration<float>(current_time - last_time).count();
        while (elapsed_time >= m_delta_time) {
            PROFILE_SCOPE("update_call");

            elapsed_time -= m_delta_time;
        }

        if (!m_minimized) {
            PROFILE_SCOPE("render_call");

            RenderCommand::clear();
            Renderer2D::begin();
            m_window->render();
            Renderer2D::end();
        }

        last_time = current_time;
        m_window->swap_buffers();
    }

    m_window->set_current_scene(nullptr);
    Logger::core_logger()->flush();
    Logger::logger()->flush();
}

void Application::on_event(Event& event)
{
    PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::on_window_close));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::on_window_resize));

    Input::on_event({}, event);
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
    Renderer::on_window_resize({}, e.width(), e.height());

    return false;
}

} // namespace Reme
