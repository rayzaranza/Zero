#include "Zero/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Zero
{
    constexpr I16 MAX_SHADERS_SUPPORTED{ 2 };

    class OpenGLShader : public Shader
    {
      public:
        OpenGLShader(const String& filePath);
        OpenGLShader(const String& name, const String& vertexSource, const String& fragmentSource);
        virtual ~OpenGLShader() override;

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;
        inline virtual const String& GetName() const override { return m_Name; }

      public:
        virtual void SetMatrix4(const String& name, const Matrix4& matrix) const override;
        virtual void SetVector4(const String& name, const Vector4& vector) const override;
        virtual void SetVector3(const String& name, const Vector3& vector) const override;
        virtual void SetFloat2(const String& name, const Vector2& vector) const override;
        virtual void SetFloat(const String& name, F32 value) const override;
        virtual void SetInt(const String& name, I32 value) const override;

      private:
        String ReadFile(const String& filePath);
        Map<U32, String> PreProcess(const String& source);
        void Compile(const Map<U32, String>& shaderSources);
        static Boolean CheckShaderErrors(U32 shader);
        static Boolean CheckProgramErrors(U32 program, const FixedArray<U32, MAX_SHADERS_SUPPORTED>& shaderIds);
        static U32 StringToShaderType(const String& type);
        static String ExtractNameFromFilePath(const String& filePath);

      private:
        RendererID m_Id{};
        String m_Name{};
    };

}
