#include "Shader.h"


Shader::Shader()
{
	shaderID = 0;
}

Shader::~Shader()
{
	Clear();
}

void Shader::Clear()
{
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
}

void Shader::Compile(std::string  vertexShaderData, std::string  fragmentShaderData)
{
	GLint success;
	GLchar log[1024] = { 0 };
	
	shaderID = glCreateProgram();

	Add(shaderID, vertexShaderData.c_str(), GL_VERTEX_SHADER);
	Add(shaderID, fragmentShaderData.c_str(), GL_FRAGMENT_SHADER);

	glLinkProgram(shaderID);

	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 1024, NULL, log);
		printf("Error linking program %s", log);
	}

	glValidateProgram(shaderID);

	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 1024, NULL, log);
		printf("Error validating program %s", log);
	}

}

void Shader::Add(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLint success;
	GLchar log[1024] = { 0 };

	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 1024, NULL, log);
		printf("Error adding shader %s", log);
	}
	
	glAttachShader(program, shader);
}

void Shader::Use()
{
	glUseProgram(shaderID);
}

void Shader::SetMatrix4(glm::mat4 model,const char* name)
{
   GLint Location = glGetUniformLocation(shaderID, name);	
   glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::SetVector4(glm::vec4 vector, const char* name)
{
	GLint Location = glGetUniformLocation(shaderID, name);
	glUniform4fv(Location, 1, glm::value_ptr(vector));
}


void Shader::SetVector3(glm::vec3 vector, const char* name)
{
	GLint Location = glGetUniformLocation(shaderID, name);
	glUniform3fv(Location, 1, glm::value_ptr(vector));
}

void Shader::SetVector2(glm::vec2 vector, const char* name)
{
	GLint Location = glGetUniformLocation(shaderID, name);
	glUniform2fv(Location, 1, glm::value_ptr(vector));
}