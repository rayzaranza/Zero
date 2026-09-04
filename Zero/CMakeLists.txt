find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")

add_library(Zero SHARED
	"src/Zero/Zero.h"
	"src/Zero/Core.h"
	"src/Zero/EntryPoint.h"

    "src/Application/Application.h"
	"src/Application/Application.cpp"

    "src/Logger/Logger.h"
    "src/Logger/Logger.cpp"

    "src/Event/Event.h"
    "src/Event/Event.cpp"
    "src/Event/KeyEvent.h"
    "src/Event/KeyEvent.cpp"
    "src/Event/MouseEvent.h"
    "src/Event/MouseEvent.cpp"
    "src/Event/ApplicationEvent.h"
    "src/Event/ApplicationEvent.cpp"

    "src/Window/Window.h"
    "src/Window/Window.cpp"

    "src/Layer/Layer.h"
    "src/Layer/Layer.cpp"
    "src/Layer/LayerStack.h"
    "src/Layer/LayerStack.cpp"

    "src/UI/UILayer.h"
    "src/UI/UILayer.cpp"

    "src/Input/Input.h"
    "src/Input/Input.cpp"
    "src/Input/KeyCode.h"
    "src/Input/MouseButtonCode.h"
)

target_include_directories(Zero PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Zero"
)

target_precompile_headers(Zero PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Zero/zrpch.h"
)

target_link_libraries(Zero PUBLIC
	glm::glm 
	glad::glad 
	glfw
	spdlog::spdlog
    imgui::imgui
)

target_compile_definitions(Zero PUBLIC
    ZERO_PLATFORM_WINDOWS
)

target_compile_definitions(Zero PRIVATE
    ZERO_BUILD_DLL
    ZERO_ENABLE_ASSERTS
    GLFW_INCLUDE_NONE
    IMGUI_IMPL_OPENGL_LOADER_CUSTOM
)

