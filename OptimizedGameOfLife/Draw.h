#pragma once
#include <SDL.h>

class Draw
{
public:
	SDL_Window* CreateWindow(unsigned int s_width, unsigned int s_height, unsigned int cellS);
	void DrawCell(unsigned int x, unsigned int y, unsigned int colour);
private:
	SDL_Window* window;
	SDL_Surface* surface;
	unsigned int screen_width, cell_size;
};

