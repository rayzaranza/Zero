#include "Zero/Application/Application.h"
#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Input/Input.h"

#include <glad/glad.h>

namespace Zero
{
    static GLenum GetOpenGLTypeFromAttributeType(AttributeType type);

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

        glCreateVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[3 * 7] {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //
            0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
            0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, //
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->SetLayout({ { AttributeType::Float3, "a_Position" }, { AttributeType::Float4, "a_Color" } });
        const VertexBufferLayout& layout { m_VertexBuffer->GetLayout() };

        uint32_t location { 0 };
        for (const VertexAttribute& attribute : layout)
        {
            glEnableVertexAttribArray(location);
            glVertexAttribPointer(
                location,
                attribute.ComponentCount,
                GetOpenGLTypeFromAttributeType(attribute.Type),
                attribute.IsNormalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                reinterpret_cast<const void*>(static_cast<uintptr_t>(attribute.Offset))
            );
            ++location;
        }

        uint32_t indices[3] { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

        const std::string vertexSource { R"(
            #version 460 core

            layout (location = 0) in vec3 a_Position;
            layout (location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0f);
            }
        )" };

        const std::string fragmentSource { R"(
            #version 460 core

            in vec3 v_Position;
            in vec4 v_Color;

            out vec4 o_Color;

            void main()
            {
                o_Color = v_Color;
            }
        )" };

        m_Shader = std::make_unique<Shader>(vertexSource, fragmentSource);
    }

    Application::~Application()
    {}

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher { event };
        dispatcher.Dispatch<WindowClosedEvent>(ZERO_BIND_FUNCTION(Application::OnWindowClosed));

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

            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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

    bool Application::OnWindowClosed(WindowClosedEvent& event)
    {
        m_IsRunning = false;
        return true;
    }

    GLenum GetOpenGLTypeFromAttributeType(AttributeType type)
    {
        switch (type)
        {
            case AttributeType::Float:
            case AttributeType::Float2:
            case AttributeType::Float3:
            case AttributeType::Float4:
            case AttributeType::Matrix3:
            case AttributeType::Matrix4: return GL_FLOAT;

            case AttributeType::Int:
            case AttributeType::Int2:
            case AttributeType::Int3:    return GL_INT;

            case AttributeType::Boolean: return GL_BOOL;

            default:
            {
                ZERO_CORE_ASSERT(false, "Unknow Vertex Attribute Type");
                return 0;
            }
        }
    }
}
