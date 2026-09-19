#pragma once

#include "Zero/Renderer/Texture.h"

namespace Zero
{
    class OpenGLTexture2D : public Texture2D
    {
      public:
        struct Format
        {
            uint32_t storage{};
            uint32_t image{};
        };

      public:
        OpenGLTexture2D(const glm::uvec2& size);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

      public:
        virtual void Bind(const uint32_t slot = 0) const override;
        inline virtual const glm::uvec2& GetSize() const override { return m_Size; }
        virtual void SetData(const void* data, const uint32_t size) override;
        inline virtual uint32_t GetRendererID() const override { return m_Id; }

      private:
        void SetupTextureBuffer();

      private:
        uint32_t m_Id{};
        std::string m_Path{};
        glm::uvec2 m_Size{};
        Format m_Format{};
    };
}
