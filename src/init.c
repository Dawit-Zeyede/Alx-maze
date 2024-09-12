#include "maze.h"

SDL_Rect view3D;
SDL_Rect mapView;
SDL_Texture *enemyTex = NULL;
SDL_Texture *weaponTex = NULL;
SDL_Texture *groundTex = NULL;
SDL_Texture *wallTex = NULL;
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
	wallTex = loadTexture(inst, "images/download.jpg", false);
	weaponTex = loadTexture(inst, "images/weapon_texture2.jpg", true);
	groundTex = loadTexture(inst, "images/ground_texture.bmp", false);
	return (success);
}
/**
  * initi - intilizer.
  */
void initi(void)
{
	px = 20;
	py = 20;
	pa = -45;
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));
	headBob = 0;
	showMap = true;
	walking = false;
	mapView.x = 0;
	mapView.y = 0;
	mapView.w = mapX * mapS;
	mapView.h = mapY * mapS;

	view3D.x = mapX * mapS;
	view3D.y = 0;
	view3D.w = screenWidth - mapX * mapS;
	view3D.h = screenHeight;
}
