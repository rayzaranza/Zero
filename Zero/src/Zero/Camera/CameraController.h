#pragma once
#include "Camera.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Time/DeltaTime.h"

namespace Zero {
  struct CameraOrthographicBounds {
    float Left{};
    float Right{};
    float Bottom{};
    float Top{};
    float GetWidth() const;
    float GetHeight() const;
  };

  class CameraOrthographicController {
  public:
    CameraOrthographicController(float aspectRatio);
    void OnUpdate(const DeltaTime deltaTime);
    void OnEvent(Event& event);
    void OnResize(const glm::uvec2& size);
    const CameraOrthographicBounds& GetBounds() const;
    const CameraOrthographic& GetCamera() const;
    CameraOrthographic& GetCamera();
    float GetZoomLevel() const;
    void SetZoomLevel(float zoomLevel);
    void CalculateView();

  private:
    bool OnMouseScrolled(MouseScrolledEvent& event);
    bool OnWindowResizedEvent(WindowResizedEvent& event);
    glm::vec3 m_Position;
    float m_AspectRatio;
    float m_ZoomLevel;
    CameraOrthographicBounds m_Bounds;
    CameraOrthographic m_Camera;
    float m_Rotation;
    float m_RotationSpeed;
    float m_ZoomSpeed;
    float m_TranslationSpeed;
  };
}
