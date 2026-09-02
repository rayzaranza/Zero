find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library(Zero SHARED
	"src/Zero/Zero.h"
	"src/Zero/Core.h"
	"src/Zero/EntryPoint.h"

    "src/Application/Application.h"
	"src/Application/Application.cpp"

    "src/Logger/Logger.h"
    "src/Logger/Logger.cpp"

    "src/Events/Event/Event.h"
    "src/Events/Event/Event.cpp"

    "src/Events/KeyEvent/KeyEvent.h"
    "src/Events/KeyEvent/KeyEvent.cpp"

    "src/Events/MouseEvent/MouseEvent.h"
    "src/Events/MouseEvent/MouseEvent.cpp"

    "src/Events/ApplicationEvent/ApplicationEvent.h"
    "src/Events/ApplicationEvent/ApplicationEvent.cpp"

    "src/Window/Window.h"
    "src/Window/Window.cpp"
)

target_include_directories(Zero PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Zero"
)

target_link_libraries(Zero PUBLIC
	glm::glm 
	glad::glad 
	glfw
	spdlog::spdlog
)

target_compile_definitions(Zero PUBLIC
    ZERO_PLATFORM_WINDOWS
    ZERO_ENABLE_ASSERTS
)

target_compile_definitions(Zero PRIVATE
    ZERO_BUILD_DLL
)

target_precompile_headers(Zero PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/zrpch.h"
)
