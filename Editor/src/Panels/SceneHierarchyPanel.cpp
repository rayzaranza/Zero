#include "SceneHierarchyPanel.h"
#include <entt/entt.hpp>
#include <imgui.h>
#include <imgui_internal.h>


Zero::SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) : m_Context{ context }, m_SelectionContext{}
{
}


void Zero::SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
{
    m_Context = context;
    m_SelectionContext = {};
}


static void DrawVector3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
{
    ImGuiIO& io{ ImGui::GetIO() };
    auto fontBold{ io.Fonts->Fonts[0] };

    ImGui::PushID(label.c_str());
    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0.0f, 0.0f });
    const float lineHeight{ GImGui->FontSize + GImGui->Style.FramePadding.y * 2.0f };
    const ImVec2 buttonSize{ lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.7f, 0.08f, 0.12f, 1.0f });

    ImGui::PushFont(fontBold);
    if (ImGui::Button("X", buttonSize))
    {
        values.x = resetValue;
    }
    ImGui::PopFont();

    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.4f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.15f, 0.62f, 0.2f, 1.0f });

    ImGui::PushFont(fontBold);
    if (ImGui::Button("Y", buttonSize))
    {
        values.y = resetValue;
    }
    ImGui::PopFont();

    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.18f, 0.7f, 1.0f });

    ImGui::PushFont(fontBold);
    if (ImGui::Button("Z", buttonSize))
    {
        values.z = resetValue;
    }
    ImGui::PopFont();

    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::Columns(1);
    ImGui::PopID();
}


template <typename T, typename UIFunction>
static void DrawComponent(const std::string& name, Zero::Entity entity, UIFunction uiFunction)
{
    if (entity.HasComponent<T>())
    {
        ImGui::PushID(name.c_str());
        T& component{ entity.GetComponent<T>() };
        const ImVec2& contentRegionAvailable{ ImGui::GetContentRegionAvail() };
        const ImGuiTreeNodeFlags treeNodeFlags{ ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowOverlap |
                                                ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth |
                                                ImGuiTreeNodeFlags_FramePadding };
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4.0f, 4.0f });
        const float lineHeight{ GImGui->FontSize + GImGui->Style.FramePadding.y * 2.0f };
        ImGui::Separator();
        const bool isOpen{ ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str()) };
        ImGui::PopStyleVar();
        ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
        if (ImGui::Button("···", ImVec2{ lineHeight, lineHeight }))
        {
            ImGui::OpenPopup("ComponentSettings");
        }

        bool shouldRemoveComponent{ false };
        if (ImGui::BeginPopup("ComponentSettings"))
        {
            if (ImGui::MenuItem("Remove component"))
            {
                shouldRemoveComponent = true;
            }
            ImGui::EndPopup();
        }

        if (isOpen)
        {
            uiFunction(component);
            ImGui::TreePop();
        }

        if (shouldRemoveComponent)
        {
            entity.RemoveComponent<T>();
        }
        ImGui::PopID();
    }
}


void Zero::SceneHierarchyPanel::OnUIRender()
{
    DrawSceneHierarchyPanel();
    DrawPropertiesPanel();
}


void Zero::SceneHierarchyPanel::DrawEntityNode(Entity entity)
{
    const std::string& tag{ entity.GetComponent<TagComponent>().Tag };
    const ImGuiTreeNodeFlags selectedFlag{ m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0 };
    ImGuiTreeNodeFlags flags{ selectedFlag | ImGuiTreeNodeFlags_OpenOnArrow };
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    const bool isExpanded{ ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str()) };

    if (ImGui::IsItemClicked())
    {
        m_SelectionContext = entity;
    }

    bool isEntityDeleted{ false };

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::MenuItem("Destroy Entity"))
        {
            isEntityDeleted = true;
        }
        ImGui::EndPopup();
    }

    if (isExpanded)
    {
        ImGui::TreePop();
    }

    if (isEntityDeleted)
    {
        m_Context->DestroyEntity(entity);

        if (m_SelectionContext == entity)
        {
            m_SelectionContext = {};
        }
    }
}


void Zero::SceneHierarchyPanel::DrawComponents(Entity entity)
{
    if (entity.HasComponent<TagComponent>())
    {
        std::string& tag{ entity.GetComponent<TagComponent>().Tag };
        char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        strcpy_s(buffer, sizeof(buffer), tag.c_str());

        if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
        {
            tag = std::string(buffer);
        }
    }

    ImGui::SameLine();
    ImGui::PushItemWidth(-1);

    if (ImGui::Button("Add Component"))
    {
        ImGui::OpenPopup("AddComponent");
    }

    if (ImGui::BeginPopup("AddComponent"))
    {
        if (ImGui::MenuItem("Camera"))
        {
            m_SelectionContext.AddComponent<CameraComponent>();
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::MenuItem("Sprite"))
        {
            m_SelectionContext.AddComponent<SpriteComponent>();
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::PopItemWidth();

    DrawComponent<TransformComponent>("Transform", entity, [](TransformComponent& transform) {
        DrawVector3Control("Translation", transform.Translation);
        glm::vec3 rotation{ glm::degrees(transform.Rotation) };
        DrawVector3Control("Rotation", rotation);
        transform.Rotation = glm::radians(rotation);
        DrawVector3Control("Scale", transform.Scale, 1.0f);
    });

    DrawComponent<CameraComponent>("Camera", entity, [](CameraComponent& cameraComponent) {
        SceneCamera& camera{ cameraComponent.Camera };
        ImGui::Checkbox("Main Camera", &cameraComponent.IsMain);
        const char* projectionTypeStrings[]{ "Perspective", "Orthographic" };
        const char* currentProjectionTypeString{ projectionTypeStrings[static_cast<int>(camera.GetProjectionType())] };

        if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
        {
            for (int i{ 0 }; i < 2; ++i)
            {
                bool isSelected{ currentProjectionTypeString == projectionTypeStrings[i] };

                if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                {
                    currentProjectionTypeString = projectionTypeStrings[i];
                    camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
        {
            float perspectiveVerticalFOV{ glm::degrees(camera.GetPerspectiveVerticalFOV()) };
            float perspectiveNearClip{ camera.GetPerspectiveNearClip() };
            float perspectiveFarClip{ camera.GetPerspectiveFarClip() };

            if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFOV))
            {
                camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFOV));
            }

            if (ImGui::DragFloat("Near", &perspectiveNearClip))
            {
                camera.SetPerspectiveNearClip(perspectiveNearClip);
            }

            if (ImGui::DragFloat("Far", &perspectiveFarClip))
            {
                camera.SetPerspectiveFarClip(perspectiveFarClip);
            }
        }

        if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
        {
            float orthographicSize{ camera.GetOrthographicSize() };
            float orthographicNearClip{ camera.GetOrthographicNearClip() };
            float orthographicFarClip{ camera.GetOrthographicFarClip() };


            if (ImGui::DragFloat("Size", &orthographicSize))
            {
                camera.SetOrthographicSize(orthographicSize);
            }

            if (ImGui::DragFloat("Near", &orthographicNearClip))
            {
                camera.SetOrthographicNearClip(orthographicNearClip);
            }

            if (ImGui::DragFloat("Far", &orthographicFarClip))
            {
                camera.SetOrthographicFarClip(orthographicFarClip);
            }

            ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.IsAspectRatioFixed);
        }
    });

    DrawComponent<SpriteComponent>("Sprite", entity, [](auto& sprite) { ImGui::ColorEdit4("Color", glm::value_ptr(sprite.Color)); });
}


Zero::Entity Zero::SceneHierarchyPanel::GetSelectedEntity() const
{
    return m_SelectionContext;
}


void Zero::SceneHierarchyPanel::DrawPropertiesPanel()
{
    ImGui::Begin("Properties");
    if (m_SelectionContext)
    {
        DrawComponents(m_SelectionContext);
    }
    ImGui::End();
}


void Zero::SceneHierarchyPanel::DrawSceneHierarchyPanel()
{
    ImGuiIO& io{ ImGui::GetIO() };
    auto fontBold{ io.Fonts->Fonts[0] };

    ImGui::Begin("Scene Hierarchy");
    for (entt::entity entityID : m_Context->m_Registry.view<TagComponent>())
    {
        const Entity entity{ entityID, m_Context.get() };
        DrawEntityNode(entity);
    }

    if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
    {
        m_SelectionContext = {};
    }

    if (ImGui::BeginPopupContextWindow(0, 1 | ImGuiPopupFlags_NoOpenOverItems))
    {
        if (ImGui::MenuItem("Create Empty Entity"))
        {
            m_Context->CreateEntity("Empty Entity");
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}
