#include "maze.h"

SDL_Texture* loadTexture(SDL_Insance* inst, const char* path, bool useColorKey)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface* Swindow = SDL_GetWindowSurface(inst->window);
	SDL_Surface* loadedSurface = IMG_Load(path);
	
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
		return NULL;
	}
	if (useColorKey)
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 124, 125, 125));
	SDL_Surface *optimizedSurface = SDL_ConvertSurface(loadedSurface, Swindow->format, 0);
	if (optimizedSurface == NULL)
	{
		printf("Unable to optimize image %s! SDL_Error: %s\n", path, SDL_GetError());
		newTexture = SDL_CreateTextureFromSurface(inst->renderer, loadedSurface);
	}
	else
	{
		if (useColorKey)
		{
			SDL_SetColorKey(optimizedSurface, SDL_TRUE, SDL_MapRGB(optimizedSurface->format, 255, 255, 255));
		}
		newTexture = SDL_CreateTextureFromSurface(inst->renderer, optimizedSurface);
	}
	if (newTexture == NULL)
	{
		printf("Unable to create texture from %s! SDL_Error: %s\n", path, SDL_GetError());
	}
	SDL_FreeSurface(optimizedSurface);
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}
