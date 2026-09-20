#include "Shader.h"
#include "Shader.OpenGL.h"
#include "Zero/Renderer/Renderer.h"

Zero::Ref<Zero::Shader> Zero::Shader::Create(const std::string& filePath) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:   ZR_CORE_ASSERT(false, "Renderer API set to None"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<ShaderOpenGL>(filePath);
    case RendererAPI::API::Vulkan: ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}

Zero::Ref<Zero::Shader> Zero::Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:   ZR_CORE_ASSERT(false, "Renderer API set to None"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<ShaderOpenGL>(name, vertexSource, fragmentSource);
    case RendererAPI::API::Vulkan: ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}

void Zero::ShaderLibrary::Add(const std::string& name, const Zero::Ref<Zero::Shader>& shader) {
  ZR_CORE_ASSERT(!Exists(name), "Shader already exists");
  m_Shaders[name] = shader;
}

void Zero::ShaderLibrary::Add(const Zero::Ref<Zero::Shader>& shader) {
  const std::string& name{ shader->GetName() };
  Add(name, shader);
}

Zero::Ref<Zero::Shader> Zero::ShaderLibrary::Load(const std::string& filePath) {
  Zero::Ref<Zero::Shader> shader{ Shader::Create(filePath) };
  Add(shader);
  return shader;
}

Zero::Ref<Zero::Shader> Zero::ShaderLibrary::Load(const std::string& name, const std::string& filePath) {
  Zero::Ref<Zero::Shader> shader{ Shader::Create(filePath) };
  Add(name, shader);
  return shader;
}

Zero::Ref<Zero::Shader> Zero::ShaderLibrary::Get(const std::string& name) {
  ZR_CORE_ASSERT(Exists(name), "Shader not found");
  return m_Shaders[name];
}

bool Zero::ShaderLibrary::Exists(const std::string& name) const {
  return m_Shaders.find(name) != m_Shaders.end();
}

Zero::Ref<Zero::ShaderLibrary> Zero::ShaderLibrary::Create() {
  return CreateRef<ShaderLibrary>();
}
