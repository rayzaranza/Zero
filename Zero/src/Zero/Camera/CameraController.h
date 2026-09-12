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
        OrthographicCameraController(F32 aspectRatio);

      public:
        void OnUpdate(DeltaTime deltaTime);
        void OnEvent(Event& event);
        inline const OrthographicCamera& GetCamera() const { return m_Camera; }
        inline OrthographicCamera& GetCamera() { return m_Camera; }
        inline F32 GetZoomLevel() const { return m_ZoomLevel; }
        inline void SetZoomLevel(F32 zoomLevel) { m_ZoomLevel = zoomLevel; }

      private:
        Boolean OnMouseScrolled(MouseScrolledEvent& event);
        Boolean OnWindowResizedEvent(WindowResizedEvent& event);

      private:
        F32 m_AspectRatio;
        F32 m_ZoomLevel;
        OrthographicCamera m_Camera;
        Vector3 m_Position;
        Degrees m_Rotation;
        F32 m_ZoomSpeed;
        F32 m_TranslationSpeed;
        F32 m_RotationSpeed;
    };
}
