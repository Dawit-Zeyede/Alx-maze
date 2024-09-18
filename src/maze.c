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

	if ((argc < 2)) /* Check for command line arguments */
	{
		if (!parseMap(DEFAULTMAP)) /* Use default map */
			return (1);
	}
	else if (!parseMap(argv[1])) /* Map file provided as argument */
		return (1);
	if (!(init(&inst))) /* Initilize SDL and create window */
		return (1);
	initi(); /* Initialize game settings */
	while (!quit) /* Main game loop */
	{
		while (SDL_PollEvent(&e) != 0) /* Process SDL events */
		{
			if (e.type == SDL_QUIT) /* Exit if quit event occurs */
				quit = true;
			if (e.type == SDL_KEYDOWN) /* Handle key press events */
				Buttons(e.key.keysym.sym);
		}
		SDL_SetRenderDrawColor(inst.renderer, 0, 0, 0, 255); /* Clear the renderer*/
		SDL_RenderClear(inst.renderer);
		if (showMap) /* Render the 2D map if showMap is true */
		{
			SDL_RenderSetViewport(inst.renderer, &mapView);
			drawMap2D(inst.renderer);
			drawPlayer2D(inst.renderer);
		}
		SDL_RenderSetViewport(inst.renderer, NULL); /* Reset to full screen */
		drawRays(inst.renderer); /* Draw rays */
		SDL_RenderPresent(inst.renderer); /* Present the renderer */
		SDL_Delay(16); /* Delay to control frame rate (60 FPS) */
	}
	close(inst); /* Clean up and close SDL resources */
	return (0); /* Success */
}
