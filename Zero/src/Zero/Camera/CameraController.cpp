#include "Zero/Camera/CameraController.h"

#include "Zero/Input/Input.h"
#include "Zero/Input/KeyCode.h"

namespace Zero
{
    OrthographicCameraController::OrthographicCameraController(F32 aspectRatio)
        : m_AspectRatio{ aspectRatio }
        , m_ZoomLevel{ 1.0f }
        , m_Camera{ -m_AspectRatio, m_AspectRatio }
        , m_Position{ 0.0f }
        , m_TranslationSpeed{ m_ZoomLevel }
        , m_ZoomSpeed{ 0.1f }
        , m_Rotation{ 0.0f }
        , m_RotationSpeed{ 90.0f }
    {}

    void OrthographicCameraController::OnUpdate(DeltaTime deltaTime)
    {
        m_TranslationSpeed = m_ZoomLevel;

        if (Input::IsKeyPressed(KeyCode::D))
            m_Position.x += m_TranslationSpeed * deltaTime;
        else if (Input::IsKeyPressed(KeyCode::A))
            m_Position.x -= m_TranslationSpeed * deltaTime;

        if (Input::IsKeyPressed(KeyCode::W))
            m_Position.y += m_TranslationSpeed * deltaTime;
        else if (Input::IsKeyPressed(KeyCode::S))
            m_Position.y -= m_TranslationSpeed * deltaTime;

        if (Input::IsKeyPressed(KeyCode::Q))
            m_Rotation += m_RotationSpeed * deltaTime;
        else if (Input::IsKeyPressed(KeyCode::E))
            m_Rotation -= m_RotationSpeed * deltaTime;

        m_Camera.SetPosition(m_Position);
        m_Camera.SetRotation(m_Rotation);
    }

    void OrthographicCameraController::OnEvent(Event& event)
    {
        EventDispatcher dispatcher{ event };
        dispatcher.Dispatch<MouseScrolledEvent>(ZR_BIND_FUNCTION(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizedEvent>(ZR_BIND_FUNCTION(OrthographicCameraController::OnWindowResizedEvent));
    }

    Boolean OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
    {
        m_ZoomLevel = std::fmax(m_ZoomLevel - event.GetOffset().y * m_ZoomSpeed, 0.1f);
        m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    Boolean OrthographicCameraController::OnWindowResizedEvent(WindowResizedEvent& event)
    {
        const Vector2i size{ event.GetSize() };
        m_AspectRatio = static_cast<F32>(size.x) / static_cast<F32>(size.y);
        m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}
