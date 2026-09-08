#include <Zero/Zero.h>

// ················································································································
//  Sandbox Example Layer
// ················································································································

class ExampleLayer : public Zero::Layer
{
  public:
    ExampleLayer() : Layer { "Example" }, m_Camera { -1.6f, 1.6f, -0.9f, 0.9f }, m_CameraPosition { 0.0f }
    {
        Zero::VertexBufferLayout layout {
            { Zero::AttributeType::Float3, "a_Position" },
            { Zero::AttributeType::Float4, "a_Color" },
        };

        // ····················································································································
        // Triangle
        // ····················································································································

        m_TriangleVertexArray.reset(Zero::VertexArray::Create());

        float triangleVertices[] {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //
            0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
            0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, //
        };
        std::shared_ptr<Zero::VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer.reset(Zero::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
        triangleVertexBuffer->SetLayout(layout);
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);

        uint32_t indices[] { 0, 1, 2 };
        std::shared_ptr<Zero::IndexBuffer> triangleIndexBuffer;
        triangleIndexBuffer.reset(Zero::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

        m_TriangleShader = std::make_shared<Zero::Shader>(triangleVertexSource, triangleFragmentSource);

        // ····················································································································
        // Quad
        // ····················································································································

        m_QuadVertexArray.reset(Zero::VertexArray::Create());
        constexpr float i { 1.1f };
        float quadVertices[] {
            0.5f * i,  0.5f * i,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
            0.5f * i,  -0.5f * i, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom right
            -0.5f * i, -0.5f * i, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom left
            -0.5f * i, 0.5f * i,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top left
        };

        std::shared_ptr<Zero::VertexBuffer> quadVertexBuffer;
        quadVertexBuffer.reset(Zero::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
        quadVertexBuffer->SetLayout(layout);
        m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

        uint32_t quadIndices[] { 0, 1, 3, 1, 2, 3 };
        std::shared_ptr<Zero::IndexBuffer> quadIndexBuffer;
        quadIndexBuffer.reset(Zero::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
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

        m_QuadShader = std::make_shared<Zero::Shader>(quadVertexSource, quadFragmentSource);
    }

  public:
    virtual void OnUpdate() override
    {
        if (Zero::Input::IsKeyPressed(ZERO_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMovementSpeed;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMovementSpeed;

        if (Zero::Input::IsKeyPressed(ZERO_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMovementSpeed;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_UP))
            m_CameraPosition.y += m_CameraMovementSpeed;

        if (Zero::Input::IsKeyPressed(ZERO_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed;

        Zero::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Zero::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Zero::Renderer::BeginScene(m_Camera);
        Zero::Renderer::Submit(m_QuadVertexArray, m_QuadShader);
        Zero::Renderer::Submit(m_TriangleVertexArray, m_TriangleShader);
        Zero::Renderer::EndScene();
    }

    virtual void OnEvent(Zero::Event& event) override {}

    virtual void OnUIRender() override {}

  private:
    std::shared_ptr<Zero::Shader> m_TriangleShader;
    std::shared_ptr<Zero::Shader> m_QuadShader;
    std::shared_ptr<Zero::VertexArray> m_TriangleVertexArray;
    std::shared_ptr<Zero::VertexArray> m_QuadVertexArray;
    Zero::CameraOrthographic m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMovementSpeed { 0.05f };
    float m_CameraRotationSpeed { 0.8f };
    float m_CameraRotation { 0.0f };
};

// ················································································································
//  Sandbox Application
// ················································································································

class Sandbox : public Zero::Application
{
  public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() {}
};

// ················································································································
//  Zero Application Creation
// ················································································································

Zero::Application* Zero::CreateApplication()
{
    return new Sandbox();
}
