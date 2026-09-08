#include <Zero/Zero.h>

#include <glm/gtc/matrix_transform.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Triangle Data    //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

float triangleVertices[]{
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, //
};

uint32_t triangleIndices[]{ 0, 1, 2 };

const std::string triangleVertexSource{ R"(
    #version 460 core

    layout (location = 0) in vec3 a_Position;
    layout (location = 1) in vec4 a_Color;

    uniform mat4 u_ViewProjectionMatrix;
    uniform mat4 u_ModelMatrix;

    out vec3 v_Position;
    out vec4 v_Color;

    void main()
    {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0f);
    }
)" };

const std::string triangleFragmentSource{ R"(
    #version 460 core

    in vec3 v_Position;
    in vec4 v_Color;

    out vec4 o_Color;

    void main()
    {
        o_Color = v_Color;
    }
)" };

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Quad Data    //////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

float quadVertices[]{
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top left
};

uint32_t quadIndices[]{ 0, 1, 3, 1, 2, 3 };

const std::string quadVertexSource{ R"(
    #version 460 core

    layout (location = 0) in vec3 a_Position;
    layout (location = 1) in vec4 a_Color;

    uniform mat4 u_ViewProjectionMatrix;
    uniform mat4 u_ModelMatrix;

    out vec3 v_Position;
    out vec4 v_Color;

    void main()
    {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0f);
    }
)" };

const std::string quadFragmentSource{ R"(
    #version 460 core

    in vec3 v_Position;
    in vec4 v_Color;

    out vec4 o_Color;

    void main()
    {
        o_Color = vec4(0.2f, 0.8f, 0.7f, 1.0f);
    }
)" };

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Sandbox Example Layer /////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExampleLayer : public Zero::Layer
{
public:
    ExampleLayer() : Layer{ "Example" }, m_Camera{ -1.6f, 1.6f, -0.9f, 0.9f }, m_CameraPosition{ 0.0f }
    {
        Zero::VertexBufferLayout layout{
            { Zero::AttributeType::Float3, "a_Position" },
            { Zero::AttributeType::Float4, "a_Color" },
        };

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        m_TriangleVertexArray.reset(Zero::VertexArray::Create());
        std::shared_ptr<Zero::VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer.reset(Zero::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
        triangleVertexBuffer->SetLayout(layout);
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
        std::shared_ptr<Zero::IndexBuffer> triangleIndexBuffer;
        triangleIndexBuffer.reset(
            Zero::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t))
        );
        m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);
        m_TriangleShader = std::make_shared<Zero::Shader>(triangleVertexSource, triangleFragmentSource);

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        m_QuadVertexArray.reset(Zero::VertexArray::Create());
        std::shared_ptr<Zero::VertexBuffer> quadVertexBuffer;
        quadVertexBuffer.reset(Zero::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
        quadVertexBuffer->SetLayout(layout);
        m_QuadVertexArray->AddVertexBuffer(quadVertexBuffer);
        std::shared_ptr<Zero::IndexBuffer> quadIndexBuffer;
        quadIndexBuffer.reset(Zero::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));
        m_QuadVertexArray->SetIndexBuffer(quadIndexBuffer);
        m_QuadShader = std::make_shared<Zero::Shader>(quadVertexSource, quadFragmentSource);
    }

public:
    virtual void OnUpdate(Zero::DeltaTime deltaTime) override
    {
        if (Zero::Input::IsKeyPressed(ZERO_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMovementSpeed * deltaTime;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMovementSpeed * deltaTime;

        if (Zero::Input::IsKeyPressed(ZERO_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMovementSpeed * deltaTime;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_UP))
            m_CameraPosition.y += m_CameraMovementSpeed * deltaTime;

        if (Zero::Input::IsKeyPressed(ZERO_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * deltaTime;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        if (Zero::Input::IsKeyPressed(ZERO_KEY_J))
            m_QuadPosition.x -= m_QuadMovementSpeed * deltaTime;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_L))
            m_QuadPosition.x += m_QuadMovementSpeed * deltaTime;

        if (Zero::Input::IsKeyPressed(ZERO_KEY_I))
            m_QuadPosition.y += m_QuadMovementSpeed * deltaTime;
        else if (Zero::Input::IsKeyPressed(ZERO_KEY_K))
            m_QuadPosition.y -= m_QuadMovementSpeed * deltaTime;

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        glm::mat4 triangleModelMatrix{ 1.0f };

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        Zero::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Zero::RenderCommand::Clear();

        Zero::Renderer::BeginScene(m_Camera);
        constexpr int count{ 20 };
        for (int y{ 0 }; y < count; ++y)
        {
            for (int x{ 0 }; x < count; ++x)
            {
                glm::vec3 position{ static_cast<float>(x) * 0.11f, static_cast<float>(y) * 0.11f, 0.0f };
                glm::mat4 quadModelMatrix{ glm::translate({ 1.0f }, position) *
                                            glm::scale({ 1.0f }, glm::vec3 { 0.1f }) };
                Zero::Renderer::Submit(m_QuadVertexArray, m_QuadShader, quadModelMatrix);
            }
        }

        Zero::Renderer::Submit(m_TriangleVertexArray, m_TriangleShader, triangleModelMatrix);

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
    float m_CameraMovementSpeed{ 1.0f };
    float m_CameraRotationSpeed{ 90.0f };
    float m_CameraRotation{ 0.0f };

    glm::vec3 m_QuadPosition{ 0.0f };
    float m_QuadMovementSpeed{ 1.0f };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Sandbox Application    ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sandbox : public Zero::Application
{
public:
    Sandbox() { PushLayer(new ExampleLayer()); }
    ~Sandbox() {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Application Creation   ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

Zero::Application* Zero::CreateApplication()
{
    return new Sandbox();
}
