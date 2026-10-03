#include "Zero/Scene/SceneSerializer.h"
#include "Zero/Scene/Components.h"
#include "Zero/Scene/Entity.h"

#include <fstream>


Zero::SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : m_Scene{ scene }
{
}


void Zero::SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity)
{
    out << YAML::BeginMap;
    out << YAML::Key << "Entity" << YAML::Value << "12383763562457";

    if (entity.HasComponent<TagComponent>())
    {
        out << YAML::Key << "TagComponent";
        out << YAML::BeginMap;
        out << YAML::Key << "Tag" << YAML::Value << entity.GetComponent<TagComponent>().Tag;
        out << YAML::EndMap;
    }

    if (entity.HasComponent<TransformComponent>())
    {
        const TransformComponent& transform{ entity.GetComponent<TransformComponent>() };

        out << YAML::Key << "TransformComponent";
        out << YAML::BeginMap;
        out << YAML::Key << "Translation" << YAML::Value << transform.Translation;
        out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
        out << YAML::Key << "Scale" << YAML::Value << transform.Scale;
        out << YAML::EndMap;
    }

    if (entity.HasComponent<CameraComponent>())
    {
        const CameraComponent& cameraComponent{ entity.GetComponent<CameraComponent>() };
        const SceneCamera& camera{ cameraComponent.Camera };

        out << YAML::Key << "CameraComponent";
        out << YAML::BeginMap;
        out << YAML::Key << "Camera" << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "ProjectionType" << YAML::Value << static_cast<int>(camera.GetProjectionType());
        out << YAML::Key << "PerspectiveFOV" << YAML::Value << cameraComponent.Camera.GetPerspectiveVerticalFOV();
        out << YAML::Key << "PerspectiveNearClip" << YAML::Value << camera.GetPerspectiveNearClip();
        out << YAML::Key << "PerspectiveFarClip" << YAML::Value << camera.GetPerspectiveFarClip();
        out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
        out << YAML::Key << "OrthographicNearClip" << YAML::Value << camera.GetOrthographicNearClip();
        out << YAML::Key << "OrthographicFarClip" << YAML::Value << camera.GetOrthographicFarClip();
        out << YAML::EndMap;
        out << YAML::Key << "IsMain" << YAML::Value << cameraComponent.IsMain;
        out << YAML::Key << "IsAspectRatioFixed" << YAML::Value << cameraComponent.IsAspectRatioFixed;
        out << YAML::EndMap;
    }

    if (entity.HasComponent<SpriteComponent>())
    {
        out << YAML::Key << "SpriteComponent";
        out << YAML::BeginMap;
        out << YAML::Key << "Color" << YAML::Value << entity.GetComponent<SpriteComponent>().Color;
        out << YAML::EndMap;
    }

    out << YAML::EndMap;
}


void Zero::SceneSerializer::Serialize(const std::string& filePath)
{
    YAML::Emitter out{};
    out << YAML::BeginMap;
    out << YAML::Key << "Scene" << YAML::Value << "Untitled";
    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

    m_Scene->m_Registry.view<entt::entity>().each([&](entt::entity entityID) {
        const Entity entity{ entityID, m_Scene.get() };
        if (!entity)
        {
            return;
        }

        SerializeEntity(out, entity);
    });

    out << YAML::EndSeq;
    out << YAML::EndMap;
    std::ofstream fout{ filePath };
    fout << out.c_str();
}


bool Zero::SceneSerializer::Deserialize(const std::string& filePath)
{
    const std::ifstream stream{ filePath };
    std::stringstream stringStream{};
    stringStream << stream.rdbuf();
    const YAML::Node& data{ YAML::Load(stringStream.str()) };

    if (!data["Scene"])
    {
        return false;
    }

    const std::string& sceneName{ data["Scene"].as<std::string>() };
    ZR_CORE_LOG("Deserializing scene '{0}'", sceneName);

    const YAML::Node& entities{ data["Entities"] };
    if (entities)
    {
        for (const YAML::Node& entity : entities)
        {
            std::string name{};
            const YAML::Node& tagComponent{ entity["TagComponent"] };
            if (tagComponent)
            {
                name = tagComponent["Tag"].as<std::string>();
            }

            Entity deserializedEntity{ m_Scene->CreateEntity(name) };

            const YAML::Node& transformComponentNode{ entity["TransformComponent"] };
            if (transformComponentNode)
            {
                TransformComponent& transformComponent{ deserializedEntity.GetComponent<TransformComponent>() };
                transformComponent.Translation = transformComponentNode["Translation"].as<glm::vec3>();
                transformComponent.Rotation = transformComponentNode["Rotation"].as<glm::vec3>();
                transformComponent.Scale = transformComponentNode["Scale"].as<glm::vec3>();
            }

            const YAML::Node& cameraComponentNode{ entity["CameraComponent"] };
            if (cameraComponentNode)
            {
                const YAML::Node& cameraNode{ cameraComponentNode["Camera"] };
                CameraComponent& cameraComponent{ deserializedEntity.AddComponent<CameraComponent>() };
                cameraComponent.Camera.SetProjectionType(
                    static_cast<SceneCamera::ProjectionType>(cameraNode["ProjectionType"].as<int>()));
                cameraComponent.Camera.SetPerspectiveVerticalFOV(cameraNode["PerspectiveFOV"].as<float>());
                cameraComponent.Camera.SetPerspectiveNearClip(cameraNode["PerspectiveNearClip"].as<float>());
                cameraComponent.Camera.SetPerspectiveFarClip(cameraNode["PerspectiveFarClip"].as<float>());

                cameraComponent.Camera.SetOrthographicSize(cameraNode["OrthographicSize"].as<float>());
                cameraComponent.Camera.SetOrthographicNearClip(cameraNode["OrthographicNearClip"].as<float>());
                cameraComponent.Camera.SetOrthographicFarClip(cameraNode["OrthographicFarClip"].as<float>());

                cameraComponent.IsMain = cameraComponentNode["IsMain"].as<bool>();
                cameraComponent.IsAspectRatioFixed = cameraComponentNode["IsAspectRatioFixed"].as<bool>();
            }

            const YAML::Node& spriteComponentNode{ entity["SpriteComponent"] };
            if (spriteComponentNode)
            {
                SpriteComponent& spriteComponent{ deserializedEntity.AddComponent<SpriteComponent>() };
                spriteComponent.Color = spriteComponentNode["Color"].as<glm::vec4>();
            }

            const uint64_t& uuid{ entity["Entity"].as<uint64_t>() };
            ZR_CORE_LOG("Deserialized entity with ID = {0}, name = {1}", uuid, name);
        }
    }
    return true;
}


void Zero::SceneSerializer::SerializeRuntime(const std::string& filePath)
{
    ZR_CORE_ASSERT(false, "Not implemented");
}


bool Zero::SceneSerializer::DeserializeRuntime(const std::string& filePath)
{
    ZR_CORE_ASSERT(false, "Not implemented");
    return false;
}


YAML::Emitter& Zero::operator<<(YAML::Emitter& out, const glm::vec2& vector)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vector.x << vector.y << YAML::EndSeq;
    return out;
}


YAML::Emitter& Zero::operator<<(YAML::Emitter& out, const glm::vec3& vector)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;
    return out;
}


YAML::Emitter& Zero::operator<<(YAML::Emitter& out, const glm::vec4& vector)
{
    out << YAML::Flow;
    out << YAML::BeginSeq << vector.x << vector.y << vector.z << vector.w << YAML::EndSeq;
    return out;
}
