#include "Shader.h"
#include <iostream>

Shader& Shader::Use()
{
	glUseProgram(ID);
	return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	unsigned int sVertex, sFragment, gShader;
	// vertex
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// fragment
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	// geometry shader (if included)
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}
	// link shader program
	ID = glCreateProgram();
	glAttachShader(ID, sVertex);
	glAttachShader(ID, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(ID, gShader);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	// delete the shaders, no longer needed
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::SetFloat(const char* name, float value, bool useShader)
{
	if (useShader) Use();
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetInteger(const char* name, int value, bool useShader)
{
	if (useShader) Use();
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetVector2f(const char* name, float x, float y, bool useShader)
{
	if (useShader) Use();
	glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
	if (useShader) Use();
	glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
	if (useShader) Use();
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
	if (useShader) Use();
	glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
	if (useShader) Use();
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
{
	if (useShader) Use();
	glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
	if (useShader) Use();
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- ------------------------------- --" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- -------------------------------- --" << std::endl;
		}
	}
}
