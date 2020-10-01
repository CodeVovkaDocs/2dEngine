#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "MainWindow.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteDrawer.h"
#include "TextDrawer.h"
#include "SpriteData.h"

#include "Loader.h"


class Graphics
{
public:

	Graphics();
	~Graphics();

	void Init(MainWindow* windowPtr, Shader *spriteShader, Shader *textShader, Shader* simpleShader);

	void Draw(spriteData drawData[], int drawDataSize, float viewCenterX,float viewCenterY);

	double GetWindowHeight() { return window->GetBufferHeight(); };
	double GetWindowWidth() { return window->GetBufferWidth(); };

private:

	MainWindow* window;
	Shader* spriteShader;
	Shader* textShader;
	Shader* simpleShader;
	SpriteDrawer spriteRenderer;
	TextDrawer textRenderer;
	glm::mat4 projection;
};

