#include "Zero/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Zero
{
    class OpenGLShader : public Shader
    {
      public:
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

      private:
        uint32_t m_Id {};
    };
}
