#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class Shader
    {
      public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

      public:
        void Bind() const;
        void Unbind() const;
        void SetUniform(const std::string& name, const glm::mat4& matrix) const;

      private:
        uint32_t m_Id {};
    };
}
