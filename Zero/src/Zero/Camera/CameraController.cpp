#include "Zero/Camera/CameraController.h"

#include "Zero/Input/Input.h"
#include "Zero/Input/KeyCode.h"

namespace Zero
{
    OrthographicCameraController::OrthographicCameraController(F32 aspectRatio)
        : m_AspectRatio(aspectRatio)
        , m_ZoomLevel{ 1.0f }
        , m_Camera{ -m_AspectRatio, m_AspectRatio }
        , m_Position{ 0.0f }
        , m_TranslationSpeed{ m_ZoomLevel }
        , m_ZoomSpeed{ 0.1f }
    {}

    void OrthographicCameraController::OnUpdate(DeltaTime deltaTime)
    {
        m_TranslationSpeed = m_ZoomLevel;

        if (Input::IsKeyPressed(Key::D))
            m_Position.x += m_TranslationSpeed * deltaTime;
        else if (Input::IsKeyPressed(Key::A))
            m_Position.x -= m_TranslationSpeed * deltaTime;

        if (Input::IsKeyPressed(Key::W))
            m_Position.y += m_TranslationSpeed * deltaTime;
        else if (Input::IsKeyPressed(Key::S))
            m_Position.y -= m_TranslationSpeed * deltaTime;

        m_Camera.SetPosition(m_Position);
    }

    void OrthographicCameraController::OnEvent(Event& event)
    {
        EventDispatcher dispatcher{ event };
        dispatcher.Dispatch<MouseScrolledEvent>(ZR_BIND_FUNCTION(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizedEvent>(ZR_BIND_FUNCTION(OrthographicCameraController::OnWindowResizedEvent));
    }

    Boolean OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event)
    {
        m_ZoomLevel = std::fmax(m_ZoomLevel - event.GetOffset().y * m_ZoomSpeed, 0.25f);
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
