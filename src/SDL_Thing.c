#include "maze.h"
/**
  * loadTexture - check for c Key.
  * @inst: SDL instance.
  * @path: path to the images.
  * @useCKey: need for Color Keying.
  * Return: SDL_Texture
  */
SDL_Texture *loadTexture(SDL_Instance *inst, const char *path, bool useCKey)
{
	int i = SDL_TRUE; /* Flag for enabling color keying */
	SDL_Texture *newTexture = NULL; /* Texture to be rendered */
	/* load window texture to Swindow */
	SDL_Surface *Swindow = SDL_GetWindowSurface(inst->window);
	SDL_Surface *lSur = IMG_Load(path); /* Loaded image surface */

	if (lSur == NULL) /* Check if the image surface was successfull */
	{
		printf("Unable to load image %s! SDL_Error: %s\n", path, SDL_GetError());
		return (NULL);
	}
	if (useCKey) /* Apply color keying if requested */
		SDL_SetColorKey(lSur, i, SDL_MapRGB(lSur->format, 124, 125, 125));
	/* Convert the loaded surface to the format of the window surface */
	SDL_Surface *opSur = SDL_ConvertSurface(lSur, Swindow->format, 0);

	if (opSur == NULL) /* check if conversion was successfull */
	{
		printf("Unable to optimize image %s! SDL_Error: %s\n", path, SDL_GetError());
		newTexture = SDL_CreateTextureFromSurface(inst->renderer, lSur);
	}
	else /* Apply color keying to the optimized surface */
	{
		if (useCKey)
		{
			SDL_SetColorKey(opSur, i, SDL_MapRGB(opSur->format, 255, 255, 255));
		}
		newTexture = SDL_CreateTextureFromSurface(inst->renderer, opSur);
	}
	if (newTexture == NULL) /* check if texture creation is successful */
	{
		printf("Err in create tex from %s! SDL_Error: %s\n", path, SDL_GetError());
	}
	/* Free the surface */
	SDL_FreeSurface(opSur);
	SDL_FreeSurface(lSur);
	return (newTexture);
}
