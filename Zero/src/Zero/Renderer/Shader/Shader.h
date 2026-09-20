#pragma once
#include <glm/glm.hpp>

namespace Zero {
  class Shader {
  public:
    virtual ~Shader() = default;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual const std::string& GetName() const = 0;
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
    static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    static Ref<Shader> Create(const std::string& filePath);
  };

  class ShaderLibrary {
  public:
    ShaderLibrary() = default;
    ~ShaderLibrary() = default;
    void Add(const Ref<Shader>& shader);
    void Add(const std::string& name, const Ref<Shader>& shader);
    Ref<Shader> Load(const std::string& filePath);
    Ref<Shader> Load(const std::string& name, const std::string& filePath);
    Ref<Shader> Get(const std::string& name);
    bool Exists(const std::string& name) const;
    static Ref<ShaderLibrary> Create();

  private:
    Map<std::string, Ref<Shader>> m_Shaders{};
  };
}
