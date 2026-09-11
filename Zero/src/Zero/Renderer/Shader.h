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
        virtual const String& GetName() const = 0;

      public:
        virtual void SetMatrix4(const String& name, const Matrix4& matrix) const = 0;
        virtual void SetVector4(const String& name, const Vector4& vector) const = 0;
        virtual void SetVector3(const String& name, const Vector3& vector) const = 0;
        virtual void SetFloat2(const String& name, const Vector2& vector) const = 0;
        virtual void SetFloat(const String& name, F32 value) const = 0;
        virtual void SetInt(const String& name, I32 value) const = 0;

      public:
        static Ref<Shader> Create(const String& name, const String& vertexSource, const String& fragmentSource);
        static Ref<Shader> Create(const String& filePath);
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
        void Add(const String& name, const ShaderRef& shader);
        ShaderRef Load(const String& filePath);
        ShaderRef Load(const String& name, const String& filePath);
        ShaderRef Get(const String& name);
        Boolean Exists(const String& name) const;

      public:
        static Ref<ShaderLibrary> Create();

      private:
        Map<String, ShaderRef> m_Shaders{};
    };

    using ShaderLibraryRef = Ref<ShaderLibrary>;
}
