#pragma once
#include "CellMap.h"

// Limit loop rate for visibility
#define LIMIT_RATE 0
// Tick-rate in milliseconds (if LIMIT_RATE == 1)
#define TICK_RATE 50

// Grid Size 
unsigned int cellmap_width = 300;
unsigned int cellmap_height = 160;

// Cell Size in pixels
unsigned int cell_size = 5;

// Screen size
unsigned int s_width = cellmap_width * cell_size;
unsigned int s_height = cellmap_height * cell_size;



int main(int argc, char* argv[])
{
	CellMap current_map(cellmap_width, cellmap_height);
	current_map.Init();
	SDL_Window* window = current_map.draw.CreateWindow(s_width, s_height, cell_size);

	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0) { if (e.type == SDL_QUIT) quit = true; }

		current_map.NextGen();
		SDL_UpdateWindowSurface(window);

#if LIMIT_RATE
		SDL_Delay(TICK_RATE);
#endif
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

