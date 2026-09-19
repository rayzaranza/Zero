#pragma once

#include "Zero/Camera/Camera.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Time/DeltaTime.h"

namespace Zero
{
    struct OrthographicCameraBounds
    {
        float Left{};
        float Right{};
        float Bottom{};
        float Top{};

        inline float GetWidth() const { return Right - Left; }
        inline float GetHeight() const { return Top - Bottom; }
    };

    class OrthographicCameraController
    {
      public:
        OrthographicCameraController(float aspectRatio);

      public:
        void OnUpdate(DeltaTime deltaTime);
        void OnEvent(Event& event);
        inline const OrthographicCamera& GetCamera() const { return m_Camera; }
        inline OrthographicCamera& GetCamera() { return m_Camera; }
        inline float GetZoomLevel() const { return m_ZoomLevel; }
        inline void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
        inline const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

      private:
        bool OnMouseScrolled(MouseScrolledEvent& event);
        bool OnWindowResizedEvent(WindowResizedEvent& event);

      private:
        float m_AspectRatio;
        float m_ZoomLevel;
        OrthographicCameraBounds m_Bounds;
        OrthographicCamera m_Camera;
        glm::vec3 m_Position;
        float m_Rotation;
        float m_RotationSpeed;
        float m_ZoomSpeed;
        float m_TranslationSpeed;
    };
}
