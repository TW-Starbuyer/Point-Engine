cmake_minimum_required(VERSION 3.5)

project(ImGui LANGUAGES CXX)

set(
	IMGUI_SOURCES
	imgui.cpp
	imgui_draw.cpp
	imgui_tables.cpp
	imgui_widgets.cpp
	imgui_demo.cpp
	
	#Backends
	backends/imgui_impl_sdl3.cpp
	backends/imgui_impl_opengl3.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})

target_include_directories(ImGui PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/backends
)

target_link_libraries(ImGui PRIVATE SDL3::SDL3)