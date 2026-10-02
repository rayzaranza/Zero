#include "Zero/Renderer/Buffer/VertexAttribute.h"


static int32_t GetSizeFromAttributeType(const Zero::VertexAttributeType type);
static uint32_t GetComponentCountFromAttributeType(const Zero::VertexAttributeType type);


Zero::VertexAttribute::VertexAttribute(const VertexAttributeType type, const std::string& name)
    : Name{ name }
    , Type{ type }
    , Size{ GetSizeFromAttributeType(type) }
    , ComponentCount{ GetComponentCountFromAttributeType(type) }
    , IsNormalized{ false }
    , Offset{ 0u }
{
}


int32_t GetSizeFromAttributeType(const Zero::VertexAttributeType type)
{
    switch (type)
    {
        case Zero::VertexAttributeType::Boolean:
        {
            return 1;
        }

        case Zero::VertexAttributeType::Float:
        case Zero::VertexAttributeType::Int:
        {
            return 4;
        }

        case Zero::VertexAttributeType::Vector2:
        case Zero::VertexAttributeType::Vector2i:
        {
            return 4 * 2;
        }

        case Zero::VertexAttributeType::Vector3:
        case Zero::VertexAttributeType::Vector3i:
        {
            return 4 * 3;
        }

        case Zero::VertexAttributeType::Vector4:
        case Zero::VertexAttributeType::Vector4i:
        {
            return 4 * 4;
        }

        case Zero::VertexAttributeType::Matrix3:
        {
            return 4 * 3 * 3;
        }

        case Zero::VertexAttributeType::Matrix4:
        {
            return 4 * 4 * 4;
        }

        default:
        {
            ZR_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
            return 0;
        }
    }
}


uint32_t GetComponentCountFromAttributeType(const Zero::VertexAttributeType type)
{
    switch (type)
    {
        case Zero::VertexAttributeType::Boolean:
        case Zero::VertexAttributeType::Float:
        case Zero::VertexAttributeType::Int:
        {
            return 1;
        }

        case Zero::VertexAttributeType::Vector2:
        case Zero::VertexAttributeType::Vector2i:
        {
            return 2;
        }

        case Zero::VertexAttributeType::Vector3:
        case Zero::VertexAttributeType::Vector3i:
        {
            return 3;
        }

        case Zero::VertexAttributeType::Vector4:
        case Zero::VertexAttributeType::Vector4i:
        {
            return 4;
        }

        case Zero::VertexAttributeType::Matrix3:
        {
            return 3 * 3;
        }

        case Zero::VertexAttributeType::Matrix4:
        {
            return 4 * 4;
        }

        default:
        {
            ZR_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
            return 0;
        }
    }
}
