#pragma once

namespace Zero {
  enum class VertexAttributeType : uint8_t {
    Int,
    Float,
    Boolean,
    Vector2,
    Vector3,
    Vector4,
    Matrix3,
    Matrix4,
    Vector2i,
    Vector3i,
    Vector4i,
  };

  int32_t GetSizeFromAttributeType(const VertexAttributeType type);
  uint32_t GetComponentCountFromAttributeType(const VertexAttributeType type);

  struct VertexAttribute {
    std::string Name;
    VertexAttributeType Type;
    int32_t Size;
    uint32_t ComponentCount;
    bool IsNormalized;
    uint32_t Offset;

    VertexAttribute(const VertexAttributeType type, const std::string& name)
      : Name{ name }
      , Type{ type }
      , Size{ GetSizeFromAttributeType(type) }
      , ComponentCount{ GetComponentCountFromAttributeType(type) }
      , IsNormalized{ false }
      , Offset{ 0u } {}
  };
}
