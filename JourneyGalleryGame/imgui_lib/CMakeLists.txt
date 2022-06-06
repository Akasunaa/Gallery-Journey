
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(imgui_lib ${SOURCES})
target_include_directories(imgui_lib PUBLIC ./)
target_link_libraries(imgui_lib sfml-graphics OpenGL glfw)
