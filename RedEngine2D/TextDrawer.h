#pragma once

#include <stdio.h>
#include <string>
#include <map>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Shader.h"
#include "CharInfo.h"

class TextDrawer
{
public:

	TextDrawer();

	~TextDrawer();

	void Init();

	void UpdateFontInfo(std::map <char, charInfo> fontInfo);

	void Draw(	std::string text,
				Texture fontAtlas,
				glm::vec2 position, 
				glm::vec2 scale, 
				glm::vec3 color, 
				Shader* shaderPtr);

private:

	std::map <char, charInfo> fontInfo;

	GLuint VAO;
	GLuint VBO;

};

