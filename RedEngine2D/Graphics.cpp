#include "Graphics.h"

Graphics::Graphics(){}

Graphics::~Graphics()
{
	glUseProgram(0);
}

void Graphics::Init(MainWindow* windowPtr, Shader *spriteShader, Shader *textShader, Shader* simpleShader)
{
	this->window = windowPtr;
	this->spriteShader = spriteShader;
	this->textShader = textShader;
	this->simpleShader = simpleShader;

	spriteRenderer.Init();
	textRenderer.Init();
	textRenderer.UpdateFontInfo(Loader::GetFontInfo());

	this->projection = glm::ortho(0.0f, (float)window->GetBufferWidth(), (float)window->GetBufferHeight(), 0.0f, -1.0f, 1.0f);
}

void Graphics::Draw(spriteData drawData[], int drawDataSize, float viewCenterX, float viewCenterY)
{
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (int i = 0; i < drawDataSize; i++)
	{
		Texture tex = *(drawData[i].tex);
		float frameSize = drawData[i].frameSize;
		glm::vec2 loc(drawData[i].loc.x, drawData[i].loc.y);
		glm::vec2 scale(drawData[i].scale.x, drawData[i].scale.y);
		glm::vec3 color(drawData[i].color.x, drawData[i].color.y, drawData[i].color.z);
		float depth = drawData[i].depth;
		int frame = drawData[i].frame;
		float angle = drawData[i].angle;
		bool flipX = drawData[i].flipX;
		bool flipY = drawData[i].flipY;

		glm::vec3 eye(0.0f, 0.0f, 0.0f);
		glm::vec3 center(0.0f, 0.0f, -1.0f);
		glm::vec3 up(0.0f, 1.0f, 0.0f);

		if (!drawData[i].background)
		{
			eye.x = viewCenterX - window->GetBufferWidth()/2;
			eye.y = viewCenterY - window->GetBufferHeight()/2;
		}

		glm::mat4 view = glm::lookAt(eye, eye + center, up);

		//Draw Sprite
		spriteShader->Use();			
		spriteRenderer.Draw(tex, frameSize, frame, projection, view, loc, scale, angle, flipX, flipY, color, depth, spriteShader);

		//Draw Collision Box

		simpleShader->Use();
		glm::vec2 colLoc(drawData[i].collisionBoxLoc.x, drawData[i].collisionBoxLoc.y);
		glm::vec2 colScale(drawData[i].collisionBoxSize.x, drawData[i].collisionBoxSize.y);
		spriteRenderer.Draw(projection, view, colLoc, colScale, simpleShader);
	}

	window->SwapBuffers();
}
