#pragma once

namespace Zero
{
    Matrix4 CalculcateModelMatrix(const Vector3& position, const Radians rotation, const Vector3& scale);
    Matrix4 CalculcateModelMatrix2D(const Vector2& position, const Radians rotation, const Vector2& scale);
}
