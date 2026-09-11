#pragma once

#include "Zero/Renderer/Texture.h"

namespace Zero
{
    class OpenGLTexture2D : public Texture2D
    {
      public:
        OpenGLTexture2D(const String& path);
        virtual ~OpenGLTexture2D();

      public:
        virtual void Bind(U32 slot = 0) const override;
        inline virtual U32 GetWidth() const override { return m_Width; }
        inline virtual U32 GetHeight() const override { return m_Height; }

      private:
        RendererID m_Id;
        String m_Path;
        U32 m_Width;
        U32 m_Height;
    };
}
