find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")

add_library(Zero SHARED
	"src/Zero/Zero.h"
	"src/Zero/Core.h"
	"src/Zero/EntryPoint.h"

    "src/Application/Application.h"
	"src/Application/Application.cpp"

    "src/Logger/Logger.h"
    "src/Logger/Logger.cpp"

    "src/Events/Event.h"
    "src/Events/Event.cpp"
    "src/Events/KeyEvent.h"
    "src/Events/KeyEvent.cpp"
    "src/Events/MouseEvent.h"
    "src/Events/MouseEvent.cpp"
    "src/Events/ApplicationEvent.h"
    "src/Events/ApplicationEvent.cpp"

    "src/Window/Window.h"
    "src/Window/Window.cpp"

    "src/Layer/Layer.h"
    "src/Layer/Layer.cpp"
    "src/Layer/LayerStack.h"
    "src/Layer/LayerStack.cpp"
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
    GLFW_INCLUDE_NONE
)

target_precompile_headers(Zero PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Zero/zrpch.h"
)
