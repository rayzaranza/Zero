#include "Shader.h"
#include <glm/glm.hpp>

namespace Zero {
  constexpr int16_t MAX_SHADERS_SUPPORTED{ 2 };

  class ShaderOpenGL : public Shader {
  public:
    ShaderOpenGL(const std::string& filePath);
    ShaderOpenGL(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
    virtual ~ShaderOpenGL() override;
    virtual void Bind() const override;
    virtual void Unbind() const override;
    virtual const std::string& GetName() const override;
    virtual void SetColor(const std::string& name, const glm::vec4& color) const override;
    virtual void SetMatrix4(const std::string& name, const glm::mat4& matrix) const override;
    virtual void SetVector4(const std::string& name, const glm::vec4& vector) const override;
    virtual void SetVector3(const std::string& name, const glm::vec3& vector) const override;
    virtual void SetVector2(const std::string& name, const glm::vec2& vector) const override;
    virtual void SetFloat(const std::string& name, const float value) const override;
    virtual void SetInt(const std::string& name, const int32_t value) const override;
    virtual void SetUnsignedInt(const std::string& name, const uint32_t value) const override;
    virtual void SetIntArray(const std::string& name, const int32_t* values, const uint32_t count) const override;
    virtual void SetUnsignedIntArray(const std::string& name, const uint32_t* values, const uint32_t count) const override;

  private:
    std::string ReadFile(const std::string& filePath);
    Map<uint32_t, std::string> PreProcess(const std::string& source);
    void Compile(const Map<uint32_t, std::string>& shaderSources);
    static bool CheckShaderErrors(uint32_t shader);
    static bool CheckProgramErrors(uint32_t program, const FixedArray<uint32_t, MAX_SHADERS_SUPPORTED>& shaderIds);
    static uint32_t StringToShaderType(const std::string& type);
    static std::string ExtractNameFromFilePath(const std::string& filePath);
    uint32_t m_Id{};
    std::string m_Name{};
  };

}
