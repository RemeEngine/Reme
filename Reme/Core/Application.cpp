#include <Reme/Core/Application.h>

#include <chrono>

namespace Reme {

Application* Application::s_instance = nullptr;

Application::Application(const WindowProps& props)
{
    CORE_ASSERT(!s_instance, "Application already exist!");
    s_instance = this;

    m_window = Window::construct(props);
    m_window->enable_VSync(true);
}

Application::~Application()
{
}

void Application::exec()
{
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
            // Update code
        }

        // Render code

        last_time = current_time;
        m_window->swap_buffers();
    }
}

} // namespace Reme
