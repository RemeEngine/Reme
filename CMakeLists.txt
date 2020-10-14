cmake_minimum_required(VERSION 3.16)

set(CMAKE_INSTALL_MESSAGE NEVER)

project(Reme)

enable_testing()

function(make_bin target_name)
    add_executable(${target_name} ${SOURCES})
    install(TARGETS ${target_name} RUNTIME DESTINATION .)
endfunction()

unset(CMAKE_SYSROOT)
set(CMAKE_STAGING_PREFIX ${CMAKE_SOURCE_DIR}/Out)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Out)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-warning-option -Wall -Wextra -Werror -Wmissing-declarations -std=c++2a -fdiagnostics-color=always")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -g1 -fno-exceptions -Wno-address-of-packed-member -Wundef -Wcast-qual -Wwrite-strings -Wimplicit-fallthrough -Wno-nonnull-compare -Wno-deprecated-copy -Wno-expansion-to-defined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG -DGL_SILENCE_DEPRECATION -DGLFW_INCLUDE_NONE")

include_directories(SYSTEM Libraries)
include_directories(SYSTEM Libraries/glad/include)
include_directories(SYSTEM Libraries/GLFW/include)
include_directories(SYSTEM Libraries/glm)
include_directories(SYSTEM Libraries/spdlog/include)
add_subdirectory(Libraries)

include_directories(.)
add_subdirectory(Reme)

add_subdirectory(Sandbox)
