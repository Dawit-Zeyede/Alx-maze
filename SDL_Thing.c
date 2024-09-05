#include "maze.h"

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path)
{
	SDL_Surface *loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
		return (NULL);
	}

	SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL_Error: %s\n", path, SDL_GetError());
		return (NULL);
	}

	return (newTexture);
}
SDL_Instance *init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return (NULL);
	}

	SDL_Instance *instance;
	instance->window = SDL_CreateWindow("THE MAZE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CETERED, 1024, 512, SDL_WINDOW_SHOWN);
	if (!(instance->window))
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (NULL);
	}

	instance->renderer = SDL_CreateRenderer(instance->window, -1, SDL_RENDERER_ACCELERATED);
	if (!(instance->renderer))
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(instance->window);
		SDL_Quit();
		return (NULL);
	}

	px = 200;
	py = 150;
	pa = 0;
	pdx = cos(degToRad(pa));
	pdy = -sin(defToRad(pa));
	return (instance);
}
