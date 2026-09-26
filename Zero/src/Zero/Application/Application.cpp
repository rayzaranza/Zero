#include "Application.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Input/Input.h"
#include "Zero/Renderer/Renderer.h"
#include <GLFW/glfw3.h>

Zero::Application* Zero::Application::s_Instance{ nullptr };

Zero::Application::Application(const std::string& name) : m_IsRunning{ true }, m_IsMinimized{ false }, m_LastFrameTime{ 0.0f } {
  ZR_CORE_ASSERT(s_Instance == nullptr, "Application already exists");
  s_Instance = this;

  m_Window = CreateScope<Window>(WindowProps{ .Title{ "Zero Editor" }, .Size{ 1280u, 720u } });
  m_Window->SetEventCallback(ZR_BIND_FUNCTION(Application::OnEvent));

  m_UILayer = new UILayer();
  PushOverlay(m_UILayer);

  Renderer::Initialize();
}

Zero::Application::~Application() {
  Renderer::Destroy();
}

void Zero::Application::OnEvent(Event& event) {
  EventDispatcher dispatcher{ event };
  dispatcher.Dispatch<WindowClosedEvent>(ZR_BIND_FUNCTION(Application::OnWindowClosed));
  dispatcher.Dispatch<WindowResizedEvent>(ZR_BIND_FUNCTION(Application::OnWindowResized));

  for (auto layer{ m_LayerStack.rbegin() }; layer != m_LayerStack.rend(); ++layer) {
    if (event.IsHandled)
      break;
    (*layer)->OnEvent(event);
  }
}

void Zero::Application::PushLayer(Layer* layer) {
  m_LayerStack.PushLayer(layer);
  layer->OnAttach();
}

void Zero::Application::PushOverlay(Layer* overlay) {
  m_LayerStack.PushOverlay(overlay);
  overlay->OnAttach();
}

void Zero::Application::Close() {
  m_IsRunning = false;
}

Zero::Application& Zero::Application::Get() {
  return *s_Instance;
}

const Zero::Window& Zero::Application::GetWindow() const {
  return *m_Window;
}

Zero::UILayer* Zero::Application::GetUILayer() const {
  return m_UILayer;
}

void Zero::Application::Run() {
  while (m_IsRunning) {
    const float time = static_cast<float>(glfwGetTime());
    DeltaTime deltaTime{ time - m_LastFrameTime };
    m_LastFrameTime = time;

    if (!m_IsMinimized) {
      for (Layer* layer : m_LayerStack)
        layer->OnUpdate(deltaTime);
      for (Layer* layer : m_LayerStack)
        layer->OnRender();

      m_UILayer->Begin();
      for (Layer* layer : m_LayerStack)
        layer->OnUIRender();
      m_UILayer->End();
    }
    m_Window->OnUpdate();
  }
}

bool Zero::Application::OnWindowClosed(WindowClosedEvent& event) {
  m_IsRunning = false;
  return true;
}

bool Zero::Application::OnWindowResized(WindowResizedEvent& event) {
  const glm::ivec2 size{ event.GetSize() };
  if (size.x == 0 || size.y == 0) {
    m_IsMinimized = true;
    return false;
  }

  Renderer::OnWindowResized(size);
  m_IsMinimized = false;
  return false;
}
