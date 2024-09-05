#include "maze.h"

// Definitions
SDL_Rect viewport3D;
SDL_Rect mapViewport;
SDL_Texture* enemyTexture = NULL;
SDL_Texture* weaponTexture = NULL;
SDL_Texture* groundTexture = NULL;
SDL_Texture* wallTexture = NULL;
float headBob = 0;
float px = 0, py = 0, pdx = 0, pdy = 0, pa = 0;
bool walking = false;
bool showMap = true;
int map[mapX * mapY];


/**
  * init - initilize the SDL2 and creates win and renderer.
  * @inst: SDL_Instance constisting of both win and renderer.
  * Return: true with success.
  */
bool init(SDL_Instance *inst)
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
void initi()
{


	px = 20;
	py = 20;
	pa = -45;
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));
	showMap = true;
	walking = false;
	mapViewport.x = 0;
	mapViewport.y = 0;
	mapViewport.w = mapX * mapS;
	mapViewport.h = mapY * mapS;

	viewport3D.x = mapX * mapS;
	viewport3D.y = 0;
	viewport3D.w = screenWidth - mapX * mapS;
	viewport3D.h = screenHeight;
}
