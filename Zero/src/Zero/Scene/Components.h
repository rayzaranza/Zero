#pragma once
#include "SceneCamera.h"
#include "ScriptableEntity.h"


namespace Zero {


struct TagComponent
{
    std::string Tag{};

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& tag);
};


struct TransformComponent
{
    glm::vec3 Translation{ 0.0f };
    glm::vec3 Rotation{ 0.0f };
    glm::vec3 Scale{ 1.0f };

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::vec3& translation);

    glm::mat4 GetTransform() const;
};


struct SpriteComponent
{
    glm::vec4 Color{ 1.0f };

    SpriteComponent() = default;
    SpriteComponent(const SpriteComponent&) = default;
    SpriteComponent(const glm::vec4& color);
};


struct CameraComponent
{
    SceneCamera Camera{};
    bool IsMain{ true };
    bool IsAspectRatioFixed{ false };

    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
};


struct NativeScriptComponent
{
    ScriptableEntity* Instance{ nullptr };
    ScriptableEntity* (*InstantiateScript)();
    void (*DestroyScript)(NativeScriptComponent*);

    template <typename T> void Bind();
};


}


template <typename T>
void Zero::NativeScriptComponent::Bind()
{
    InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
    DestroyScript = [](NativeScriptComponent* nativeScript) {
        delete nativeScript->Instance;
        nativeScript->Instance = nullptr;
    };
}
