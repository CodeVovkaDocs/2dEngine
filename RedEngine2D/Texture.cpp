#include "Texture.h"

Texture::Texture()
{
	textureId = 0;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
}

void Texture::Clear()
{
	glDeleteTextures(1, &textureId);
	textureId = 0;
	width = 0;
	height = 0;
}


void Texture::Generate(unsigned char* texData, int width, int height,texType type)
{
	GLenum format = GL_RGBA;

	if (type == texType::IMAGE)
	{
		format = GL_RGBA;
	}

	if (type == texType::FONT)
	{
		format = GL_RED;
	}

	this->width = width;
	this->height = height;

	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, texData);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}