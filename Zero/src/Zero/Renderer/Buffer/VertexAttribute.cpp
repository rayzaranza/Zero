#include "VertexAttribute.h"

int32_t Zero::GetSizeFromAttributeType(const VertexAttributeType type) {
  switch (type) {
    case VertexAttributeType::Float:    return 4;
    case VertexAttributeType::Vector2:  return 4 * 2;
    case VertexAttributeType::Vector3:  return 4 * 3;
    case VertexAttributeType::Vector4:  return 4 * 4;
    case VertexAttributeType::Matrix3:  return 4 * 3 * 3;
    case VertexAttributeType::Matrix4:  return 4 * 4 * 4;
    case VertexAttributeType::Int:      return 4;
    case VertexAttributeType::Vector2i: return 4 * 2;
    case VertexAttributeType::Vector3i: return 4 * 3;
    case VertexAttributeType::Vector4i: return 4 * 4;
    case VertexAttributeType::Boolean:  return 1;
  }
  ZR_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
  return 0;
}

uint32_t Zero::GetComponentCountFromAttributeType(const VertexAttributeType type) {
  switch (type) {
    case VertexAttributeType::Float:    return 1;
    case VertexAttributeType::Vector2:  return 2;
    case VertexAttributeType::Vector3:  return 3;
    case VertexAttributeType::Vector4:  return 4;
    case VertexAttributeType::Matrix3:  return 3 * 3;
    case VertexAttributeType::Matrix4:  return 4 * 4;
    case VertexAttributeType::Int:      return 1;
    case VertexAttributeType::Vector2i: return 2;
    case VertexAttributeType::Vector3i: return 3;
    case VertexAttributeType::Vector4i: return 4;
    case VertexAttributeType::Boolean:  return 1;
  }
  ZR_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
  return 0;
}
