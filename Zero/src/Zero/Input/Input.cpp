#include "Input.h"

#include <GLFW/glfw3.h>

#include "Zero/Application/Application.h"

namespace Zero
{
    Input* Input::s_Instance{ new Input() };

    Boolean Input::IsKeyPressed(I32 keyCode)
    {
        GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
        const I32 state{ glfwGetKey(window, keyCode) };
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    Boolean Input::IsMouseButtonPressed(I32 button)
    {
        GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
        const I32 state{ glfwGetMouseButton(window, button) };
        return state == GLFW_PRESS;
    }

    Vector2 Input::GetMousePosition()
    {
        GLFWwindow* window{ Application::Get().GetWindow().GetWindowHandle() };
        F64 x, y;
        glfwGetCursorPos(window, &x, &y);
        return Vector2{ static_cast<F32>(x), static_cast<F32>(y) };
    }

}
