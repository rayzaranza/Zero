find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(Zero SHARED
	"src/Zero.h"
	"src/Zero/Core.h"
	"src/Zero/EntryPoint.h"
    "src/Zero/Application.h"
	"src/Zero/Application.cpp"
)

target_include_directories(Zero PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(Zero PUBLIC
	glm::glm 
	glad::glad 
	glfw
	spdlog::spdlog
)

target_compile_definitions(Zero PUBLIC ZERO_PLATFORM_WINDOWS)
target_compile_definitions(Zero PRIVATE ZERO_BUILD_DLL)
