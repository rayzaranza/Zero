#pragma once
#include <memory>
#include "../Window/Window.h"
#include "../Core/Types.h"


namespace Zero {

class Application
{
  public:
    Application();
    ~Application();

  public:
    void Run() const;

  private:
    Scope<Window> m_Window;
    bool m_IsRunning { true };
};

}
