#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class OrthographicCamera
    {
      public:
        OrthographicCamera(const F32 left, const F32 right, const F32 bottom = -1.0f, const F32 top = 1.0f);

      public:
        inline const Matrix4& GetViewMatrix() const { return m_ViewMatrix; }
        inline const Matrix4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
        inline const Matrix4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };
        inline const Vector3& GetPosition() const { return m_Position; }
        inline Degrees GetRotation() const { return m_Rotation; }

      public:
        void SetPosition(const Vector3& position);
        void SetRotation(const Degrees rotation);
        void SetProjectionMatrix(const F32 left, const F32 right, const F32 bottom, const F32 top);

      private:
        void CalculateViewProjectionMatrix();

      private:
        Vector3 m_Position;
        Matrix4 m_ViewMatrix;
        Matrix4 m_ProjectionMatrix;
        Matrix4 m_ViewProjectionMatrix;
        Degrees m_Rotation;
    };
}
