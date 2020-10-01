#pragma once

#include <stdio.h>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

	Shader();
	~Shader();

	void Compile(std::string vertexShaderData, std::string  fragmentShaderData);

	void Use();

	void SetMatrix4(glm::mat4 model, const char* name);

	void SetVector4(glm::vec4 vector, const char* name);

	void SetVector3(glm::vec3 vector, const char* name);

	void SetVector2(glm::vec2 vector, const char* name);

	void Clear();

private:

	GLuint shaderID;

	void Add(GLuint program, const char* shaderCode, GLenum shaderType);

};

