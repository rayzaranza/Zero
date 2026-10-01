include(FetchContent)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)

FetchContent_Declare(EnTT
  GIT_REPOSITORY https://github.com/skypjack/entt
  GIT_TAG 85c6bba014049b5de8fad49d25424df2f1f6a8c1
)

FetchContent_MakeAvailable(EnTT)


set(SRC "src/Zero")

add_library(Zero STATIC
    "src/Zero.h"
    "${SRC}/Core/Core.h"
    "${SRC}/Core/EntryPoint.h"
    "${SRC}/Core/Types.h" 

    "${SRC}/Math/Math.h"
    "${SRC}/Math/Math.cpp"

    "${SRC}/Application/Application.h"
    "${SRC}/Application/Application.cpp"

    "${SRC}/Logger/Logger.h"
    "${SRC}/Logger/Logger.cpp"

    "${SRC}/Input/Input.h"
    "${SRC}/Input/Input.cpp"
    "${SRC}/Input/KeyCode.h"
    "${SRC}/Input/MouseButton.h"

    "${SRC}/Window/Window.h"
    "${SRC}/Window/Window.cpp"

    "${SRC}/Event/Event.h"
    "${SRC}/Event/Event.cpp"
    "${SRC}/Event/KeyEvent.h"
    "${SRC}/Event/KeyEvent.cpp"
    "${SRC}/Event/MouseEvent.h"
    "${SRC}/Event/MouseEvent.cpp"
    "${SRC}/Event/ApplicationEvent.h"
    "${SRC}/Event/ApplicationEvent.cpp"

    "${SRC}/Layer/Layer.h"
    "${SRC}/Layer/Layer.cpp"
    "${SRC}/Layer/LayerStack.h"
    "${SRC}/Layer/LayerStack.cpp"
    "${SRC}/UI/UILayer.h"
    "${SRC}/UI/UILayer.cpp"

    "${SRC}/Renderer/Renderer.h"
    "${SRC}/Renderer/Renderer.cpp"
    "${SRC}/Renderer/Renderer2D.h"
    "${SRC}/Renderer/Renderer2D.cpp"
    "${SRC}/Renderer/RenderCommand.h"
    "${SRC}/Renderer/RenderCommand.cpp"
    "${SRC}/Renderer/RendererAPI.h"
    "${SRC}/Renderer/RendererAPI.cpp"
    "${SRC}/Renderer/RendererAPI.OpenGL.h"
    "${SRC}/Renderer/RendererAPI.OpenGL.cpp"

    "${SRC}/Renderer/GraphicsContext.h"
    "${SRC}/Renderer/GraphicsContext.OpenGL.h"
    "${SRC}/Renderer/GraphicsContext.OpenGL.cpp"

    "${SRC}/Renderer/Buffer/VertexAttribute.h"
    "${SRC}/Renderer/Buffer/VertexAttribute.cpp"
    "${SRC}/Renderer/Buffer/VertexBuffer.h"
    "${SRC}/Renderer/Buffer/VertexBuffer.cpp"
    "${SRC}/Renderer/Buffer/VertexBuffer.OpenGL.h"
    "${SRC}/Renderer/Buffer/VertexBuffer.OpenGL.cpp"
    "${SRC}/Renderer/Buffer/VertexBufferLayout.h"
    "${SRC}/Renderer/Buffer/VertexBufferLayout.cpp"
    "${SRC}/Renderer/Buffer/IndexBuffer.h"
    "${SRC}/Renderer/Buffer/IndexBuffer.cpp"
    "${SRC}/Renderer/Buffer/IndexBuffer.OpenGL.h"
    "${SRC}/Renderer/Buffer/IndexBuffer.OpenGL.cpp"
    "${SRC}/Renderer/Buffer/VertexArray.h"
    "${SRC}/Renderer/Buffer/VertexArray.cpp"
    "${SRC}/Renderer/Buffer/VertexArray.OpenGL.h"
    "${SRC}/Renderer/Buffer/VertexArray.OpenGL.cpp"

    "${SRC}/Renderer/Framebuffer.h"
    "${SRC}/Renderer/Framebuffer.cpp"
    "${SRC}/Renderer/Framebuffer.OpenGL.h"
    "${SRC}/Renderer/Framebuffer.OpenGL.cpp"

    "${SRC}/Renderer/Shader/Shader.h"
    "${SRC}/Renderer/Shader/Shader.cpp"
    "${SRC}/Renderer/Shader/Shader.OpenGL.h"
    "${SRC}/Renderer/Shader/Shader.OpenGL.cpp"

    "${SRC}/Renderer/Texture/Texture.h"
    "${SRC}/Renderer/Texture/Texture.cpp"
    "${SRC}/Renderer/Texture/SubTexture2D.h"
    "${SRC}/Renderer/Texture/SubTexture2D.cpp"
    "${SRC}/Renderer/Texture/Texture.OpenGL.h"
    "${SRC}/Renderer/Texture/Texture.OpenGL.cpp"

    "${SRC}/Camera/Camera.h"
    "${SRC}/Camera/Camera.cpp"
    "${SRC}/Camera/CameraController.h"
    "${SRC}/Camera/CameraController.cpp"

    "${SRC}/Time/DeltaTime.h"
    "${SRC}/Profiler/Profiler.h"
    "${SRC}/Profiler/Profiler.cpp"

    "${SRC}/Scene/Scene.h"
    "${SRC}/Scene/Scene.cpp"
    "${SRC}/Scene/Components.h"
    "${SRC}/Scene/Components.cpp"
    "${SRC}/Scene/Entity.h"
    "${SRC}/Scene/Entity.cpp"
    "${SRC}/Scene/SceneCamera.h"
    "${SRC}/Scene/SceneCamera.cpp"
    "${SRC}/Scene/ScriptableEntity.h"
    "${SRC}/Scene/ScriptableEntity.cpp"
    "${SRC}/Scene/SceneSerializer.h"
    "${SRC}/Scene/SceneSerializer.cpp"

    "${SRC}/Utils/Utils.h"
    "${SRC}/Utils/Utils.Windows.cpp"
)


target_include_directories(Zero PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${Stb_INCLUDE_DIR}"
)

target_link_libraries(Zero PUBLIC
    glm::glm 
    glad::glad 
    glfw
    spdlog::spdlog
    imgui::imgui
    EnTT::EnTT
    yaml-cpp::yaml-cpp
    imguizmo::imguizmo
)

target_compile_definitions(Zero PUBLIC
    ZR_ENABLE_ASSERTS
    ZR_PLATFORM_WINDOWS
    GLFW_INCLUDE_NONE
    GLM_ENABLE_EXPERIMENTAL
    IMGUI_IMPL_OPENGL_LOADER_GLAD
)

target_precompile_headers(Zero PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/${SRC}/zrpch.h"
)
