#include "Texture.h"
#include "Texture.OpenGL.h"
#include "Zero/Core/Core.h"
#include "Zero/Renderer/Renderer.h"

Zero::Ref<Zero::Texture2D> Zero::Texture2D::Create(const glm::uvec2& size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:   ZR_CORE_ASSERT(false, "Renderer API set to None"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<Texture2DOpenGL>(size);
    case RendererAPI::API::Vulkan: ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}

Zero::Ref<Zero::Texture2D> Zero::Texture2D::Create(const std::string& path) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:   ZR_CORE_ASSERT(false, "Renderer API set to None"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<Texture2DOpenGL>(path);
    case RendererAPI::API::Vulkan: ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}
