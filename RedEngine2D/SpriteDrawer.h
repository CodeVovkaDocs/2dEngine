#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Shader.h"

class SpriteDrawer
{
public:

	SpriteDrawer();

	~SpriteDrawer();

	void Init();

	void Draw(Texture tex,
			float frameSize,
			int frame, 
			glm::mat4 projection, 
			glm::mat4 view,
			glm::vec2 position, 
			glm::vec2 scale,
			double rotateAngle,
			bool flipX,
			bool flipY,
			glm::vec3 color, 
			float depth,
			Shader* shaderptr);

	void Draw(
		glm::mat4 projection,
		glm::mat4 view,
		glm::vec2 position,
		glm::vec2 scale,
		Shader* shaderptr);

	void Clear();

private:

	GLuint VAO; //Array object
	GLuint VBO; //Vertex buffer 
};

