#include "ExampleLayer2D.h"

#include <imgui.h>

#include <chrono>
#include <glm/gtc/type_ptr.hpp>
#include <print>

template <typename TFunction>
class Timer
{
  public:
    Timer(const char* name, TFunction&& function)
        : m_Name{ name }
        , m_IsStopped{ false }
        , m_StartTime{ std::chrono::high_resolution_clock::now() }
        , m_Function{ function }
    {}

    ~Timer()
    {
        if (!m_IsStopped)
            Stop();
    }

  public:
    void Stop()
    {
        const auto endTimepoint{ std::chrono::high_resolution_clock::now() };
        const long long start{ std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime).time_since_epoch().count() };
        const long long end{ std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count() };

        m_IsStopped = true;
        const Zero::Milliseconds duration{ (end - start) * 0.001f };
        m_Function({ m_Name, duration });
    }

  private:
    const char* m_Name;
    Zero::Boolean m_IsStopped;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
    TFunction m_Function;
};

#define PROFILE_SCOPE(name)                                                                                                                    \
    Timer timer##__LINE__(name, [&](ExampleLayer2D::ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

ExampleLayer2D::ExampleLayer2D()
    : Zero::Layer{ "ExampleLayer2D" }
    , m_QuadColor{ Zero::Color::Blue }
    , m_CameraController{ Zero::Application::Get().GetWindow().GetAspectRatio() }
{}

ExampleLayer2D::~ExampleLayer2D()
{}

void ExampleLayer2D::OnAttach()
{
    m_Texture = Zero::Texture2D::Create("D:/Zero/Sandbox/assets/textures/Checkerboard.png");
}

void ExampleLayer2D::OnDetach()
{}

void ExampleLayer2D::OnUpdate(const Zero::DeltaTime deltaTime)
{
    PROFILE_SCOPE("OnUpdate");
    m_CameraController.OnUpdate(deltaTime);
}

void ExampleLayer2D::OnRender()
{
    PROFILE_SCOPE("OnRender");
    {
        PROFILE_SCOPE("Renderer Prep");
        Zero::RenderCommand::Clear(Zero::Color::Black);
    }
    {
        PROFILE_SCOPE("Renderer Draw");
        Zero::Renderer2D::BeginScene(m_CameraController.GetCamera());
        Zero::Renderer2D::DrawQuad({ -1.0f, -0.5f }, 0.0f, Zero::Vector2{ 10.0f }, m_Texture);
        Zero::Renderer2D::DrawQuad(Zero::Vector2::Zero, 0.0f, Zero::Vector2::One, Zero::Color::Red);
        Zero::Renderer2D::DrawQuad({ 0.5f, 1.0f }, 0.0f, Zero::Vector2::One, m_QuadColor);
        Zero::Renderer2D::EndScene();
    }
}

void ExampleLayer2D::OnEvent(Zero::Event& event)
{
    m_CameraController.OnEvent(event);
}

void ExampleLayer2D::OnUIRender()
{
    ImGui::Begin("Settings");
    {
        ImGui::ColorEdit4("Quad Color", glm::value_ptr(static_cast<glm::vec4&>(m_QuadColor)));

        for (auto& result : m_ProfileResults)
        {
            char label[50];
            strcpy(label, "%.3fms ");
            strcat(label, result.Name.c_str());
            ImGui::Text(label, result.Time);
        }
        m_ProfileResults.clear();
    }
    ImGui::End();
}
