#include "UILayer.h"

#include <imgui.h>

#include "Application/Application.h"
#include "ImGui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

namespace Zero
{
    UILayer::UILayer() : Layer { "UILayer" }
    {}

    UILayer::~UILayer()
    {}

    void UILayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io { ImGui::GetIO() };
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void UILayer::OnDetach()
    {}

    void UILayer::OnUpdate()
    {
        ImGuiIO& io { ImGui::GetIO() };
        float time { static_cast<float>(glfwGetTime()) };
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        const Window& window { Application::Get().GetWindow() };
        io.DisplaySize = ImVec2 { static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()) };
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool showDebugWindow { true };
        ImGui::ShowDemoWindow(&showDebugWindow);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UILayer::OnEvent(Event& event)
    {}
}
