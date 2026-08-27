#include "../Asset/Asset.h"
#include "../Logger/Logger.h"
#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

const std::string SHADERS_FOLDER{ "../../../assets/shaders/" };

ZY::Shader::Shader(const std::string& name) :
	id{ glCreateProgram() },
	name{ name }
{
	compileAndLinkShader(name);
	LOG("Shader #{} created: {}", id, name);
	bind();
}

ZY::Shader::~Shader()
{
	glDeleteProgram(id);
	LOG("Shader #{} destroyed: {}.", id, name);
}

void ZY::Shader::compileAndLinkShader(const std::string& name)
{
	const std::string vertexShaderPath{ SHADERS_FOLDER + name + ".vert" };
	const std::string vertexSourceString{ ZY::Asset::getFileContent(vertexShaderPath) };
	const char* vertexSource{ vertexSourceString.c_str() };
	unsigned int vertex{ createShader(vertexSource, GL_VERTEX_SHADER) };

	const std::string fragmentShaderPath{ SHADERS_FOLDER + name + ".frag" };
	const std::string fragmentSourceString{ ZY::Asset::getFileContent(fragmentShaderPath) };
	const char* fragmentSource{ fragmentSourceString.c_str() };
	unsigned int fragment{ createShader(fragmentSource, GL_FRAGMENT_SHADER) };

	glLinkProgram(id);

	int success;
	char infoLog[512];
	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		LOG_ERROR("Error linking shader program #{}. Details: {}", id, infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void ZY::Shader::bind() const
{
	glUseProgram(id);
}

void ZY::Shader::setUniform(const std::string& name, const float& value) const
{
	bind();
	const int location{ glGetUniformLocation(id, name.c_str()) };
	glUniform1f(location, value);
}

void ZY::Shader::setUniform(const std::string& name, const glm::vec4& vector) const
{
	bind();
	const int location{ glGetUniformLocation(id, name.c_str()) };
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void ZY::Shader::setUniform(const std::string& name, const glm::vec3& vector) const
{
	bind();
	const int location{ glGetUniformLocation(id, name.c_str()) };
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ZY::Shader::setUniform(const std::string& name, const glm::vec2& vector) const
{
	bind();
	const int location{ glGetUniformLocation(id, name.c_str()) };
	glUniform2f(location, vector.x, vector.y);
}

void ZY::Shader::setUniform(const std::string& name, const glm::mat4& matrix) const
{
	bind();
	const int location{ glGetUniformLocation(id, name.c_str()) };
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

unsigned int ZY::Shader::createShader(const std::string& source, GLenum type) const
{
	const char* sourceChar{ source.c_str() };
	unsigned int shader{ glCreateShader(type) };

	glShaderSource(shader, 1, &sourceChar, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		LOG_ERROR("Error compiling shader #{}. Details: {}", id, infoLog);
	}

	glAttachShader(id, shader);
	return shader;
}
