#include "Zero/Renderer/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Zero
{
    OpenGLShader::OpenGLShader(const std::string& filePath) : m_Name{ ExtractNameFromFilePath(filePath) }
    {
        const std::string source{ ReadFile(filePath) };
        const std::unordered_map<GLenum, std::string> shaderSources{ PreProcess(source) };
        OpenGLShader::Compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource) : m_Name{ name }
    {
        const std::unordered_map<GLenum, std::string> shaderSources{
            { GL_VERTEX_SHADER, vertexSource },
            { GL_FRAGMENT_SHADER, fragmentSource },
        };
        OpenGLShader::Compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_Id);
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
    {
        const GLuint program{ glCreateProgram() };

        ZR_CORE_ASSERT(shaderSources.size() <= MAX_SHADERS_SUPPORTED, "Only 2 shaders are supported");

        std::array<GLenum, MAX_SHADERS_SUPPORTED> shaderIds{};
        int shaderIdIndex{ 0 };

        for (auto& [type, source] : shaderSources)
        {
            const GLuint shader{ glCreateShader(type) };
            const GLchar* sourceRaw{ source.c_str() };
            glShaderSource(shader, 1, &sourceRaw, 0);
            glCompileShader(shader);

            const bool isCompiled{ CheckShaderErrors(shader) };
            ZR_CORE_ASSERT(isCompiled, "Shader compilation error");

            if (!isCompiled)
                continue;

            glAttachShader(program, shader);
            shaderIds[shaderIdIndex++] = shader;
        }

        glLinkProgram(program);
        const bool isLinked{ CheckProgramErrors(program, shaderIds) };
        ZR_CORE_ASSERT(isLinked, "Shader linking error");

        if (!isLinked)
            return;

        for (GLuint shaderId : shaderIds)
        {
            glDetachShader(program, shaderId);
            glDeleteShader(shaderId);
        }

        m_Id = program;
    }

    std::string OpenGLShader::ReadFile(const std::string& filePath)
    {
        std::string result{};
        std::ifstream inputStream{ filePath, std::ios::in | std::ios::binary };

        if (!inputStream.is_open())
        {
            ZR_CORE_ERROR("Could not open file: {0}", filePath);
            return result;
        }

        inputStream.seekg(0, std::ios::end);
        result.resize(inputStream.tellg());
        inputStream.seekg(0, std::ios::beg);
        inputStream.read(&result[0], result.size());
        inputStream.close();
        return result;
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shaderSources{};

        const char* typeToken{ "#type" };
        const size_t typeTokenLength{ strlen(typeToken) };
        size_t position{ source.find(typeToken, 0) };

        while (position != std::string::npos)
        {
            const size_t endOfLine{ source.find_first_of("\r\n", position) };

            ZR_CORE_ASSERT(endOfLine != std::string::npos, "Syntax error");

            if (endOfLine == std::string::npos)
                break;

            const size_t typeNameBegin{ position + typeTokenLength + 1 };

            const std::string typeName{ source.substr(typeNameBegin, endOfLine - typeNameBegin) };
            const GLenum type{ StringToShaderType(typeName) };

            ZR_CORE_ASSERT(type, "Invalid Shader Type");

            const size_t nextLinePosition{ source.find_first_of("\r\n", endOfLine) };
            position = source.find(typeToken, nextLinePosition);

            if (!type)
                continue;

            const size_t blockEnd{ position == std::string::npos ? source.size() : position };
            shaderSources[type] = source.substr(nextLinePosition, blockEnd - nextLinePosition);
        }

        return shaderSources;
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
        const int location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec4& vector) const
    {
        const int location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec3& vector) const
    {
        const int location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform3f(location, vector.x, vector.y, vector.z);
    }

    void OpenGLShader::SetUniform(const std::string& name, const glm::vec2& vector) const
    {
        const int location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform2f(location, vector.x, vector.y);
    }

    void OpenGLShader::SetUniform(const std::string& name, float value) const
    {
        const int location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform1f(location, value);
    }

    void OpenGLShader::SetUniform(const std::string& name, int value) const
    {
        const int location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform1i(location, value);
    }

    GLenum OpenGLShader::StringToShaderType(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment")
            return GL_FRAGMENT_SHADER;
        if (type == "compute")
            return GL_COMPUTE_SHADER;
        if (type == "geometry")
            return GL_GEOMETRY_SHADER;

        ZR_CORE_ASSERT(false, "Unknow shader type");
        return 0;
    }

    std::string OpenGLShader::ExtractNameFromFilePath(const std::string& filePath)
    {
        size_t lastSlashPosition{ filePath.find_last_of("/\\") };
        lastSlashPosition = lastSlashPosition == std::string::npos ? 0 : lastSlashPosition + 1;
        size_t lastDotPosition{ filePath.rfind(".") };
        size_t count{ lastDotPosition == std::string::npos ? filePath.size() - lastSlashPosition : lastDotPosition - lastSlashPosition };
        return filePath.substr(lastSlashPosition, count);
    }

    bool OpenGLShader::CheckShaderErrors(GLuint shader)
    {
        GLint isCompiled{};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            int32_t maxLength{ 0 };
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());
            glDeleteShader(shader);

            ZR_CORE_ERROR("{0}", infoLog.data());
            return false;
        }

        return true;
    }

    bool OpenGLShader::CheckProgramErrors(GLuint program, const std::array<GLuint, MAX_SHADERS_SUPPORTED>& shaderIds)
    {
        int isLinked{ 0 };
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            int32_t maxLength{ 0 };
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

            for (GLuint shaderId : shaderIds)
                glDeleteShader(shaderId);

            glDeleteProgram(program);

            ZR_CORE_ERROR("{0}", infoLog.data());
            return false;
        }

        return true;
    }
}
