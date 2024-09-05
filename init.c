#include "maze.h"
/**
  * init - initilize the SDL2 and creates win and renderer.
  * @inst: SDL_Instance constisting of both win and renderer.
  * Return: true with success.
  */
bool init(SDL_Insance *inst)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (false);
	}
	inst->window = SDL_CreateWindow("SDL2 Raycaster",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (!(inst->window))
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (false);
	}
	inst->renderer = SDL_CreateRenderer(inst->window,
			-1, SDL_RENDERER_ACCELERATED);
	if (!(inst->renderer))
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(inst->window);
		SDL_Quit();
		return (false);
	}
	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image Error: %s\n", IMG_GetError());
		return (false);
	}
	wallTexture = loadTexture(inst, "download.jpg", false);
	weaponTexture = loadTexture(inst, "weapon_texture2.jpg", true);
	groundTexture = loadTexture(inst, "ground_texture.bmp", false);
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));
	return (success);
}
