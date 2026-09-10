#include "Zero/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;
typedef unsigned int GLuint;

namespace Zero
{
    constexpr int MAX_SHADERS_SUPPORTED{ 2 };

    class OpenGLShader : public Shader
    {
      public:
        OpenGLShader(const std::string& filePath);
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader() override;

      public:
        virtual void Bind() const override;
        virtual void Unbind() const override;

      public:
        void SetUniform(const std::string& name, const glm::mat4& matrix) const;
        void SetUniform(const std::string& name, const glm::vec4& vector) const;
        void SetUniform(const std::string& name, const glm::vec3& vector) const;
        void SetUniform(const std::string& name, const glm::vec2& vector) const;
        void SetUniform(const std::string& name, float value) const;
        void SetUniform(const std::string& name, int value) const;

      private:
        std::string ReadFile(const std::string& filePath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
        static bool CheckShaderErrors(GLuint shader);
        static bool CheckProgramErrors(GLuint program, const std::array<GLuint, MAX_SHADERS_SUPPORTED>& shaderIds);
        static GLenum StringToShaderType(const std::string& type);

      private:
        uint32_t m_Id{};
    };
}
