set(SOURCES
    Core/Application.cpp
    Core/Log.cpp
    Core/Window.cpp
    Impl/GLFW_Window.cpp
)

add_library(Reme STATIC ${SOURCES})
target_link_libraries(Reme glfw imgui)
