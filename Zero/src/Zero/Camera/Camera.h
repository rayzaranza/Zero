#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class OrthographicCamera
    {
      public:
        OrthographicCamera(const F32 left, const F32 right, const F32 bottom = -1.0f, const F32 top = 1.0f);

      public:
        inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
        inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };
        inline const glm::vec3& GetPosition() const { return m_Position; }
        inline Radians GetRotation() const { return m_Rotation; }

      public:
        void SetPosition(const glm::vec3& position);
        void SetRotation(const Radians rotation);
        void SetProjectionMatrix(const F32 left, const F32 right, const F32 bottom, const F32 top);

      private:
        void CalculateViewProjectionMatrix();

      private:
        glm::vec3 m_Position;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        Radians m_Rotation;
    };
}
