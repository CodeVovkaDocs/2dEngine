#pragma once

#ifndef LOADER_H
#define LOADER_H



#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>


#include "Texture.h"
#include "Shader.h"
#include "CharInfo.h"


class Loader
{

public:

	static std::string ReadFile(const char* fileLocation);

	// LOAD GRAPHICS STUFF
	static void LoadShader(const char* vertexFileLocation, const char* fragmentFileLocation, const char* name);

	static void LoadTexture(const char* textureLoc, const char* textureName,texType format);

	static void LoadFontData(const char* fondDataLoc);

	// RETRIEVE GRAPHICS STUFF

	static Texture* GetTexture(std::string textureName);

	static Shader* GetShader(std::string shaderName);

	static std::map <char, charInfo> GetFontInfo();

	// LOAD GAME STUFF

	static const char* ReadLevelData(const char* fileLocation);

	
private:

	static std::map <char, charInfo> fontInfo;

	static std::map <std::string, Texture> textures;

	static std::map <std::string, Shader*> shaders;

	static int findIntInFontDataLine(std::string line, std::string var);

};


#endif 