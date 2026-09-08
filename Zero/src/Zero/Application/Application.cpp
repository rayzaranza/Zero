#include "Zero/Application/Application.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Input/Input.h"
#include "Zero/Renderer/Renderer.h"

namespace Zero
{
    Application* Application::s_Instance { nullptr };

    Application::Application()
        : m_Window { std::make_unique<Window>() },
          m_UILayer { new UILayer() },
          m_IsRunning { true },
          m_Camera { -1.6f, 1.6f, -0.9f, 0.9f }
    {
        ZERO_CORE_ASSERT(s_Instance == nullptr, "Application already exists");
        s_Instance = this;
        m_Window->SetEventCallback(ZERO_BIND_FUNCTION(Application::OnEvent));
        PushOverlay(m_UILayer);

        VertexBufferLayout layout {
            { AttributeType::Float3, "a_Position" },
            { AttributeType::Float4, "a_Color" },
        };

        // ····················································································································
        // Triangle
        // ····················································································································

        m_TriangleVertexArray.reset(VertexArray::Create());

        float triangleVertices[] {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //
            0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
            0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, //
        };
        std::shared_ptr<VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
        triangleVertexBuffer->SetLayout(layout);
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

        uint32_t indices[] { 0, 1, 2 };
        std::shared_ptr<IndexBuffer> triangleIndexBuffer;
        triangleIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

        const std::string triangleVertexSource { R"(
            #version 460 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            uniform mat4 u_ViewProjectionMatrix;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0f);
            }
        )" };

        const std::string triangleFragmentSource { R"(
            #version 460 core

            in vec3 v_Position;
            in vec4 v_Color;

            out vec4 o_Color;

            void main()
            {
                o_Color = v_Color;
            }
        )" };

        m_TriangleShader = std::make_shared<Shader>(triangleVertexSource, triangleFragmentSource);

        // ····················································································································
        // Quad
        // ····················································································································

        m_QuadVertexArray.reset(VertexArray::Create());
        constexpr float i { 1.1f };
        float quadVertices[] {
            0.5f * i,  0.5f * i,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
            0.5f * i,  -0.5f * i, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom right
            -0.5f * i, -0.5f * i, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom left
            -0.5f * i, 0.5f * i,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top left
        };

        std::shared_ptr<VertexBuffer> quadVertexBuffer;
        quadVertexBuffer.reset(VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
        quadVertexBuffer->SetLayout(layout);
        m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

        uint32_t quadIndices[] { 0, 1, 3, 1, 2, 3 };
        std::shared_ptr<IndexBuffer> quadIndexBuffer;
        quadIndexBuffer.reset(IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
        m_QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

        const std::string quadVertexSource { R"(
            #version 460 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjectionMatrix;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0f);
            }
        )" };

        const std::string quadFragmentSource { R"(
            #version 460 core

            in vec3 v_Position;
            in vec4 v_Color;

            out vec4 o_Color;

            void main()
            {
                o_Color = vec4(0.2f, 0.8f, 0.7f, 1.0f);
            }
        )" };

        m_QuadShader = std::make_shared<Shader>(quadVertexSource, quadFragmentSource);

        ZERO_CORE_LOG("Application created");
    }

    Application::~Application()
    {
        ZERO_CORE_LOG("Application destroyed");
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher { event };
        dispatcher.Dispatch<WindowClosedEvent>(ZERO_BIND_FUNCTION(Application::OnWindowClosed));

        for (std::vector<Layer*>::iterator iterator { m_LayerStack.end() }; iterator != m_LayerStack.begin();)
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

    void Application::Run()
    {
        while (m_IsRunning)
        {
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            // ····································································

            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::Clear();

            // ····································································

            m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
            m_Camera.SetRotation(45.0f);

            Renderer::BeginScene(m_Camera);
            Renderer::Submit(m_QuadVertexArray, m_QuadShader);
            Renderer::Submit(m_TriangleVertexArray, m_TriangleShader);
            Renderer::EndScene();

            // ····································································

            m_UILayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUIRender();
            }
            m_UILayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClosed(WindowClosedEvent& event)
    {
        m_IsRunning = false;
        return true;
    }
}
