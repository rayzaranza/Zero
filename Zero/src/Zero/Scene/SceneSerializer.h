#pragma once
#include "Scene.h"
#include <yaml-cpp/yaml.h>


namespace Zero {

class SceneSerializer
{
  public:
    SceneSerializer(const Ref<Scene>& scene);

  public:
    void SerializeEntity(YAML::Emitter& out, Entity entity);
    void Serialize(const std::string& filePath);
    bool Deserialize(const std::string& filePath);
    void SerializeRuntime(const std::string& filePath);
    bool DeserializeRuntime(const std::string& filePath);

  private:
    Ref<Scene> m_Scene;
};


YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& vector);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vector);
YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vector);


}


namespace YAML {


template <>
struct convert<glm::vec3>
{
    static Node encode(const glm::vec3& vector)
    {
        Node node;
        node.push_back(vector.x);
        node.push_back(vector.y);
        node.push_back(vector.z);
        return node;
    }

    static bool decode(const Node& node, glm::vec3& vector)
    {
        if (!node.IsSequence() || node.size() != 3)
        {
            return false;
        }
        vector.x = node[0].as<float>();
        vector.y = node[1].as<float>();
        vector.z = node[2].as<float>();
        return true;
    }
};


template <>
struct convert<glm::vec4>
{
    static Node encode(const glm::vec4& vector)
    {
        Node node;
        node.push_back(vector.x);
        node.push_back(vector.y);
        node.push_back(vector.z);
        node.push_back(vector.w);
        return node;
    }

    static bool decode(const Node& node, glm::vec4& vector)
    {
        if (!node.IsSequence() || node.size() != 4)
        {
            return false;
        }
        vector.x = node[0].as<float>();
        vector.y = node[1].as<float>();
        vector.z = node[2].as<float>();
        vector.w = node[3].as<float>();
        return true;
    }
};


}
