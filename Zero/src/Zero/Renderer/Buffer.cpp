#include "Zero/Renderer/Buffer.h"
#include "Zero/Renderer/OpenGL/OpenGLBuffer.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    // ················································································································
    //  Vertex Buffer
    // ················································································································

    VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:
                ZERO_CORE_ASSERT(false, "Renderer API set to None");
                return nullptr;

            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, size);

            default:
                ZERO_CORE_ASSERT(false, "Unknown Renderer API");
                return nullptr;
        }
    }

    // ················································································································
    //  Index Buffer
    // ················································································································

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:
                ZERO_CORE_ASSERT(false, "Renderer API set to None");
                return nullptr;

            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices, size);

            default:
                ZERO_CORE_ASSERT(false, "Unknown Renderer API");
                return nullptr;
        }
    }
}
