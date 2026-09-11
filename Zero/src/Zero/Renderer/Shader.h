#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    //======================================================================================
    //  Shader
    //======================================================================================
    class Shader
    {
      public:
        virtual ~Shader() = default;

      public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual const std::string& GetName() const = 0;

      public:
        virtual void SetMatrix4(const std::string& name, const glm::mat4& matrix) const = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& vector) const = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& vector) const = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& vector) const = 0;
        virtual void SetFloat(const std::string& name, float value) const = 0;
        virtual void SetInt(const std::string& name, int value) const = 0;

      public:
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
        static Ref<Shader> Create(const std::string& filePath);
    };

    //======================================================================================
    //  Shader Library
    //======================================================================================
    class ShaderLibrary
    {
      public:
        ShaderLibrary() = default;
        ~ShaderLibrary() = default;

      public:
        void Add(const Ref<Shader>& shader);
        void Add(const std::string& name, const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& filePath);
        Ref<Shader> Load(const std::string& name, const std::string& filePath);
        Ref<Shader> Get(const std::string& name);
        bool Exists(const std::string& name) const;

      public:
        static Ref<ShaderLibrary> Create();

      private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders{};
    };
}
