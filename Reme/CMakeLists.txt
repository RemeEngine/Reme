set(SOURCES
    Core/Application.cpp
    Core/Log.cpp
    Core/Window.cpp
    Impl/GLFW_Window.cpp
    Impl/OpenGL/OpenGL_Buffers.cpp
    Impl/OpenGL/OpenGL_RendererAPI.cpp
    Impl/OpenGL/OpenGL_Shader.cpp
    Impl/OpenGL/OpenGL_Texture.cpp
    Impl/OpenGL/OpenGL_VertexArray.cpp
    Renderer/Buffers.cpp
    Renderer/Color.cpp
    Renderer/OrthographicCamera.cpp
    Renderer/PerspectiveCamera.cpp 
    Renderer/Renderer.cpp
    Renderer/Renderer2D.cpp
    Renderer/RendererAPI.cpp
    Renderer/Shader.cpp
    Renderer/Texture.cpp
    Renderer/VertexArray.cpp
    Utility/Utils.cpp
)

add_library(Reme STATIC ${SOURCES})
target_link_libraries(Reme glfw imgui)
