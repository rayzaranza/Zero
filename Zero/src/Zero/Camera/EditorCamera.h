#pragma once
#include "Camera.h"
#include "Zero/Event/Event.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Time/DeltaTime.h"


namespace Zero {


class EditorCamera : public Camera
{
  public:
    EditorCamera() = default;
    EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

  public:
    void OnUpdate(DeltaTime deltaTime);
    void OnEvent(Event& event);
    void SetDistance(float distance);
    void SetViewportSize(const glm::vec2& size);
    float GetDistance() const;
    const glm::mat4& GetViewMatrix() const;
    glm::mat4 GetViewProjection() const;
    glm::vec3 GetUpDirection() const;
    glm::vec3 GetRightDirection() const;
    glm::vec3 GetForwardDirection() const;
    const glm::vec3& GetPosition() const;
    glm::quat GetOrientation() const;
    float GetPitch() const;
    float GetYaw() const;

  private:
    void UpdateProjection();
    void UpdateView();
    bool OnMouseScroll(MouseScrolledEvent& event);
    void Pan(const glm::vec2& delta);
    void Rotate(const glm::vec2& delta);
    void Zoom(float delta);
    glm::vec3 CalculatePosition() const;
    glm::vec2 GetPanSpeed() const;
    float GetRotationSpeed() const;
    float GetZoomSpeed() const;

  private:
    float m_FOV{ 30.0f };
    float m_AspectRatio{ 1.778f };
    float m_NearClip{ 0.1f };
    float m_FarClip{ 1000.0f };
    glm::mat4 m_ViewMatrix{ 1.0f };
    glm::vec3 m_Position{ 0.0f };
    glm::vec3 m_FocalPoint{ 0.0f };
    glm::vec2 m_InitialMousePosition{ 0.0f };
    glm::vec2 m_ViewportSize{ 1280.0f, 720.0f };
    float m_Distance{ 10.0f };
    float m_Pitch{ 0.0f };
    float m_Yaw{ 0.0f };
};


}
