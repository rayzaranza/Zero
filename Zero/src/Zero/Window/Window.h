#pragma once
#include "Zero/Core/Core.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Renderer/GraphicsContext.h"
#include <glm/glm.hpp>

struct GLFWwindow;

namespace Zero {

using EventCallback = Function<void(Event&)>;

struct WindowProps {
  std::string Title{ "Zero" };
  glm::uvec2 Size{ 1920u, 1080u };
  EventCallback EventCallback{};
};

class Window {
public:
  Window(const WindowProps& props);
  ~Window();
  const glm::ivec2& GetSize() const;
  GLFWwindow* GetWindowHandle() const;
  void SetEventCallback(const EventCallback& callback);
  float GetAspectRatio() const;
  void OnUpdate();
  void Initialize();
  void Destroy();

private:
  void SetCallbacks();
  static void ErrorCallback(const int32_t error, const char* description);
  GLFWwindow* m_WindowHandle;
  GraphicsContext* m_RendererContext;
  WindowProps m_Props;
};

}
