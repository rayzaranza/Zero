find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_library(Zero
    STATIC
        "src/Zero/Zero.h"
        "src/Zero/Core.h"
        "src/Zero/EntryPoint.h"

        "src/Zero/Application/Application.h"
	    "src/Zero/Application/Application.cpp"

        "src/Zero/Logger/Logger.h"
        "src/Zero/Logger/Logger.cpp"

        "src/Zero/Input/Input.h"
        "src/Zero/Input/KeyCode.h"
        "src/Zero/Input/MouseButtonCode.h"
        "src/Zero/Input/Input.cpp"

        "src/Zero/Window/Window.h"
        "src/Zero/Window/Window.cpp"

        "src/Zero/Event/Event.h"
        "src/Zero/Event/Event.cpp"

        "src/Zero/Event/KeyEvent.h"
        "src/Zero/Event/KeyEvent.cpp"

        "src/Zero/Event/MouseEvent.h"
        "src/Zero/Event/MouseEvent.cpp"

        "src/Zero/Event/ApplicationEvent.h"
        "src/Zero/Event/ApplicationEvent.cpp"

        "src/Zero/Layer/Layer.h"
        "src/Zero/Layer/Layer.cpp"

        "src/Zero/Layer/LayerStack.h"
        "src/Zero/Layer/LayerStack.cpp"

        "src/Zero/UI/UILayer.h"
        "src/Zero/UI/UILayer.cpp"

        "src/Zero/Renderer/RendererContext.h"
        "src/Zero/Renderer/OpenGL/OpenGLContext.h"
        "src/Zero/Renderer/OpenGL/OpenGLContext.cpp"
        "src/Zero/Renderer/Shader.h"
        "src/Zero/Renderer/Shader.cpp"
)

target_include_directories(Zero
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_precompile_headers(Zero
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Zero/zrpch.h"
)

target_link_libraries(Zero
    PUBLIC
	    glm::glm 
	    glad::glad 
	    glfw
	    spdlog::spdlog
        imgui::imgui
)

target_compile_definitions(Zero
    PUBLIC
        ZERO_PLATFORM_WINDOWS
)

target_compile_definitions(Zero
    PUBLIC
        ZERO_ENABLE_ASSERTS
        GLFW_INCLUDE_NONE
        ZERO_BUILD_DLL
        IMGUI_IMPL_OPENGL_LOADER_GLAD
)
