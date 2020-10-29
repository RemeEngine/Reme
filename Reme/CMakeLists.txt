set(SOURCES
    Core/Application.cpp
    Core/Asset.cpp
    Core/Logger.cpp
    Core/StbImpl.cpp
    Core/Window.cpp
    Debug/ExceptionHandler.cpp
    Events/Input.cpp
    GUI/Node.cpp
    GUI/Sprite.cpp
    Platform/GLFW_Window.cpp
    Platform/OpenGL/OpenGL_Buffers.cpp
    Platform/OpenGL/OpenGL_RendererAPI.cpp
    Platform/OpenGL/OpenGL_Shader.cpp
    Platform/OpenGL/OpenGL_Texture.cpp
    Platform/OpenGL/OpenGL_VertexArray.cpp
    Renderer/Buffers.cpp
    Renderer/Color.cpp
    Renderer/Image.cpp
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

set(LIBS
    glad
    glfw
    imgui
)

add_library(Reme STATIC ${SOURCES})
target_link_libraries(Reme ${LIBS})

add_library(ProfileReme STATIC ${SOURCES})
target_compile_definitions(ProfileReme PUBLIC -DREME_RUN_PROFILE)
target_link_libraries(ProfileReme ${LIBS})

