#pragma once
#include "Zero/Camera/Camera.h"


namespace Zero {


class SceneCamera : public Camera
{
  public:
    enum class ProjectionType
    {
        Perspective = 0,
        Orthographic = 1,
    };

  public:
    SceneCamera();
    virtual ~SceneCamera() = default;

  public:
    void SetProjectionType(ProjectionType type);
    ProjectionType GetProjectionType() const;
    void SetViewportSize(const glm::uvec2& size);
    void SetAspectRatio(const float aspectRatio);
    float GetAspectRatio() const;

  public:
    void SetOrthographic(float size, float nearClip, float farClip);
    void SetPerspective(float verticalFOV, float nearClip, float farClip);
    void SetOrthographicSize(const float size);
    float GetOrthographicSize() const;
    void SetOrthographicNearClip(const float nearClip);
    float GetOrthographicNearClip() const;
    void SetOrthographicFarClip(const float farClip);
    float GetOrthographicFarClip() const;

  public:
    void SetPerspectiveVerticalFOV(const float perspectiveFOV);
    float GetPerspectiveVerticalFOV() const;
    void SetPerspectiveNearClip(const float nearClip);
    float GetPerspectiveNearClip() const;
    void SetPerspectiveFarClip(const float farClip);
    float GetPerspectiveFarClip() const;

  private:
    void RecalculateProjection();

  private:
    float m_OrthographicSize{ 10.0f };
    float m_OrthographicNearClip{ -1.0f };
    float m_OrthographicFarClip{ 1.0f };
    float m_AspectRatio{ 1.0f };
    float m_PerspectiveFOV{ glm::radians(45.0f) };
    float m_PerspectiveNearClip{ 0.01f };
    float m_PerspectiveFarClip{ 1000.0f };
    ProjectionType m_ProjectionType{ ProjectionType::Orthographic };
};


}
