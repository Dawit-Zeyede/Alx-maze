#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define mapX  8
#define mapY  8
#define mapS 16
#define NumRays 60
#define screenWidth 1024
#define screenHeight 512
#define DEFAULTMAP "default_map.txt"


typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Insance;

typedef struct
{
    float rx, ry;
    int mx, my;
    int dof;
    float distance;
    int side;
} RayHit;

int map[mapX * mapY];
bool showMap = true;
bool walking = false;
float px, py, pdx, pdy, pa;
float headBob = 0;
SDL_Texture* wallTexture;
SDL_Texture* groundTexture;
SDL_Texture* weaponTexture;
SDL_Texture* enemyTexture;
SDL_Rect mapViewport = {0, 0, mapX * mapS, mapY * mapS};
SDL_Rect viewport3D = { mapX * mapS, 0, screenWidth - mapX * mapS, screenHeight };

SDL_Instance *init();
float degToRad(int a);
int FixAng(int a);
void drawMap2D(SDL_Renderer *renderer);
bool isWall(float x, float y);
bool parseMap(cost char *mapFile);
void movePlayer(float dx, float dy);
void drawPlayer2D(SDL_Renderer *renderer);
void Buttons(SDL_Keycode key);
float distance(float ax, float ay, float bx, float by, float ang);
SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path, bool useColorkey);
void drawRays(SDL_Renderer *renderer);
void RayDistance(RayHit *hit, float rx, float ry, float xo, float yo, float ra);
RayHit VerticalIntersection(float ra);
RayHit HorizontalIntersection(float ra);
void WallTexture(SDL_Renderer* renderer, int r, int lineOff, int lineH, int wallslice, int side);
void drawWeaponAndEnemies(SDL_Renderer *renderer);
void drawbasics(SDL_Renderer *renderer);
void close(SDL_Insance inst);

#endif
