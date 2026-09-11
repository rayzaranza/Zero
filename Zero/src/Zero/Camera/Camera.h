#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class OrthographicCamera
    {
      public:
        OrthographicCamera(F32 left, F32 right, F32 bottom = -1.0f, F32 top = 1.0f);

      public:
        inline const Matrix4& GetViewMatrix() const { return m_ViewMatrix; }
        inline const Matrix4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
        inline const Matrix4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };
        inline const Vector3& GetPosition() const { return m_Position; }
        inline F32 GetRotation() const { return m_Rotation; }

        void SetPosition(const Vector3& position);
        void SetRotation(F32 rotation);
        void SetProjectionMatrix(F32 left, F32 right, F32 bottom, F32 top);

      private:
        void CalculateViewProjectionMatrix();

      private:
        Vector3 m_Position;
        Matrix4 m_ViewMatrix;
        Matrix4 m_ProjectionMatrix;
        Matrix4 m_ViewProjectionMatrix;
        F32 m_Rotation;
    };
}
