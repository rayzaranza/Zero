#include "Zero/Scene/Scene.h"
#include "Zero/Scene/Components.h"
#include "Zero/Scene/Entity.h"
#include "Zero/Renderer/Renderer2D.h"


Zero::Scene::Scene()
{
}


Zero::Scene::~Scene()
{
}


void Zero::Scene::OnRuntimeUpdate(const DeltaTime deltaTime)
{
    const auto nativeScripts{ m_Registry.view<NativeScriptComponent>() };

    for (const auto [entity, nativeScript] : nativeScripts.each())
    {
        if (!nativeScript.Instance)
        {
            nativeScript.Instance = nativeScript.InstantiateScript();
            nativeScript.Instance->m_Entity = Entity{ entity, this };
            nativeScript.Instance->OnCreate();
        }

        nativeScript.Instance->OnUpdate(deltaTime);
    }
}


void Zero::Scene::OnRuntimeRender()
{
    Camera* cameraMain{ nullptr };
    glm::mat4 cameraTransform;

    const auto entitiesWithCamera{ m_Registry.view<const TransformComponent, CameraComponent>() };

    for (const auto [entity, transform, camera] : entitiesWithCamera.each())
    {
        if (camera.IsMain)
        {
            cameraMain = &camera.Camera;
            cameraTransform = transform.GetTransform();
            break;
        }
    }

    if (cameraMain)
    {
        Renderer2D::BeginScene(*cameraMain, cameraTransform);

        const auto entitiesWithSprite{ m_Registry.view<const TransformComponent, const SpriteComponent>() };
        for (const auto [entity, transform, sprite] : entitiesWithSprite.each())
        {
            Renderer2D::DrawQuad({ .Transform{ transform.GetTransform() }, .Color{ sprite.Color } });
        }

        Renderer2D::EndScene();
    }
}


void Zero::Scene::OnEditorUpdate(const DeltaTime deltaTime, EditorCamera& camera)
{
    camera.OnUpdate(deltaTime);
}


void Zero::Scene::OnEditorRender(EditorCamera& camera)
{
    Renderer2D::BeginScene(camera);

    const auto entitiesWithSprite{ m_Registry.view<const TransformComponent, const SpriteComponent>() };
    for (const auto [entity, transform, sprite] : entitiesWithSprite.each())
    {
        Renderer2D::DrawQuad({
            .Transform{ transform.GetTransform() },
            .Color{ sprite.Color },
            .EntityID{ static_cast<int32_t>(entity) },
        });
    }

    Renderer2D::EndScene();
}


void Zero::Scene::OnViewportResize(const glm::uvec2& size)
{
    m_ViewportSize = size;

    const auto cameras{ m_Registry.view<CameraComponent>() };
    for (auto [entity, cameraComponent] : cameras.each())
    {
        if (!cameraComponent.IsAspectRatioFixed)
        {
            cameraComponent.Camera.SetViewportSize(size);
        }
    }
}


Zero::Entity Zero::Scene::CreateEntity(const std::string& name)
{
    Entity entity{ m_Registry.create(), this };
    entity.AddComponent<TransformComponent>();
    entity.AddComponent<TagComponent>(name);

    return entity;
}


void Zero::Scene::DestroyEntity(Entity entity)
{
    m_Registry.destroy(entity);
}


Zero::Entity Zero::Scene::GetMainCameraEntity()
{
    for (auto [entity, camera] : m_Registry.view<const CameraComponent>().each())
    {
        if (camera.IsMain)
        {
            return Entity{ entity, this };
        }
    }

    return {};
}
