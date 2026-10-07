#pragma once
#include "../Core/Types.h"

#include <memory>
#include <string>
#include <glm/glm.hpp>


struct GLFWwindow;


namespace Zero {


struct WindowProps
{
    std::string Title { "" };
    glm::ivec2 Size { 1920, 1080 };

    WindowProps() = default;
    WindowProps(const std::string& title, const glm::ivec2& size) : Title { title }, Size { size }
    {}
};


class Window
{
  public:
    Window(const WindowProps& props);
    ~Window();

  public:
    static Scope<Window> Create(const WindowProps& props);

  public:
    void Update() const;

  private:
    static void ErrorCallback(int error, const char* description);

  private:
    GLFWwindow* m_WindowHandle;
    WindowProps m_Props;
};


}
