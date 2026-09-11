#pragma once

namespace Zero
{
    //======================================================================================
    //  Texture
    //======================================================================================
    class Texture
    {
      public:
        virtual ~Texture() = default;

      public:
        virtual void Bind(U32 slot = 0) const = 0;
        virtual U32 GetWidth() const = 0;
        virtual U32 GetHeight() const = 0;
    };

    //======================================================================================
    //  Texture 2D
    //======================================================================================
    class Texture2D;
    using Texture2DRef = Ref<Texture2D>;

    class Texture2D : public Texture
    {
      public:
        static Texture2DRef Create(const String& path);
    };

}
