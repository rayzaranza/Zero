#pragma once
#include "Zero/Camera/Camera.h"
#include "Zero/Core/Core.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/Event.h"
#include "Zero/Layer/LayerStack.h"
#include "Zero/Time/DeltaTime.h"
#include "Zero/UI/UILayer.h"
#include "Zero/Window/Window.h"

namespace Zero {
  class Application {
  public:
    Application(const std::string& name = "Zero");
    virtual ~Application();
    void Run();
    void OnEvent(Event& event);
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void Close();
    static Application& Get();
    const Window& GetWindow() const;

  private:
    bool OnWindowClosed(WindowClosedEvent& event);
    bool OnWindowResized(WindowResizedEvent& event);
    Scope<Window> m_Window;
    bool m_IsRunning;
    bool m_IsMinimized;
    LayerStack m_LayerStack;
    UILayer* m_UILayer;
    float m_LastFrameTime;
    static Application* s_Instance;
  };

  Application* CreateApplication();
}
