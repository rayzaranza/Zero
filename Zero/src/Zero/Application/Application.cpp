#include "Application.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Input/Input.h"

#include <glad/glad.h>

namespace Zero
{
    Application* Application::s_Instance { nullptr };

    Application::Application()
        : m_Window { std::make_unique<Window>() },
          m_UILayer { new UILayer() },
          m_IsRunning { true }
    {
        ZERO_ASSERT(s_Instance == nullptr, "Application already exists");
        s_Instance = this;
        m_Window->SetEventCallback(ZERO_BIND_FUNCTION(Application::OnEvent));
        PushOverlay(m_UILayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        constexpr float vertices[3 * 3] {
            -0.5f, -0.5f, 0.0f, //
            0.5f,  -0.5f, 0.0f, //
            0.0f,  0.5f,  0.0f, //
        };

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        constexpr unsigned int indices[3] { 0, 1, 2 };

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        const std::string vertexSource { R"(
            #version 460 core

            layout (location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0f);
            }
        )" };

        const std::string fragmentSource { R"(
            #version 460 core

            in vec3 v_Position;

            out vec4 o_Color;

            void main()
            {
                o_Color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
            }
        )" };

        m_Shader = std::make_unique<Shader>(vertexSource, fragmentSource);
    }

    Application::~Application()
    {}

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher { event };
        dispatcher.Dispatch<WindowClosedEvent>(ZERO_BIND_FUNCTION(Application::onWindowClosed));

        for (LayerPointerArray::iterator iterator { m_LayerStack.end() }; iterator != m_LayerStack.begin();)
        {
            (*--iterator)->OnEvent(event);
            if (event.IsHandled())
            {
                break;
            }
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    Window& Application::GetWindow() const
    {
        return *m_Window;
    }

    Application& Application::Get()
    {
        return *s_Instance;
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(m_VertexArray);
            m_Shader->Bind();

            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_UILayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUIRender();
            }
            m_UILayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::onWindowClosed(WindowClosedEvent& event)
    {
        m_IsRunning = false;
        return true;
    }
}
