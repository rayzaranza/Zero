#pragma once

#include "Zero/Renderer/Texture.h"

namespace Zero
{
    class OpenGLTexture2D : public Texture2D
    {
      public:
        struct Format
        {
            U32 storage{};
            U32 image{};
        };

      public:
        OpenGLTexture2D(const Vector2u& size);
        OpenGLTexture2D(const String& path);
        virtual ~OpenGLTexture2D();

      public:
        virtual void Bind(const U32 slot = 0) const override;
        inline virtual const Vector2u& GetSize() const override { return m_Size; }
        virtual void SetData(const void* data, const U32 size) override;

      private:
        void SetupTextureBuffer();

      private:
        RendererID m_Id{};
        String m_Path{};
        Vector2u m_Size{};
        Format m_Format{};
    };
}
