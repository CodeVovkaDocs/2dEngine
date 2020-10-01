#pragma once

#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include<GL/glew.h>

enum class texType
{
	IMAGE,
	FONT
};

class Texture
{
public:

	Texture();
	~Texture();

	void Generate(unsigned char* texData, int width, int height, texType type);
	void Use();
	void Clear();

	int GetWidth();
	int GetHeight();

private:
	GLuint textureId;
	int width, height;

};


#endif // !TEXTURE_HEADER




