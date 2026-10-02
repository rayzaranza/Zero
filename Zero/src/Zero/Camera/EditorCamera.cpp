#include "EditorCamera.h"
#include "Zero/Input/Input.h"
#include <glm/gtx/quaternion.hpp>


Zero::EditorCamera::EditorCamera(float fov, float aspectRatio, float nearClip, float farClip)
    : m_FOV{ fov }
    , m_AspectRatio{ aspectRatio }
    , m_NearClip{ nearClip }
    , m_FarClip{ farClip }
    , Camera{ glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip) }
{
    UpdateView();
}


void Zero::EditorCamera::OnUpdate(DeltaTime deltaTime)
{
    if (Input::IsKeyPressed(KeyCode::LEFT_ALT))
    {
        const glm::vec2& mousePosition{ Input::GetMousePosition() };
        const glm::vec2 mouseDelta{ (mousePosition - m_InitialMousePosition) * 0.003f };
        m_InitialMousePosition = mousePosition;

        if (Input::IsMouseButtonPressed(MouseButton::MIDDLE))
        {
            Pan(mouseDelta);
        }
        else if (m_IsRotationEnabled && Input::IsMouseButtonPressed(MouseButton::LEFT))
        {
            Rotate(mouseDelta);
        }
        else if (Input::IsMouseButtonPressed(MouseButton::RIGHT))
        {
            Zoom(mouseDelta.y);
        }
    }

    UpdateView();
}


void Zero::EditorCamera::OnEvent(Event& event)
{
    EventDispatcher dispatcher{ event };
    dispatcher.Dispatch<MouseScrolledEvent>(ZR_BIND_FUNCTION(EditorCamera::OnMouseScroll));
}


void Zero::EditorCamera::SetDistance(float distance)
{
    m_Distance = distance;
}


void Zero::EditorCamera::SetViewportSize(const glm::vec2& size)
{
    m_ViewportSize = size;
    UpdateProjection();
}


float Zero::EditorCamera::GetDistance() const
{
    return m_Distance;
}


const glm::mat4& Zero::EditorCamera::GetViewMatrix() const
{
    return m_ViewMatrix;
}


glm::mat4 Zero::EditorCamera::GetViewProjection() const
{
    return m_Projection * m_ViewMatrix;
}


glm::vec3 Zero::EditorCamera::GetUpDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3{ 0.0f, 1.0f, 0.0f });
}


glm::vec3 Zero::EditorCamera::GetRightDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3{ 1.0f, 0.0f, 0.0f });
}


glm::vec3 Zero::EditorCamera::GetForwardDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3{ 0.0f, 0.0f, -1.0f });
}


const glm::vec3& Zero::EditorCamera::GetPosition() const
{
    return m_Position;
}


glm::quat Zero::EditorCamera::GetOrientation() const
{
    const glm::vec3 eulerAngles{ -m_Pitch, -m_Yaw, 0.0f };
    return glm::quat{ eulerAngles };
}


float Zero::EditorCamera::GetPitch() const
{
    return m_Pitch;
}


float Zero::EditorCamera::GetYaw() const
{
    return m_Yaw;
}


void Zero::EditorCamera::UpdateProjection()
{
    m_AspectRatio = m_ViewportSize.x / m_ViewportSize.y;
    m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
}


void Zero::EditorCamera::UpdateView()
{
    m_Position = CalculatePosition();

    glm::quat orientation{ GetOrientation() };
    m_ViewMatrix = glm::translate(glm::mat4{ 1.0f }, m_Position) * glm::toMat4(orientation);
    m_ViewMatrix = glm::inverse(m_ViewMatrix);
}


bool Zero::EditorCamera::OnMouseScroll(MouseScrolledEvent& event)
{
    const float delta{ event.GetOffset().y };
    Zoom(delta);
    UpdateView();
    return false;
}


void Zero::EditorCamera::EnableRotation(bool enable)
{
    m_IsRotationEnabled = enable;
}


bool Zero::EditorCamera::GetIsRotationEnabled() const
{
    return m_IsRotationEnabled;
}


void Zero::EditorCamera::Pan(const glm::vec2& delta)
{
    const glm::vec2 panSpeed{ GetPanSpeed() };
    m_FocalPoint += -GetRightDirection() * delta.x * panSpeed.x * m_Distance;
    m_FocalPoint += GetUpDirection() * delta.y * panSpeed.y * m_Distance;
}


void Zero::EditorCamera::Rotate(const glm::vec2& delta)
{
    const float rotationSpeed{ GetRotationSpeed() };
    const float yawSign{ GetUpDirection().y < 0 ? -1.0f : 1.0f };

    m_Yaw += yawSign * delta.x * rotationSpeed;
    m_Pitch += delta.y * rotationSpeed;
}


void Zero::EditorCamera::Zoom(float delta)
{
    m_Distance -= delta * GetZoomSpeed();
    constexpr float minDistance{ 1.0f };

    if (m_Distance < minDistance)
    {
        m_FocalPoint += GetForwardDirection();
        m_Distance = minDistance;
    }
}


glm::vec3 Zero::EditorCamera::CalculatePosition() const
{
    return m_FocalPoint - GetForwardDirection() * m_Distance;
}


glm::vec2 Zero::EditorCamera::GetPanSpeed() const
{
    const float x{ std::min(m_ViewportSize.x / 1000.0f, 2.4f) };
    const float xFactor{ 0.0366f * (x * x) - 0.1778f * x + 0.3021f };

    const float y{ std::min(m_ViewportSize.y / 1000.0f, 2.4f) };
    const float yFactor{ 0.0366f * (y * y) - 0.1778f * y + 0.3021f };

    return glm::vec2{ xFactor, yFactor };
}


float Zero::EditorCamera::GetRotationSpeed() const
{
    return 0.8f;
}


float Zero::EditorCamera::GetZoomSpeed() const
{
    const float distance{ std::max(m_Distance * 0.2f, 0.0f) };
    const float speed{ std::min(distance * distance, 100.0f) };
    return speed;
}
