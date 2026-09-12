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
        virtual void Bind(const U32 slot = 0) const = 0;
        virtual const Vector2u& GetSize() const = 0;
    };

    //======================================================================================
    //  Texture 2D
    //======================================================================================
    class Texture2D : public Texture
    {
      public:
        static Ref<Texture2D> Create(const String& path);
    };

    using Texture2DRef = Ref<Texture2D>;

}
