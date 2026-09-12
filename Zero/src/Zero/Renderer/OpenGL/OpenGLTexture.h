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
        virtual void Bind(const U32 slot = 0) const override;
        inline virtual const Vector2u& GetSize() const override { return m_Size; }

      private:
        RendererID m_Id;
        String m_Path;
        Vector2u m_Size;
    };
}
