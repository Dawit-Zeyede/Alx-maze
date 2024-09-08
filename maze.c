#include "maze.h"
/**
  * main - Entry point to the program.
  * @argc: Name of the program and map file
  * @argv: [program, map]
  * Return: 0 on sucess and 1 on failure.
  */
int main(int argc, char *argv[])
{
	SDL_Instance inst;
	SDL_Event e;
	bool quit = false;

	if ((argc < 2))
	{
		if (!parseMap(DEFAULTMAP))
			return (1);
	}
	else
	{
		if (!parseMap(argv[1]))
			return (1);
	}
	if (!(init(&inst)))
		return (1);
	initi();
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN)
				Buttons(e.key.keysym.sym);
		}
		SDL_SetRenderDrawColor(inst.renderer, 0, 0, 0, 255);
		SDL_RenderClear(inst.renderer);
		if (showMap)
		{
			SDL_RenderSetViewport(inst.renderer, &mapView);
			drawMap2D(inst.renderer);
			drawPlayer2D(inst.renderer);
		}
		SDL_RenderSetViewport(inst.renderer, NULL);
		drawRays(inst.renderer);
		SDL_RenderPresent(inst.renderer);
		SDL_Delay(16);
	}
	close(inst);
	return (0);

