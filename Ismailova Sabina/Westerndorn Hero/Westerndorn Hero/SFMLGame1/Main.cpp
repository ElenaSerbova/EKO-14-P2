#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif 

#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

int main()
{
	Game game;
	game.StartScreen();	
	return 1;
}

