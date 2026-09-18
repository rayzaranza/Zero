#pragma once

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
        virtual void SetColor(const std::string& name, const glm::vec4& color) const = 0;
        virtual void SetMatrix4(const std::string& name, const glm::mat4& matrix) const = 0;
        virtual void SetVector4(const std::string& name, const glm::vec4& vector) const = 0;
        virtual void SetVector3(const std::string& name, const glm::vec3& vector) const = 0;
        virtual void SetVector2(const std::string& name, const glm::vec2& vector) const = 0;
        virtual void SetFloat(const std::string& name, const float value) const = 0;
        virtual void SetInt(const std::string& name, const int32_t value) const = 0;
        virtual void SetUnsignedInt(const std::string& name, const uint32_t value) const = 0;
        virtual void SetIntArray(const std::string& name, const int32_t* values, const uint32_t count) const = 0;
        virtual void SetUnsignedIntArray(const std::string& name, const uint32_t* values, const uint32_t count) const = 0;

        inline void SetTextureSlot(const std::string& name, const int32_t slot) const { SetInt(name, slot); }

      public:
        static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
        static Ref<Shader> Create(const std::string& filePath);
    };

    using ShaderRef = Ref<Shader>;

    //======================================================================================
    //  Shader Library
    //======================================================================================
    class ShaderLibrary
    {
      public:
        ShaderLibrary() = default;
        ~ShaderLibrary() = default;

      public:
        void Add(const ShaderRef& shader);
        void Add(const std::string& name, const ShaderRef& shader);
        ShaderRef Load(const std::string& filePath);
        ShaderRef Load(const std::string& name, const std::string& filePath);
        ShaderRef Get(const std::string& name);
        bool Exists(const std::string& name) const;

      public:
        static Ref<ShaderLibrary> Create();

      private:
        Map<std::string, ShaderRef> m_Shaders{};
    };

    using ShaderLibraryRef = Ref<ShaderLibrary>;
}
