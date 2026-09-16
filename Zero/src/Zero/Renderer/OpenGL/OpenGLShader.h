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
        virtual void SetColor(const String& name, const glm::vec4& color) const override;
        virtual void SetMatrix4(const String& name, const glm::mat4& matrix) const override;
        virtual void SetVector4(const String& name, const glm::vec4& vector) const override;
        virtual void SetVector3(const String& name, const glm::vec3& vector) const override;
        virtual void SetVector2(const String& name, const glm::vec2& vector) const override;
        virtual void SetFloat(const String& name, const F32 value) const override;
        virtual void SetInt(const String& name, const I32 value) const override;
        virtual void SetUnsignedInt(const String& name, const U32 value) const override;
        virtual void SetIntArray(const String& name, const I32* values, const U32 count) const override;
        virtual void SetUnsignedIntArray(const String& name, const U32* values, const U32 count) const override;

      private:
        String ReadFile(const String& filePath);
        Map<U32, String> PreProcess(const String& source);
        void Compile(const Map<U32, String>& shaderSources);
        static bool CheckShaderErrors(U32 shader);
        static bool CheckProgramErrors(U32 program, const FixedArray<U32, MAX_SHADERS_SUPPORTED>& shaderIds);
        static U32 StringToShaderType(const String& type);
        static String ExtractNameFromFilePath(const String& filePath);

      private:
        RendererID m_Id{};
        String m_Name{};
    };

}
