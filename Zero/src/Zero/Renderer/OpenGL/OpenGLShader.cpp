#include "Zero/Renderer/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Zero
{
    OpenGLShader::OpenGLShader(const String& filePath) : m_Name{ ExtractNameFromFilePath(filePath) }
    {
        const String source{ ReadFile(filePath) };
        const Map<U32, String> shaderSources{ PreProcess(source) };
        OpenGLShader::Compile(shaderSources);
    }

    OpenGLShader::OpenGLShader(const String& name, const String& vertexSource, const String& fragmentSource) : m_Name{ name }
    {
        const Map<U32, String> shaderSources{
            { GL_VERTEX_SHADER, vertexSource },
            { GL_FRAGMENT_SHADER, fragmentSource },
        };
        OpenGLShader::Compile(shaderSources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_Id);
    }

    void OpenGLShader::Compile(const Map<U32, String>& shaderSources)
    {
        const U32 program{ glCreateProgram() };

        ZR_CORE_ASSERT(shaderSources.size() <= MAX_SHADERS_SUPPORTED, "Only 2 shaders are supported");

        FixedArray<U32, MAX_SHADERS_SUPPORTED> shaderIds{};
        I32 shaderIdIndex{ 0 };

        for (auto& [type, source] : shaderSources)
        {
            const U32 shader{ glCreateShader(type) };
            const char* sourceRaw{ source.c_str() };
            glShaderSource(shader, 1, &sourceRaw, 0);
            glCompileShader(shader);

            const Boolean isCompiled{ CheckShaderErrors(shader) };
            ZR_CORE_ASSERT(isCompiled, "Shader compilation error");

            if (!isCompiled)
                continue;

            glAttachShader(program, shader);
            shaderIds[shaderIdIndex++] = shader;
        }

        glLinkProgram(program);
        const Boolean isLinked{ CheckProgramErrors(program, shaderIds) };
        ZR_CORE_ASSERT(isLinked, "Shader linking error");

        if (!isLinked)
            return;

        for (U32 shaderId : shaderIds)
        {
            glDetachShader(program, shaderId);
            glDeleteShader(shaderId);
        }

        m_Id = program;
    }

    String OpenGLShader::ReadFile(const String& filePath)
    {
        String result{};
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

    Map<U32, String> OpenGLShader::PreProcess(const String& source)
    {
        Map<U32, String> shaderSources{};

        const char* typeToken{ "#type" };
        const Length typeTokenLength{ strlen(typeToken) };
        Length position{ source.find(typeToken, 0) };

        while (position != String::npos)
        {
            const Length endOfLine{ source.find_first_of("\r\n", position) };

            ZR_CORE_ASSERT(endOfLine != String::npos, "Syntax error");

            if (endOfLine == String::npos)
                break;

            const Length typeNameBegin{ position + typeTokenLength + 1 };

            const String typeName{ source.substr(typeNameBegin, endOfLine - typeNameBegin) };
            const U32 type{ StringToShaderType(typeName) };

            ZR_CORE_ASSERT(type, "Invalid Shader Type");

            const Length nextLinePosition{ source.find_first_of("\r\n", endOfLine) };
            position = source.find(typeToken, nextLinePosition);

            if (!type)
                continue;

            const Length blockEnd{ position == String::npos ? source.size() : position };
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

    void OpenGLShader::SetMatrix4(const String& name, const Matrix4& matrix) const
    {
        const I32 location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetVector4(const String& name, const Vector4& vector) const
    {
        const I32 location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }

    void OpenGLShader::SetVector3(const String& name, const Vector3& vector) const
    {
        const I32 location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform3f(location, vector.x, vector.y, vector.z);
    }

    void OpenGLShader::SetFloat2(const String& name, const Vector2& vector) const
    {
        const I32 location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform2f(location, vector.x, vector.y);
    }

    void OpenGLShader::SetFloat(const String& name, F32 value) const
    {
        const I32 location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform1f(location, value);
    }

    void OpenGLShader::SetInt(const String& name, I32 value) const
    {
        const I32 location{ glGetUniformLocation(m_Id, name.c_str()) };
        glUniform1i(location, value);
    }

    U32 OpenGLShader::StringToShaderType(const String& type)
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

    String OpenGLShader::ExtractNameFromFilePath(const String& filePath)
    {
        Length lastSlashPosition{ filePath.find_last_of("/\\") };
        lastSlashPosition = lastSlashPosition == String::npos ? 0 : lastSlashPosition + 1;
        Length lastDotPosition{ filePath.rfind(".") };
        Length count{ lastDotPosition == String::npos ? filePath.size() - lastSlashPosition : lastDotPosition - lastSlashPosition };
        return filePath.substr(lastSlashPosition, count);
    }

    Boolean OpenGLShader::CheckShaderErrors(U32 shader)
    {
        I32 isCompiled{};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            I32 maxLength{ 0 };
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            Array<char> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());
            glDeleteShader(shader);

            ZR_CORE_ERROR("{0}", infoLog.data());
            return false;
        }

        return true;
    }

    Boolean OpenGLShader::CheckProgramErrors(U32 program, const FixedArray<U32, MAX_SHADERS_SUPPORTED>& shaderIds)
    {
        I32 isLinked{ 0 };
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            I32 maxLength{ 0 };
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            Array<char> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

            for (U32 shaderId : shaderIds)
                glDeleteShader(shaderId);

            glDeleteProgram(program);

            ZR_CORE_ERROR("{0}", infoLog.data());
            return false;
        }

        return true;
    }
}
