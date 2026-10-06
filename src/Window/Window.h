#pragma once
#include <memory>
#include <string>
#include <glm/glm.hpp>


struct GLFWwindow;


namespace Zero {


struct WindowProps
{
    std::string Title { "Window" };
    glm::ivec2 Size { 1920, 1080 }; 
};


class Window
{
  public:
    explicit Window(const WindowProps& props = {});
    ~Window();

    void Update() const;

  private:
    GLFWwindow* m_WindowHandle;
    WindowProps m_Props;
};


} // Zero
