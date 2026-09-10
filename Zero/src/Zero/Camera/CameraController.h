#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Time/DeltaTime.h"

namespace Zero
{
    class OrthographicCameraController
    {
      public:
        OrthographicCameraController(float aspectRatio);

      public:
        void OnUpdate(DeltaTime deltaTime);
        void OnEvent(Event& event);
        inline const OrthographicCamera& GetCamera() const { return m_Camera; }
        inline OrthographicCamera& GetCamera() { return m_Camera; }

      private:
        bool OnMouseScrolled(MouseScrolledEvent& event);
        bool OnWindowResizedEvent(WindowResizedEvent& event);

      private:
        float m_AspectRatio;
        float m_ZoomLevel;
        OrthographicCamera m_Camera;
        glm::vec3 m_Position;
        float m_ZoomSpeed;
        float m_TranslationSpeed;
    };
}
