#include "IndexBuffer.h"
#include "../Renderer.h"
#include "IndexBuffer.OpenGL.h"

Zero::Ref<Zero::IndexBuffer> Zero::IndexBuffer::Create(const Array<uint32_t>& indices) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:   ZR_CORE_ASSERT(false, "Renderer API set to None"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<IndexBufferOpenGL>(indices);
    case RendererAPI::API::Vulkan: ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}

Zero::Ref<Zero::IndexBuffer> Zero::IndexBuffer::Create(const uint32_t size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:   ZR_CORE_ASSERT(false, "Renderer API set to None"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<IndexBufferOpenGL>(size);
    case RendererAPI::API::Vulkan: ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}

Zero::Ref<Zero::IndexBuffer> Zero::IndexBuffer::Create(const uint32_t* indices, const uint32_t count) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:   ZR_CORE_ASSERT(false, "Renderer API set to None"); return nullptr;
    case RendererAPI::API::OpenGL: return CreateRef<IndexBufferOpenGL>(indices, count);
    case RendererAPI::API::Vulkan: ZR_CORE_ASSERT(false, "Vulkan Renderer API not supported"); return nullptr;
  }
  ZR_CORE_ASSERT(false, "Unknown Renderer API");
  return nullptr;
}
