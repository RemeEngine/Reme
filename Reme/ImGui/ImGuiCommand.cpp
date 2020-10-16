#include <Reme/Core/Application.h>
#include <Reme/Core/Core.h>
#include <Reme/ImGui/ImGuiCommand.h>

#include <imgui/imgui.h>

#include <imgui/examples/imgui_impl_glfw.h>
#include <imgui/examples/imgui_impl_opengl3.h>

namespace Reme {

void ImGuiCommand::initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowRounding = 0.0f;

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::the().window().native_window(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiCommand::shutdown()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();

    ImGui::DestroyContext();
}

void ImGuiCommand::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiCommand::end()
{
    ImGuiIO& io = ImGui::GetIO();
    Window& window = Application::the().window();
    io.DisplaySize = ImVec2((float)window.width(), (float)window.height());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        window.make_context_current();
    }
}

bool ImGuiCommand::should_swallow_event(Event& event)
{
    ImGuiIO& io = ImGui::GetIO();
    return ((event.in_category(EventCategoryMouse) && io.WantCaptureMouse) || (event.in_category(EventCategoryKeyboard) && io.WantCaptureKeyboard));
}

} // namespace Reme
