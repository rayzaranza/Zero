#include "EditorLayer.h"
#include <ImGuizmo.h>
#include <Zero/Math/Math.h>
#include <Zero/Scene/SceneSerializer.h>
#include <Zero/Utils/Utils.h>
#include <glm/gtc/matrix_transform.hpp>


Zero::EditorLayer::EditorLayer()
    : Layer{ "EditorLayer" }
    , m_CameraController{ Application::Get().GetWindow().GetAspectRatio() }
    , m_Framebuffer{ Framebuffer::Create({ .Size{ 1280u, 720u } }) }
    , m_GizmoType{ ImGuizmo::OPERATION::TRANSLATE }
{
}


Zero::EditorLayer::~EditorLayer()
{
}


void Zero::EditorLayer::OnAttach()
{
    m_TextureCheckerboard = Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png");
    m_ActiveScene = CreateRef<Scene>();
    m_SceneHierarchyPanel.SetContext(m_ActiveScene);
}


void Zero::EditorLayer::OnDetach()
{
}


void Zero::EditorLayer::OnUpdate(const DeltaTime deltaTime)
{
    if (m_ViewportSize.x > 0u && m_ViewportSize.y > 0u &&
        (m_Framebuffer->GetSize().x != m_ViewportSize.x || m_Framebuffer->GetSize().y != m_ViewportSize.y))
    {
        m_Framebuffer->Resize(m_ViewportSize);
        m_CameraController.OnResize(m_ViewportSize);
        m_ActiveScene->OnViewportResize(m_ViewportSize);
    }

    if (m_IsViewportFocused)
    {
        m_CameraController.OnUpdate(deltaTime);
    }

    m_ActiveScene->OnUpdate(deltaTime);
}


void Zero::EditorLayer::OnRender()
{
    Renderer2D::ResetStats();
    m_Framebuffer->Bind();
    RenderCommand::SetClearColor({ 0.02f, 0.02f, 0.022f, 1.0f });
    RenderCommand::Clear();
    m_ActiveScene->OnRender();
    m_Framebuffer->Unbind();
}


void Zero::EditorLayer::OnUIRender()
{
    static bool isOpen{ true };
    static bool isFullscreenPersistant{ true };
    static bool isFullscreen{ isFullscreenPersistant };
    static ImGuiDockNodeFlags dockSpaceFlags{ ImGuiDockNodeFlags_None };
    static ImGuiWindowFlags windowFlags{ ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking };

    if (isFullscreen)
    {
        ImGuiViewport* viewport{ ImGui::GetMainViewport() };
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                       ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
    {
        windowFlags |= ImGuiWindowFlags_NoBackground;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
    ImGui::Begin("Zero DockSpace Demo", &isOpen, windowFlags);
    ImGui::PopStyleVar();

    if (isFullscreen)
    {
        ImGui::PopStyleVar(2);
    }

    ImGuiIO& io{ ImGui::GetIO() };
    ImGuiStyle& style{ ImGui::GetStyle() };
    const float minWindowWidth{ style.WindowMinSize.x };
    style.WindowMinSize.x = 256.0f;

    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockSpaceId{ ImGui::GetID("ZeroDockSpace") };
        ImGui::DockSpace(dockSpaceId, ImVec2{ 0.0f, 0.0f }, dockSpaceFlags);
    }

    style.WindowMinSize.x = minWindowWidth;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N"))
            {
                NewScene();
            }

            if (ImGui::MenuItem("Open...", "Ctrl+O"))
            {
                OpenScene();
            }

            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
            {
                SaveSceneAs();
            }

            if (ImGui::MenuItem("Exit", "Ctrl+Q"))
            {
                Application::Get().Close();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    m_SceneHierarchyPanel.OnUIRender();
    RenderSettingsPanel();
    RenderViewportPanel();

    ImGui::End();
}


void Zero::EditorLayer::OnEvent(Event& event)
{
    m_CameraController.OnEvent(event);
    EventDispatcher dispatcher{ event };
    dispatcher.Dispatch<KeyPressedEvent>(ZR_BIND_FUNCTION(EditorLayer::OnKeyPressed));
}


bool Zero::EditorLayer::OnKeyPressed(KeyPressedEvent& event)
{
    const KeyCode keyCode{ event.GetKeyCode() };
    const bool isControlPressed{ Input::IsKeyPressed(KeyCode::LEFT_CONTROL) || Input::IsKeyPressed(KeyCode::RIGHT_CONTROL) };
    const bool isShiftPressed{ Input::IsKeyPressed(KeyCode::LEFT_SHIFT) || Input::IsKeyPressed(KeyCode::RIGHT_SHIFT) };

    if (keyCode == KeyCode::N && isControlPressed)
    {
        NewScene();
    }
    else if (keyCode == KeyCode::O && isControlPressed)
    {
        OpenScene();
    }
    else if (keyCode == KeyCode::S && isControlPressed && isShiftPressed)
    {
        SaveSceneAs();
    }

    if (keyCode == KeyCode::Q)
    {
        m_GizmoType = -1;
    }
    else if (keyCode == KeyCode::W)
    {
        m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
    }
    else if (keyCode == KeyCode::E)
    {
        m_GizmoType = ImGuizmo::OPERATION::ROTATE;
    }
    else if (keyCode == KeyCode::R)
    {
        m_GizmoType = ImGuizmo::OPERATION::SCALE;
    }

    return false;
}


void Zero::EditorLayer::RenderViewportPanel()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
    ImGui::Begin("Viewport");

    m_IsViewportFocused = ImGui::IsWindowFocused();
    m_IsViewportHovered = ImGui::IsWindowHovered();
    Application::Get().GetUILayer()->SetIsBlockingEvents(!m_IsViewportFocused || !m_IsViewportHovered);

    const ImVec2 viewportPanelSize{ ImGui::GetContentRegionAvail() };
    m_ViewportSize = { static_cast<uint32_t>(viewportPanelSize.x), static_cast<uint32_t>(viewportPanelSize.y) };
    ImGui::Image(m_Framebuffer->GetColorAttachmentRendererID(), viewportPanelSize, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });

    Entity selectedEntity{ m_SceneHierarchyPanel.GetSelectedEntity() };

    if (selectedEntity && m_GizmoType != -1)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        const float windowWidth{ static_cast<float>(ImGui::GetWindowWidth()) };
        const float windowHeight{ static_cast<float>(ImGui::GetWindowHeight()) };
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

        Entity cameraEntity{ m_ActiveScene->GetMainCameraEntity() };
        Camera& camera{ cameraEntity.GetComponent<CameraComponent>().Camera };
        const glm::mat4 projection{ camera.GetProjection() };
        const glm::mat4 cameraView{ glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform()) };

        TransformComponent& transformComponent{ selectedEntity.GetComponent<TransformComponent>() };
        glm::mat4 transform{ transformComponent.GetTransform() };

        const bool isSnapping{ Input::IsKeyPressed(KeyCode::LEFT_CONTROL) };
        const float snapIncrement{ m_GizmoType == ImGuizmo::OPERATION::ROTATE ? 45.0f : 0.5f };
        const float snapIncrements[3]{ snapIncrement, snapIncrement, snapIncrement };

        ImGuizmo::Manipulate(glm::value_ptr(cameraView),
            glm::value_ptr(projection),
            static_cast<ImGuizmo::OPERATION>(m_GizmoType),
            ImGuizmo::LOCAL,
            glm::value_ptr(transform),
            nullptr,
            isSnapping ? snapIncrements : nullptr);

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 translation{};
            glm::vec3 rotation{};
            glm::vec3 scale{};
            Math::DecomposeTransform(transform, translation, rotation, scale);

            const glm::vec3 deltaRotation{ rotation - transformComponent.Rotation };
            transformComponent.Translation = translation;
            transformComponent.Rotation += deltaRotation;
            transformComponent.Scale = scale;
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}


void Zero::EditorLayer::RenderSettingsPanel()
{
    const RenderStats& stats{ Renderer2D::GetStats() };

    ImGui::Begin("Renderer2D Stats");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
    ImGui::End();
}


void Zero::EditorLayer::NewScene()
{
    m_ActiveScene = CreateRef<Scene>();
    m_ActiveScene->OnViewportResize(m_ViewportSize);
    m_SceneHierarchyPanel.SetContext(m_ActiveScene);
}


void Zero::EditorLayer::OpenScene()
{
    const std::string filePath{ FileDialog::OpenFile("Zero Scene (*.zero)\0*.zero\0") };
    if (!filePath.empty())
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResize(m_ViewportSize);
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);

        SceneSerializer serializer{ m_ActiveScene };
        serializer.Deserialize(filePath);
    }
}


void Zero::EditorLayer::SaveSceneAs() const
{
    const std::string filePath{ FileDialog::SaveFile("Zero Scene (*.zero)\0*.zero\0") };
    if (!filePath.empty())
    {
        SceneSerializer serializer{ m_ActiveScene };
        serializer.Serialize(filePath);
    }
}
