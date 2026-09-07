#pragma once

namespace Zero
{
    class Shader
    {
      public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

      public:
        void Bind() const;

      private:
        uint32_t m_Id;
    };
}
