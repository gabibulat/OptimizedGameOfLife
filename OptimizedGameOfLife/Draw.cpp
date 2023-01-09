#include "Draw.h"

SDL_Window* Draw::CreateWindow(unsigned int s_width, unsigned int s_height, unsigned int cellS)
{
	screen_width = s_width;
	cell_size = cellS;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, s_width, s_height, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	return window;
}

void Draw::DrawCell(unsigned int x, unsigned int y, unsigned int colour)
{

	Uint8* pixel_ptr = (Uint8*)surface->pixels + (y * cell_size * screen_width + (x * cell_size)) * 4;

	for (unsigned int i = 0; i < cell_size; i++)
	{
		for (unsigned int j = 0; j < cell_size; j++)
		{
			*(pixel_ptr + j * 4) = colour;
			*(pixel_ptr + j * 4 + 1) = colour;
			*(pixel_ptr + j * 4 + 2) = colour;
		}
		pixel_ptr += screen_width * 4;
	}
}
