#ifndef MAZE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define mapX 8
#define mapY 8
#define mapS 64

typedef struct SDL_Instance =
{
	SDL_Window *window;
	SDL_Renderer *renderer;
}SDL_Instance;

int map[] = 
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

float px = 20;
float py = 20;
float pdx;
float pdy;
SDL_Texture *wallTexture;
SDL_Texture *groundTexture;

SDL_Instance *init();
float degToRad(int a);
int FixAng(int a);
void drawMap2D(SDL_Renderer *renderer);
bool isWall(float x, float y);
void movePlayer(float dx, float dy);
void drawPlayer2D(SDL_Renderer *renderer);
void Buttons(SDL_Keycode key);
float distance(float ax, float ay, float bx, float by, float ang);
SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path);
void drawRays2D(SDL_Renderer *renderer);

#endif
