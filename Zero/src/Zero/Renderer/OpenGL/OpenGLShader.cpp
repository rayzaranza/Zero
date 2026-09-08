#include "Zero/Renderer/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Zero
{
    OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource) : m_Id { glCreateProgram() }
    {
        uint32_t vertexShader { glCreateShader(GL_VERTEX_SHADER) };
        const char* source { vertexSource.c_str() };
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);

        int isCompiled { 0 };
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            int32_t maxLength { 0 };
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog.data());
            glDeleteShader(vertexShader);

            ZERO_CORE_ERROR("{0}", infoLog.data());
            ZERO_CORE_ASSERT(false, "Vertex shader compilation error");
            return;
        }

        uint32_t fragmentShader { glCreateShader(GL_FRAGMENT_SHADER) };
        source = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            int32_t maxLength { 0 };
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog.data());
            glDeleteShader(fragmentShader);
            glDeleteShader(vertexShader);

            ZERO_CORE_ERROR("{0}", infoLog.data());
            ZERO_CORE_ASSERT(false, "Fragment shader compilation error");
            return;
        }

        glAttachShader(m_Id, vertexShader);
        glAttachShader(m_Id, fragmentShader);
        glLinkProgram(m_Id);

        int isLinked { 0 };
        glGetProgramiv(m_Id, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            int32_t maxLength { 0 };
            glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(m_Id, maxLength, &maxLength, infoLog.data());

            glDeleteProgram(m_Id);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            ZERO_CORE_ERROR("{0}", infoLog.data());
            ZERO_CORE_ASSERT(false, "Shader linking error");
            return;
        }

        glDetachShader(m_Id, vertexShader);
        glDetachShader(m_Id, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_Id);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_Id);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::mat4& matrix) const
    {
        int location { glGetUniformLocation(m_Id, name.c_str()) };
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec4& vector) const
    {
        int location { glGetUniformLocation(m_Id, name.c_str()) };
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec3& vector) const
    {
        int location { glGetUniformLocation(m_Id, name.c_str()) };
        glUniform3f(location, vector.x, vector.y, vector.z);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec2& vector) const
    {
        int location { glGetUniformLocation(m_Id, name.c_str()) };
        glUniform2f(location, vector.x, vector.y);
    }

    void OpenGLShader::SetUniform(const std::string& name, float value) const
    {
        int location { glGetUniformLocation(m_Id, name.c_str()) };
        glUniform1f(location, value);
    }
}
