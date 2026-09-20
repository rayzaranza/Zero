#include "CameraController.h"
#include "Zero/Input/Input.h"
#include "Zero/Input/KeyCode.h"

Zero::CameraOrthographicController::CameraOrthographicController(float aspectRatio)
  : m_AspectRatio{ aspectRatio }
  , m_ZoomLevel{ 1.0f }
  , m_Bounds{ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }
  , m_Camera{ m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top }
  , m_TranslationSpeed{ m_ZoomLevel }
  , m_Position{ 0.0f }
  , m_ZoomSpeed{ 0.1f }
  , m_Rotation{ 0.0f }
  , m_RotationSpeed{ 1.0f } {
}

void Zero::CameraOrthographicController::OnUpdate(const DeltaTime deltaTime) {
  m_TranslationSpeed = m_ZoomLevel;

  if (Input::IsKeyPressed(KeyCode::D)) {
    m_Position.x += m_TranslationSpeed * deltaTime;
  } else if (Input::IsKeyPressed(KeyCode::A)) {
    m_Position.x -= m_TranslationSpeed * deltaTime;
  }

  if (Input::IsKeyPressed(KeyCode::W)) {
    m_Position.y += m_TranslationSpeed * deltaTime;
  } else if (Input::IsKeyPressed(KeyCode::S)) {
    m_Position.y -= m_TranslationSpeed * deltaTime;
  }

  if (Input::IsKeyPressed(KeyCode::Q)) {
    m_Rotation += m_RotationSpeed * deltaTime;
  } else if (Input::IsKeyPressed(KeyCode::E)) {
    m_Rotation -= m_RotationSpeed * deltaTime;
  }

  m_Camera.SetPosition(m_Position);
  m_Camera.SetRotation(m_Rotation);
}

void Zero::CameraOrthographicController::OnEvent(Event& event) {
  EventDispatcher dispatcher{ event };
  dispatcher.Dispatch<MouseScrolledEvent>(ZR_BIND_FUNCTION(CameraOrthographicController::OnMouseScrolled));
  dispatcher.Dispatch<WindowResizedEvent>(ZR_BIND_FUNCTION(CameraOrthographicController::OnWindowResizedEvent));
}

const Zero::CameraOrthographic& Zero::CameraOrthographicController::GetCamera() const {
  return m_Camera;
}

Zero::CameraOrthographic& Zero::CameraOrthographicController::GetCamera() {
  return m_Camera;
}

float Zero::CameraOrthographicController::GetZoomLevel() const {
  return m_ZoomLevel;
}

void Zero::CameraOrthographicController::SetZoomLevel(float zoomLevel) {
  m_ZoomLevel = zoomLevel;
  CalculateView();
}

void Zero::CameraOrthographicController::CalculateView() {
  m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
  m_Camera.SetProjectionMatrix(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
}

const Zero::CameraOrthographicBounds& Zero::CameraOrthographicController::GetBounds() const {
  return m_Bounds;
}

bool Zero::CameraOrthographicController::OnMouseScrolled(MouseScrolledEvent& event) {
  m_ZoomLevel = std::fmax(m_ZoomLevel - event.GetOffset().y * m_ZoomSpeed, 0.1f);
  CalculateView();
  return false;
}

bool Zero::CameraOrthographicController::OnWindowResizedEvent(WindowResizedEvent& event) {
  const glm::ivec2 size{ event.GetSize() };
  m_AspectRatio = static_cast<float>(size.x) / static_cast<float>(size.y);
  CalculateView();
  return false;
}

float Zero::CameraOrthographicBounds::GetWidth() const {
  return Right - Left;
}

float Zero::CameraOrthographicBounds::GetHeight() const {
  return Top - Bottom;
}
