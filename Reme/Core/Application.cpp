#include <Reme/Core/Application.h>

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

    m_window = Window::construct(props);
    m_window->enable_VSync(true);

    Renderer::initialize();
}

Application::~Application()
{
    Renderer::shutdown();
}

void Application::exec()
{
    using TimeStamp = std::chrono::time_point<std::chrono::high_resolution_clock>;

    TimeStamp current_time;
    TimeStamp last_time = std::chrono::high_resolution_clock::now();
    float elapsed_time;

    auto cam = make<OrthographicCamera>(0, m_window->width(), 0, m_window->height());

    while (m_running) {
        m_window->poll_event();

        current_time = std::chrono::high_resolution_clock::now();
        elapsed_time = std::chrono::duration<float>(current_time - last_time).count();
        while (elapsed_time >= m_delta_time) {
            elapsed_time -= m_delta_time;
            // Update code
        }

        // Render code
        Renderer2D::begin(cam);
        Renderer2D::fill_rect(Color::RED, 0, 0, 200, 200);
        Renderer2D::end();

        last_time = current_time;
        m_window->swap_buffers();
    }
}

} // namespace Reme
