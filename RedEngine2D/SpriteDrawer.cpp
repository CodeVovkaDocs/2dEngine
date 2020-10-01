#include "SpriteDrawer.h"


SpriteDrawer::SpriteDrawer()
{
	VAO = 0;
	VBO = 0;
}

SpriteDrawer::~SpriteDrawer()
{
	Clear();
}

void SpriteDrawer::Clear()
{
	if (VAO != 0)
	{
		glDeleteBuffers(1, &VAO);
		VAO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

}
void SpriteDrawer::Init()
{
	//Set vertices - two triangles to create a sprite quad, u and t are x and y for texture
	/*
	GLfloat vertices[] = {

		//x     //y    //z      //u    //t
		-1.0f , -1.0f ,0.0f ,    0.0f , 0.0f,
		-1.0f ,  1.0f ,0.0f ,    0.0f , 1.0f,
		 1.0f , -1.0f ,0.0f ,    1.0f , 0.0f,

		-1.0f ,  1.0f ,0.0f ,    0.0f ,  1.0f,
		 1.0f , -1.0f ,0.0f ,    1.0f ,  0.0f,
		 1.0f ,  1.0f ,0.0f ,    1.0f ,  1.0f
	};
	*/
    /*
	GLfloat vertices[] = {

		//x     //y    //z      //u    //t
		-0.5f , -0.5f ,0.0f ,    0.0f , 0.0f,
		-0.5f ,  0.5f ,0.0f ,    0.0f , 1.0f,
		 0.5f , -0.5f ,0.0f ,    1.0f , 0.0f,

		-0.5f ,  0.5f ,0.0f ,    0.0f ,  1.0f,
		 0.5f , -0.5f ,0.0f ,    1.0f ,  0.0f,
		 0.5f ,  0.5f ,0.0f ,    1.0f ,  1.0f
	};
	*/
	
	GLfloat vertices[] = {

		//x     //y    //z      //u    //t
		 0.0f ,  1.0f ,0.0f ,    0.0f , 1.0f,
		 1.0f ,  0.0f ,0.0f ,    1.0f , 0.0f,
		 0.0f ,  0.0f ,0.0f ,    0.0f , 0.0f,

		 0.0f ,  1.0f ,0.0f ,    0.0f ,  1.0f,
		 1.0f ,  1.0f ,0.0f ,    1.0f ,  1.0f,
		 1.0f ,  0.0f ,0.0f ,    1.0f ,  0.0f
	};
	

	//Make VAO and VBO Buffers
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Give vertices to array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Set pointer to vertices at location = 0 for shader use
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
	glEnableVertexAttribArray(0);

	//Set pointer to texture coordinates at location = 1 for shader use
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	//After buffer data and pointers are set, unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteDrawer::Draw(Texture tex,
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
	Shader* shaderptr){

	//Calc texture shift by frame
	int rows = tex.GetHeight() / frameSize;
	int cols = tex.GetWidth() / frameSize;
	float frameShiftY = frame / cols;
	float frameShiftX = frame - frameShiftY * cols;

	if (frame > rows * cols - 1)
	{
		return;
	}
	
	glm::vec4 texShift = glm::vec4(frameShiftX / cols, frameShiftY / rows, rows, cols);

	//Apply texture shift to shader
	shaderptr->SetVector4(texShift, "texShift");

	//Location and scale matrix - model matrix
	//Calc rotate angle in rads
	double rotateAngleRads = glm::radians(rotateAngle);

	glm::mat4 model(1.0f);

	model = glm::translate(model, glm::vec3(position, depth));
	
	
	model = glm::translate(model, glm::vec3(scale*0.5f , 0.0f));
	model = glm::rotate(model, (float)rotateAngleRads, glm::vec3(0.0f, 0.0f, 1.0f));
	if (flipX)
	{
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (flipY)
	{
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	model = glm::translate(model, glm::vec3(scale*-0.5f, 0.0f));
	
	model = glm::scale(model, glm::vec3(scale, 1.0f));
	
	
	//MVP matrix
	glm::mat4 mvp = projection * view * model;

	//Apply MVP matrix to shader
	shaderptr->SetMatrix4(mvp,"mvp");

	//Set color
	shaderptr->SetVector3(color, "spriteColor");

	//Use texture
	tex.Use();

	//Draw vertices from vertex array
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonOffset(1.0f, 1.0f);

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

void SpriteDrawer::Draw(
	glm::mat4 projection,
	glm::mat4 view,
	glm::vec2 position,
	glm::vec2 scale,
	Shader* shaderptr)
 {

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position, 1.0f));
	model = glm::scale(model, glm::vec3(scale, 1.0f));
	//MVP matrix
	glm::mat4 mvp = projection * view * model;
	//Apply MVP matrix to shader
	shaderptr->SetMatrix4(mvp, "mvp");
	//Draw vertices from vertex array
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonOffset(1.0f, 1.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 6);
	glBindVertexArray(0);

}