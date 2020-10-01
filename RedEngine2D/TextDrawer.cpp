#include "TextDrawer.h"

TextDrawer::TextDrawer()
{
	VAO = 0;
	VBO = 0;

}
TextDrawer::~TextDrawer()
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

void TextDrawer::Init()
{

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 30, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextDrawer::UpdateFontInfo(std::map <char, charInfo> fontInfo)
{
	this->fontInfo = fontInfo;
}


void TextDrawer::Draw(std::string text, 
						Texture fontAtlas, 
						glm::vec2 position, 
						glm::vec2 scale,
						glm::vec3 color, 
						Shader* shaderPtr){



	glBindVertexArray(VAO);

	shaderPtr->SetVector3(color, "textColor");

	fontAtlas.Use();

	for (std::string::iterator c = text.begin(); c != text.end(); ++c)
	{
		float w = (float)(fontAtlas.GetWidth());
		float h = (float)(fontAtlas.GetHeight());

		charInfo ci = fontInfo[*c];

		GLfloat x1 = position.x + ci.xoffset * scale.x;
		GLfloat x2 = x1 + ci.width * scale.x;
		GLfloat y1 = position.y + ( ci.yoffset) * scale.y;
		GLfloat y2 = y1 + ci.height * scale.y;

		GLfloat tX1 = ci.atlasX/w ;
		GLfloat tX2 =  ci.atlasX / w + ci.width / w;
		GLfloat tY1 = (ci.atlasY)/h ;
		GLfloat tY2 = (ci.atlasY)/h  + ci.height/h ;

		GLfloat zVal = 0.8f;

		GLfloat charVertices[] = {

			 //x  //y  //z      //u   //t
			 x1 , y1 , zVal ,  tX1 , tY1,
			 x1 , y2 , zVal ,  tX1 , tY2,
			 x2 , y1 , zVal ,  tX2 , tY1,

			 x1 , y2 , zVal ,  tX1 , tY2,
			 x2 , y1 , zVal ,  tX2 , tY1,
			 x2 , y2 , zVal ,  tX2 , tY2

		};

		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(charVertices), charVertices);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);


		position.x += ci.xAdvance * scale.x;
	}

	glBindVertexArray(0);
}
