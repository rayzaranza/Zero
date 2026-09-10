#pragma once

#include <glm/glm.hpp>

namespace Zero
{
    class OrthographicCamera
    {
      public:
        OrthographicCamera(float left, float right, float bottom = -1.0f, float top = 1.0f);

      public:
        inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; };
        inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; };
        inline const glm::vec3& GetPosition() const { return m_Position; }
        inline float GetRotation() const { return m_Rotation; }

        void SetPosition(const glm::vec3& position);
        void SetRotation(float rotation);
        void SetProjectionMatrix(float left, float right, float bottom, float top);

      private:
        void CalculateViewProjectionMatrix();

      private:
        glm::vec3 m_Position;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        float m_Rotation;
    };
}
