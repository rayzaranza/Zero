find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Stb REQUIRED)

set(ZR_SRC "src/Zero")

add_library(Zero STATIC
  "src/Zero.h"
  "${ZR_SRC}/Core/Core.h"
  "${ZR_SRC}/Core/EntryPoint.h"
  "${ZR_SRC}/Core/Types.h"

  "${ZR_SRC}/Math/Math.h"
  "${ZR_SRC}/Math/Math.cpp"

  "${ZR_SRC}/Application/Application.h"
	"${ZR_SRC}/Application/Application.cpp"

  "${ZR_SRC}/Logger/Logger.h"
  "${ZR_SRC}/Logger/Logger.cpp"

  "${ZR_SRC}/Input/Input.h"
  "${ZR_SRC}/Input/Input.cpp"
  "${ZR_SRC}/Input/KeyCode.h"
  "${ZR_SRC}/Input/MouseButton.h"

  "${ZR_SRC}/Window/Window.h"
  "${ZR_SRC}/Window/Window.cpp"

  "${ZR_SRC}/Event/Event.h"
  "${ZR_SRC}/Event/Event.cpp"
  "${ZR_SRC}/Event/KeyEvent.h"
  "${ZR_SRC}/Event/KeyEvent.cpp"
  "${ZR_SRC}/Event/MouseEvent.h"
  "${ZR_SRC}/Event/MouseEvent.cpp"
  "${ZR_SRC}/Event/ApplicationEvent.h"
  "${ZR_SRC}/Event/ApplicationEvent.cpp"

  "${ZR_SRC}/Layer/Layer.h"
  "${ZR_SRC}/Layer/Layer.cpp"
  "${ZR_SRC}/Layer/LayerStack.h"
  "${ZR_SRC}/Layer/LayerStack.cpp"
  "${ZR_SRC}/UI/UILayer.h"
  "${ZR_SRC}/UI/UILayer.cpp"

  "${ZR_SRC}/Renderer/Renderer.h"
  "${ZR_SRC}/Renderer/Renderer.cpp"
  "${ZR_SRC}/Renderer/Renderer2D.h"
  "${ZR_SRC}/Renderer/Renderer2D.cpp"
  "${ZR_SRC}/Renderer/RenderCommand.h"
  "${ZR_SRC}/Renderer/RenderCommand.cpp"
  "${ZR_SRC}/Renderer/RendererAPI.h"
  "${ZR_SRC}/Renderer/RendererAPI.cpp"
  "${ZR_SRC}/Renderer/RendererAPI.OpenGL.h"
  "${ZR_SRC}/Renderer/RendererAPI.OpenGL.cpp"

  "${ZR_SRC}/Renderer/GraphicsContext.h"
  "${ZR_SRC}/Renderer/GraphicsContext.OpenGL.h"
  "${ZR_SRC}/Renderer/GraphicsContext.OpenGL.cpp"

  "${ZR_SRC}/Renderer/Buffer/VertexAttribute.h"
  "${ZR_SRC}/Renderer/Buffer/VertexAttribute.cpp"
  "${ZR_SRC}/Renderer/Buffer/VertexBuffer.h"
  "${ZR_SRC}/Renderer/Buffer/VertexBuffer.cpp"
  "${ZR_SRC}/Renderer/Buffer/VertexBuffer.OpenGL.h"
  "${ZR_SRC}/Renderer/Buffer/VertexBuffer.OpenGL.cpp"
  "${ZR_SRC}/Renderer/Buffer/VertexBufferLayout.h"
  "${ZR_SRC}/Renderer/Buffer/VertexBufferLayout.cpp"
  "${ZR_SRC}/Renderer/Buffer/IndexBuffer.h"
  "${ZR_SRC}/Renderer/Buffer/IndexBuffer.cpp"
  "${ZR_SRC}/Renderer/Buffer/IndexBuffer.OpenGL.h"
  "${ZR_SRC}/Renderer/Buffer/IndexBuffer.OpenGL.cpp"
  "${ZR_SRC}/Renderer/Buffer/VertexArray.h"
  "${ZR_SRC}/Renderer/Buffer/VertexArray.cpp"
  "${ZR_SRC}/Renderer/Buffer/VertexArray.OpenGL.h"
  "${ZR_SRC}/Renderer/Buffer/VertexArray.OpenGL.cpp"

  "${ZR_SRC}/Renderer/Framebuffer.h"
  "${ZR_SRC}/Renderer/Framebuffer.cpp"
  "${ZR_SRC}/Renderer/Framebuffer.OpenGL.h"
  "${ZR_SRC}/Renderer/Framebuffer.OpenGL.cpp"


  "${ZR_SRC}/Renderer/Shader/Shader.h"
  "${ZR_SRC}/Renderer/Shader/Shader.cpp"
  "${ZR_SRC}/Renderer/Shader/Shader.OpenGL.h"
  "${ZR_SRC}/Renderer/Shader/Shader.OpenGL.cpp"

  "${ZR_SRC}/Renderer/Texture/Texture.h"
  "${ZR_SRC}/Renderer/Texture/Texture.cpp"
  "${ZR_SRC}/Renderer/Texture/SubTexture2D.h"
  "${ZR_SRC}/Renderer/Texture/SubTexture2D.cpp"
  "${ZR_SRC}/Renderer/Texture/Texture.OpenGL.h"
  "${ZR_SRC}/Renderer/Texture/Texture.OpenGL.cpp"

  "${ZR_SRC}/Camera/Camera.h"
  "${ZR_SRC}/Camera/Camera.cpp"
  "${ZR_SRC}/Camera/CameraController.h"
  "${ZR_SRC}/Camera/CameraController.cpp"

  "${ZR_SRC}/Time/DeltaTime.h"
  "${ZR_SRC}/Profiler/Profiler.h"
  "${ZR_SRC}/Profiler/Profiler.cpp"
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
)

target_compile_definitions(Zero PUBLIC
  "ZR_ENABLE_ASSERTS"
  "ZR_PLATFORM_WINDOWS"
  "GLFW_INCLUDE_NONE"
  "IMGUI_IMPL_OPENGL_LOADER_GLAD"
)

target_precompile_headers(Zero PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/${ZR_SRC}/zrpch.h")
