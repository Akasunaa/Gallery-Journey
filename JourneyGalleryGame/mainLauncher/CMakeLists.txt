
add_executable(mainLauncher mainLauncher.cpp "../imgui_lib/imconfig.h" "../imgui_lib/imgui-SFML.cpp" "../imgui_lib/imgui-SFML.h" "../imgui_lib/imgui-SFML_export.h" "../imgui_lib/imgui.cpp" "../imgui_lib/imgui.h" "../imgui_lib/imgui_demo.cpp" "../imgui_lib/imgui_draw.cpp" "../imgui_lib/imgui_internal.h" "../imgui_lib/imgui_widgets.cpp" "../imgui_lib/imstb_rectpack.h" "../imgui_lib/imstb_textedit.h" "../imgui_lib/imstb_truetype.h")

target_link_libraries(mainLauncher PUBLIC src pugixml sfml-graphics box2d ${OPENGL_LIBRARIES})

add_custom_target(copy-resources ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources 
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources/images
                   DEPENDS ${CMAKE_SOURCE_DIR}/resources/xml_files
                   COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
                   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)
add_dependencies(mainLauncher copy-resources)