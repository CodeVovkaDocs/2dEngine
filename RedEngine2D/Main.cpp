
#include <stdio.h>
#include <string.h>


#include "MainWindow.h"
#include "Loader.h"
#include "Graphics.h"
#include "Game.h"
#include "Translator.h"
#include "Input.h"


//
//

int main()
{
	MainWindow window(640,480);
	window.init();


	Loader::LoadShader("Shaders/shader.vert", "Shaders/shader.frag", "sprite_shader");
	Loader::LoadShader("Shaders/textShader.vert", "Shaders/textShader.frag", "text_shader");
	Loader::LoadShader("Shaders/simpleShader.vert", "Shaders/simpleShader.frag", "simple_shader");
	Loader::LoadTexture("Textures/playerSheet.png","player",texType::IMAGE);
	Loader::LoadTexture("Textures/Wall1.png", "wall", texType::IMAGE);
	Loader::LoadTexture("Textures/Sky.png", "sky", texType::IMAGE);
	Loader::LoadTexture("Textures/Cursor.png", "cursor", texType::IMAGE);
	Loader::LoadTexture("Fonts/Font_0.png", "font", texType::FONT);
	Loader::LoadFontData("Fonts/Font.fnt");


	
	Game game;

	Graphics graphics;
	Input input;

	double prevTime = 0.0f;
	double currentTime = 0.0f;
	double dt = 0.0f;

	input.SetWindowRef(window.GetWindowPtr());
	graphics.Init(&window, Loader::GetShader("sprite_shader"),Loader::GetShader("text_shader"), Loader::GetShader("simple_shader"));

	game.LinkGraphics(&graphics);
	game.LinkInput(&input);
	game.Start();

	while (!window.GetShouldClose())
	{
		currentTime = glfwGetTime();
		dt = currentTime - prevTime;
		prevTime = currentTime;

		game.Update(dt);	

		game.Draw();

		window.PollEvents();
	
	}

	return 0;
}