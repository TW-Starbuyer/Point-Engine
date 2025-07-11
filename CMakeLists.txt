cmake_minimum_required(VERSION 3.5)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:DebugDLL>")

project("PointEngine")


set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

include(FetchContent)

# GLFW
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


find_package(GLFW QUIET)
if(NOT GLFW_FOUND)
	FetchContent_Declare(
		glfw
		GIT_REPOSITORY https://github.com/glfw/glfw.git
		GIT_TAG 3.4
	)
	FetchContent_MakeAvailable(glfw)
	message(STATUS "Fetched glfw SUCCESS")
endif()

# SDL
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
	FetchContent_Declare(
		sdl
		GIT_REPOSITORY https://github.com/libsdl-org/SDL.git 
		GIT_TAG release-3.2.0
	)
	FetchContent_MakeAvailable(sdl)
	message(STATUS "Fetched sdl SUCCESS")
endif()

# GLM
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
find_package(GLM QUIET)
if (NOT GLM_FOUND)
	FetchContent_Declare(
		glm
		GIT_REPOSITORY https://github.com/g-truc/glm.git
		GIT_TAG 1.0.1
	)
	FetchContent_MakeAvailable(glm)
	message(STATUS "Fetched glm SUCCESS")
endif()

# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
find_package(SOL2 QUIET)
if (NOT SOL2_FOUND)
	FetchContent_Declare(
		sol2
		GIT_REPOSITORY https://github.com/ThePhD/sol2.git
		GIT_TAG v3.3.0
	)
	FetchContent_MakeAvailable(sol2)
	message(STATUS "Fetched sol2 SUCCESS")
endif()


# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
find_package(NLOHMANN_JSON QUIET)
if (NOT NLOHMANN_JSON_FOUND)
	FetchContent_Declare(
		json
		GIT_REPOSITORY https://github.com/nlohmann/json.git
		GIT_TAG v3.11.3	
	)
	FetchContent_MakeAvailable(json)
	message(STATUS "Fetched nlohmann_json SUCCESS")
endif()


find_package(ASSIMP QUIET)
if (NOT ASSIMP_FOUND)
	FetchContent_Declare(
		assimp
		GIT_REPOSITORY https://github.com/assimp/assimp.git
		GIT_TAG v5.4.0
	)
	FetchContent_MakeAvailable(assimp)
	message(STATUS "Fetched assimp SUCCESS")
endif()

add_subdirectory(include/third_party/glad)
add_subdirectory(include/third_party/imgui)
add_subdirectory(include/third_party/lua-5.4.7)


file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/code/*.cpp")


add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") 

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(MSVC) 

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

endif()


target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC 
	"${CMAKE_CURRENT_SOURCE_DIR}/include/lib"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/headers"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/utils"
)


target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE 
	glfw
	glad
	SDL3::SDL3 
	glm::glm 
	ImGui 
	LuaLib 
	sol2
	nlohmann_json::nlohmann_json
	assimp::assimp
	)