cmake_minimum_required(VERSION 3.20)

project("Ex")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ex "")

set_target_properties(ex PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

target_include_directories(ex PRIVATE
    src
)

target_sources(ex PRIVATE
    src/main.cpp
)
