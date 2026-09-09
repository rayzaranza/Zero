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
        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
    };

    //======================================================================================
    //  Texture 2D
    //======================================================================================
    class Texture2D : public Texture
    {
      public:
        static Ref<Texture2D> Create(const std::string& path);
    };
}
