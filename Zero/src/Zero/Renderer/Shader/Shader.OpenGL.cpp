#include "Shader.OpenGL.h"
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Zero::ShaderOpenGL::ShaderOpenGL(const std::string& filePath) : m_Name{ ExtractNameFromFilePath(filePath) } {
  const std::string source{ ReadFile(filePath) };
  const Map<uint32_t, std::string> shaderSources{ PreProcess(source) };
  ShaderOpenGL::Compile(shaderSources);
}

Zero::ShaderOpenGL::ShaderOpenGL(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : m_Name{ name } {
  const Map<uint32_t, std::string> shaderSources{ { GL_VERTEX_SHADER, vertexSource }, { GL_FRAGMENT_SHADER, fragmentSource } };
  ShaderOpenGL::Compile(shaderSources);
}

Zero::ShaderOpenGL::~ShaderOpenGL() {
  glDeleteProgram(m_Id);
}

void Zero::ShaderOpenGL::Compile(const Map<uint32_t, std::string>& shaderSources) {
  const uint32_t program{ glCreateProgram() };
  ZR_CORE_ASSERT(shaderSources.size() <= MAX_SHADERS_SUPPORTED, "Only 2 shaders are supported");

  FixedArray<uint32_t, MAX_SHADERS_SUPPORTED> shaderIds{};
  int32_t shaderIdIndex{ 0 };

  for (auto& [type, source] : shaderSources) {
    const uint32_t shader{ glCreateShader(type) };
    const char* sourceRaw{ source.c_str() };
    glShaderSource(shader, 1, &sourceRaw, 0);
    glCompileShader(shader);

    const bool isCompiled{ CheckShaderErrors(shader) };
    ZR_CORE_ASSERT(isCompiled, "Shader compilation error");

    if (!isCompiled)
      continue;

    glAttachShader(program, shader);
    shaderIds[shaderIdIndex++] = shader;
  }

  glLinkProgram(program);
  const bool isLinked{ CheckProgramErrors(program, shaderIds) };
  ZR_CORE_ASSERT(isLinked, "Shader linking error");

  if (!isLinked)
    return;

  for (uint32_t shaderId : shaderIds) {
    glDetachShader(program, shaderId);
    glDeleteShader(shaderId);
  }

  m_Id = program;
}

std::string Zero::ShaderOpenGL::ReadFile(const std::string& filePath) {
  std::string result{};
  std::ifstream inputStream{ filePath, std::ios::in | std::ios::binary };

  if (!inputStream.is_open()) {
    ZR_CORE_ERROR("Could not open file: {0}", filePath);
    return result;
  }

  inputStream.seekg(0, std::ios::end);
  result.resize(inputStream.tellg());
  inputStream.seekg(0, std::ios::beg);
  inputStream.read(&result[0], result.size());
  inputStream.close();
  return result;
}

Zero::Map<uint32_t, std::string> Zero::ShaderOpenGL::PreProcess(const std::string& source) {
  Map<uint32_t, std::string> shaderSources{};
  const char* typeToken{ "#type" };
  const size_t typeTokenLength{ strlen(typeToken) };
  size_t position{ source.find(typeToken, 0) };

  while (position != std::string::npos) {
    const size_t endOfLine{ source.find_first_of("\r\n", position) };
    ZR_CORE_ASSERT(endOfLine != std::string::npos, "Syntax error");

    if (endOfLine == std::string::npos)
      break;

    const size_t typeNameBegin{ position + typeTokenLength + 1 };
    const std::string typeName{ source.substr(typeNameBegin, endOfLine - typeNameBegin) };
    const uint32_t type{ StringToShaderType(typeName) };
    ZR_CORE_ASSERT(type, "Invalid Shader Type");

    const size_t nextLinePosition{ source.find_first_of("\r\n", endOfLine) };
    position = source.find(typeToken, nextLinePosition);

    if (!type)
      continue;

    const size_t blockEnd{ position == std::string::npos ? source.size() : position };
    shaderSources[type] = source.substr(nextLinePosition, blockEnd - nextLinePosition);
  }

  return shaderSources;
}

void Zero::ShaderOpenGL::Bind() const {
  glUseProgram(m_Id);
}

void Zero::ShaderOpenGL::Unbind() const {
  glUseProgram(0);
}

const std::string& Zero::ShaderOpenGL::GetName() const {
  return m_Name;
}

void Zero::ShaderOpenGL::SetColor(const std::string& name, const glm::vec4& color) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform4f(location, color.r, color.g, color.b, color.a);
}

void Zero::ShaderOpenGL::SetMatrix4(const std::string& name, const glm::mat4& matrix) const {
  int32_t location{};
  location = glGetUniformLocation(m_Id, name.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Zero::ShaderOpenGL::SetVector4(const std::string& name, const glm::vec4& vector) const {
  int32_t location{};
  location = glGetUniformLocation(m_Id, name.c_str());
  glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Zero::ShaderOpenGL::SetVector3(const std::string& name, const glm::vec3& vector) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform3f(location, vector.x, vector.y, vector.z);
}

void Zero::ShaderOpenGL::SetVector2(const std::string& name, const glm::vec2& vector) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform2f(location, vector.x, vector.y);
}

void Zero::ShaderOpenGL::SetFloat(const std::string& name, const float value) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform1f(location, value);
}

void Zero::ShaderOpenGL::SetInt(const std::string& name, const int32_t value) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform1i(location, value);
}

void Zero::ShaderOpenGL::SetUnsignedInt(const std::string& name, const uint32_t value) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform1ui(location, value);
}

void Zero::ShaderOpenGL::SetIntArray(const std::string& name, const int32_t* values, const uint32_t count) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform1iv(location, count, values);
}

void Zero::ShaderOpenGL::SetUnsignedIntArray(const std::string& name, const uint32_t* values, const uint32_t count) const {
  const int32_t location{ glGetUniformLocation(m_Id, name.c_str()) };
  glUniform1uiv(location, count, values);
}

uint32_t Zero::ShaderOpenGL::StringToShaderType(const std::string& type) {
  if (type == "vertex") {
    return GL_VERTEX_SHADER;
  } else if (type == "fragment") {
    return GL_FRAGMENT_SHADER;
  } else if (type == "compute") {
    return GL_COMPUTE_SHADER;
  } else if (type == "geometry") {
    return GL_GEOMETRY_SHADER;
  }
  ZR_CORE_ASSERT(false, "Unknow shader type");
  return 0;
}

std::string Zero::ShaderOpenGL::ExtractNameFromFilePath(const std::string& filePath) {
  size_t lastSlashPosition{ filePath.find_last_of("/\\") };
  lastSlashPosition = lastSlashPosition == std::string::npos ? 0 : lastSlashPosition + 1;
  size_t lastDotPosition{ filePath.rfind(".") };
  size_t count{ lastDotPosition == std::string::npos ? filePath.size() - lastSlashPosition : lastDotPosition - lastSlashPosition };
  return filePath.substr(lastSlashPosition, count);
}

bool Zero::ShaderOpenGL::CheckShaderErrors(uint32_t shader) {
  int32_t isCompiled{};
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

  if (isCompiled == GL_FALSE) {
    int32_t maxLength{ 0 };
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    Array<char> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());
    glDeleteShader(shader);
    ZR_CORE_ERROR("{0}", infoLog.data());
    return false;
  }

  return true;
}

bool Zero::ShaderOpenGL::CheckProgramErrors(uint32_t program, const FixedArray<uint32_t, MAX_SHADERS_SUPPORTED>& shaderIds) {
  int32_t isLinked{ 0 };
  glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE) {
    int32_t maxLength{ 0 };
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    Array<char> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

    for (uint32_t shaderId : shaderIds) {
      glDeleteShader(shaderId);
    }

    glDeleteProgram(program);

    ZR_CORE_ERROR("{0}", infoLog.data());
    return false;
  }

  return true;
}
