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
        virtual void Bind(const uint32_t slot = 0) const = 0;
        virtual const glm::uvec2& GetSize() const = 0;
        virtual void SetData(const void* data, uint32_t size) = 0;
        virtual uint32_t GetRendererID() const = 0;
    };

    //======================================================================================
    //  Texture 2D
    //======================================================================================
    class Texture2D : public Texture
    {
      public:
        static Ref<Texture2D> Create(const glm::uvec2& size);
        static Ref<Texture2D> Create(const std::string& path);
    };

    using Texture2DRef = Ref<Texture2D>;

}
