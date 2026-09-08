#pragma once

namespace Zero
{
    class Shader
    {
      public:
        virtual ~Shader() = default;

      public:
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

      public:
        static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
    };
}
