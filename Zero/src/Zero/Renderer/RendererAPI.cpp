#include "RendererAPI.h"
#include "RendererAPI.OpenGL.h"

Zero::RendererAPI::API Zero::RendererAPI::s_API{ RendererAPI::API::OpenGL };

Zero::RendererAPI::API Zero::RendererAPI::GetAPI() {
  return s_API;
}

Zero::Scope<Zero::RendererAPI> Zero::RendererAPI::Create() {
  switch (s_API) {
    case API::OpenGL: return CreateScope<RendererAPIOpenGL>();
    case API::None:   ZR_CORE_ASSERT(false, "Renderer API None is not supported"); return nullptr;
    case API::Vulkan: ZR_CORE_ASSERT(false, "Renderer API Vulkan is not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}
