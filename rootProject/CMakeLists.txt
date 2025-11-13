cmake_minimum_required(VERSION 3.16)
project(ImGuiPlotDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Paths
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/externals/imgui)
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/externals/implot)

# Find SDL2
find_package(SDL2 REQUIRED)

# ImGui sources
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# ImPlot sources
set(IMPLOT_SOURCES
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
    ${IMPLOT_DIR}/implot_demo.cpp
)

add_executable(ImGuiPlotDemo
    main.cpp
    ${IMGUI_SOURCES}
    ${IMPLOT_SOURCES}
)

target_include_directories(ImGuiPlotDemo PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMPLOT_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(ImGuiPlotDemo PRIVATE
    ${SDL2_LIBRARIES}
    GL
)

