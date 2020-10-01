#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Loader.h"


std::map <std::string, Texture> Loader::textures;
std::map <char, charInfo> Loader::fontInfo;
std::map <std::string, Shader*> Loader::shaders;


std::string Loader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream;

	fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		fileStream.open(fileLocation);
		std::stringstream stream;
		stream << fileStream.rdbuf();
		fileStream.close();
		content = stream.str();
	}
	catch (std::fstream::failure fail)
	{
		printf("ERROR: read file %s", fileLocation);
	}


	return content;
}

void Loader::LoadShader(const char* vertexFileLocation, const char* fragmentFileLocation,const char* name)
{
	std::string vertexShaderData = ReadFile(vertexFileLocation);
	std::string  fragmentShaderData = ReadFile(fragmentFileLocation);

	Shader* shader = new Shader();
	shader->Compile(vertexShaderData, fragmentShaderData);

	shaders[name] = shader;

}

Shader* Loader::GetShader(std::string shaderName)
{
	return shaders[shaderName];
}


void Loader::LoadTexture(const char* textureLoc, const char* textureName, texType format)
{
	Texture texture;

	int width, height, bitDepth;

	unsigned char* texData = stbi_load(textureLoc, &width, &height, &bitDepth, 0);

	if (!texData)
	{
		printf("Failed to load tex:%s", textureLoc);
		return;
	}
	
	texture.Generate(texData, width, height, format);
	textures[textureName] = texture;

	stbi_image_free(texData);

}


Texture* Loader::GetTexture(std::string textureName)
{
	return &textures[textureName];
}


int Loader::findIntInFontDataLine(std::string line, std::string var)
{
	if (line.find(var) != std::string::npos)
	{
		int val = std::stoi(line.substr(line.find(var) + var.length(), 3));
		return val;
	}
	else
		return 0;
}


void Loader::LoadFontData(const char* fondDataLoc)
{
	std::ifstream stream(fondDataLoc);

	if (!stream)
	{
		printf("Failed to open font data %s", fondDataLoc);
		return;
	}

	charInfo chInf;

	while (stream) 
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("char ") != std::string::npos)
		{
			chInf.atlasX = findIntInFontDataLine(line, "x="); 
			chInf.atlasY = findIntInFontDataLine(line, "y="); 
			chInf.width = findIntInFontDataLine(line, "width="); 
			chInf.height = findIntInFontDataLine(line, "height="); 
			chInf.xoffset = findIntInFontDataLine(line, "xoffset="); 
			chInf.yoffset = findIntInFontDataLine(line, "yoffset="); 
			chInf.xAdvance = findIntInFontDataLine(line, "xadvance="); 

			int charASCII = findIntInFontDataLine(line, "id=");
			char theChar = charASCII;

			fontInfo[theChar] = chInf;

		}

	}
}


std::map <char, charInfo> Loader::GetFontInfo()
{
	return fontInfo;
}


const char* Loader::ReadLevelData(const char* fileLocation)
{
	std::ifstream stream(fileLocation);
	std::string data = "";

	if (!stream)
	{
		printf("Failed to open level data %s", fileLocation);
	}

	while (stream)
	{
		std::string temp;
		std::getline(stream, temp);
		data += temp;
	}

	return data.c_str();

}