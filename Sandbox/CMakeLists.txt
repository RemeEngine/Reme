set(SOURCES
    Sandbox.cpp
)

add_executable(sb ${SOURCES})
target_link_libraries(sb Reme)

add_executable(profile ${SOURCES})
target_link_libraries(profile ProfileReme)

install(TARGETS sb profile RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/Out/Sandbox)
install(DIRECTORY assets/ DESTINATION ${CMAKE_SOURCE_DIR}/Out/Sandbox/assets)
