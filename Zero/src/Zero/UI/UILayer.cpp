#include "Zero/UI/UILayer.h"
#include "Zero/Application/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <ImGuizmo.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


Zero::UILayer::UILayer() : Layer{ "UILayer" }, m_Time{ 0.0f }
{
}


void Zero::UILayer::OnAttach()
{
    Window& window{ Application::Get().GetWindow() };

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io{ ImGui::GetIO() };
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    constexpr float fontSize{ 16.0f };
    io.Fonts->AddFontFromFileTTF("D:/Zero/Editor/assets/fonts/Rubik/Rubik-Medium.ttf", fontSize);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("D:/Zero/Editor/assets/fonts/Rubik/Rubik-Regular.ttf", fontSize);

    ImGui::StyleColorsDark();

    GLFWwindow* windowHandle{ window.GetWindowHandle() };
    float xScale, yScale;
    glfwGetWindowContentScale(windowHandle, &xScale, &yScale);

    ImGuiStyle& style{ ImGui::GetStyle() };
    style.ScaleAllSizes(yScale);
    style.FontScaleDpi = yScale;

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    SetDarkThemeColors();

    ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}


void Zero::UILayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Zero::UILayer::OnUIRender()
{
}


void Zero::UILayer::OnEvent(Event& event)
{
    if (m_IsBlockingEvents)
    {
        ImGuiIO& io{ ImGui::GetIO() };
        event.IsHandled |= event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
        event.IsHandled |= event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
    }
}


void Zero::UILayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}


void Zero::UILayer::End()
{
    ImGuiIO& io{ ImGui::GetIO() };
    const glm::vec2& windowSize{ Application::Get().GetWindow().GetSize() };
    io.DisplaySize = ImVec2{ windowSize.x, windowSize.y };

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backupCurrentContext{ glfwGetCurrentContext() };
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }
}


void Zero::UILayer::SetIsBlockingEvents(const bool isBlocking)
{
    m_IsBlockingEvents = isBlocking;
}


void Zero::UILayer::SetDarkThemeColors()
{
    auto& colors{ ImGui::GetStyle().Colors };

    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    constexpr ImVec4 BACKGROUND_DEFAULT{ 0.2f, 0.205f, 0.21f, 1.0f };
    constexpr ImVec4 BACKGROUND_LIGHTER{ 0.3f, 0.305f, 0.31f, 1.0f };
    constexpr ImVec4 BACKGROUND_DARKER{ 0.15f, 0.1505f, 0.151f, 1.0f };

    colors[ImGuiCol_Header] = BACKGROUND_DEFAULT;
    colors[ImGuiCol_HeaderHovered] = BACKGROUND_LIGHTER;
    colors[ImGuiCol_HeaderActive] = BACKGROUND_DARKER;

    colors[ImGuiCol_Button] = BACKGROUND_DEFAULT;
    colors[ImGuiCol_ButtonHovered] = BACKGROUND_LIGHTER;
    colors[ImGuiCol_ButtonActive] = BACKGROUND_DARKER;

    colors[ImGuiCol_FrameBg] = BACKGROUND_DEFAULT;
    colors[ImGuiCol_FrameBgHovered] = BACKGROUND_LIGHTER;
    colors[ImGuiCol_FrameBgActive] = BACKGROUND_DARKER;

    colors[ImGuiCol_Tab] = BACKGROUND_DARKER;
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = BACKGROUND_DARKER;
    colors[ImGuiCol_TabUnfocusedActive] = BACKGROUND_DEFAULT;

    colors[ImGuiCol_TitleBg] = BACKGROUND_DARKER;
    colors[ImGuiCol_TitleBgActive] = BACKGROUND_DARKER;
    colors[ImGuiCol_TitleBgCollapsed] = BACKGROUND_DARKER;
}
