#pragma once

#include "Zero/Renderer/Texture.h"

namespace Zero
{
    class OpenGLTexture2D : public Texture2D
    {
      public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

      public:
        virtual void Bind(uint32_t slot = 0) const override;
        inline virtual uint32_t GetWidth() const override { return m_Width; }
        inline virtual uint32_t GetHeight() const override { return m_Height; }

      private:
        std::string m_Path;
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_Id;
    };
}
