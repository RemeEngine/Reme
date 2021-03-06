#include <Reme/Platform/OpenGL/OpenGL_RendererAPI.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <sstream>

namespace Reme {

void glDebugOutput(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    MAYBE_UNUSED GLsizei length,
    const GLchar* message,
    MAYBE_UNUSED const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::stringstream ss;

    switch (source) {
    case GL_DEBUG_SOURCE_API_ARB:
        ss << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
        ss << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
        ss << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
        ss << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION_ARB:
        ss << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER_ARB:
        ss << "Source: Other";
        break;
    }
    ss << ", ";

    switch (type) {
    case GL_DEBUG_TYPE_ERROR_ARB:
        ss << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
        ss << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
        ss << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY_ARB:
        ss << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE_ARB:
        ss << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_OTHER_ARB:
        ss << "Type: Other";
        break;
    }
    ss << ", ";

    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH_ARB:
        ss << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM_ARB:
        ss << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW_ARB:
        ss << "Severity: low";
        break;
    default:
        ss << "Severity: Notification";
        break;
    }

    CORE_LOG_ERROR("OpenGL {} - ({})", message, ss.str());
}

void OpenGL_RendererAPI::initialize()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        CORE_LOG_ERROR("Failed to initialize GLAD");
        exit(EXIT_FAILURE);
    }

    CORE_LOG_INFO("OpenGL Version: {}", glGetString(GL_VERSION));
    CORE_LOG_INFO("GLSL Version  : {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
    CORE_LOG_INFO("Renderer      : {}", glGetString(GL_RENDERER));

    GLint temp;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &temp);
    CORE_LOG_INFO("Max Texture Units: {}", temp);
    m_max_texture_unit = temp;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &temp);
    CORE_LOG_INFO("Max Texture Size : {0}x{0}", temp);
    m_max_texture_size = temp;

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (GLAD_GL_ARB_debug_output) {
        m_use_error_polling = false;
        glEnable(GL_ARB_debug_output);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
        glDebugMessageCallbackARB(glDebugOutput, nullptr);
        glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}

void OpenGL_RendererAPI::set_viewport(u32 x, u32 y, u32 width, u32 height)
{
    glViewport(x, y, width, height);
}

void OpenGL_RendererAPI::set_clear_color(const Color& color)
{
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}

void OpenGL_RendererAPI::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGL_RendererAPI::poll_errors()
{
    if (!m_use_error_polling)
        return;

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        CORE_LOG_ERROR("OpenGL Error: {}", err);
    }
}

GLenum GetDrawMode(const DrawMode& mode)
{
    switch (mode) {
    case DrawMode::LINE_LOOP:
        return GL_LINE_LOOP;
    case DrawMode::LINE_STRIP:
        return GL_LINE_STRIP;
    case DrawMode::LINES:
        return GL_LINES;
    case DrawMode::POINTS:
        return GL_POINTS;
    case DrawMode::TRIANGLE_FAN:
        return GL_TRIANGLE_FAN;
    case DrawMode::TRIANGLE_STRIP:
        return GL_TRIANGLE_STRIP;
    case DrawMode::TRIANGLES:
        return GL_TRIANGLES;
    default:
        CORE_ASSERT(false, "Unknown draw mode!");
        return 0;
    }
}

void OpenGL_RendererAPI::draw_indexed(DrawMode mode, u32 count, u32 offset)
{
    glDrawElements(GetDrawMode(mode), count, GL_UNSIGNED_INT, (void*)static_cast<FlatPtr>(offset));
}

void OpenGL_RendererAPI::draw_arrays(DrawMode mode, u32 count, u32 offset)
{
    glDrawArrays(GetDrawMode(mode), offset, count);
}

} // namespace Reme
