cmake_minimum_required(VERSION 3.20)

project(jrpg)

# set(GLFW_BUILD_WAYLAND OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(third_party/glfw-3.4)

add_executable(editor "")

set_target_properties(editor PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

target_sources(editor PRIVATE
    src/main.cpp

    src/mesh.hpp
    src/mesh.cpp

    src/util.hpp
    src/util.cpp

    src/shaders.hpp # Generated
    src/shaders.cpp # Generated
)

target_include_directories(editor PRIVATE
    src
    third_party/glad/include
    third_party/imgui-1.91.9b
)

target_sources(editor PRIVATE
    third_party/glad/include/KHR/khrplatform.h
    third_party/glad/include/glad/gles2.h
    third_party/glad/src/gles2.c

    third_party/imgui-1.91.9b/imconfig.h
    third_party/imgui-1.91.9b/imgui_demo.cpp
    third_party/imgui-1.91.9b/imgui_draw.cpp
    third_party/imgui-1.91.9b/imgui_internal.h
    third_party/imgui-1.91.9b/imgui_tables.cpp
    third_party/imgui-1.91.9b/imgui_widgets.cpp
    third_party/imgui-1.91.9b/imgui.cpp
    third_party/imgui-1.91.9b/imgui.h
    third_party/imgui-1.91.9b/imstb_rectpack.h
    third_party/imgui-1.91.9b/imstb_textedit.h
    third_party/imgui-1.91.9b/imstb_truetype.h

    third_party/imgui-1.91.9b/backends/imgui_impl_glfw.h
    third_party/imgui-1.91.9b/backends/imgui_impl_glfw.cpp
    third_party/imgui-1.91.9b/backends/imgui_impl_opengl3.h
    third_party/imgui-1.91.9b/backends/imgui_impl_opengl3_loader.h
    third_party/imgui-1.91.9b/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(editor PRIVATE
    # dl
    glfw
)
