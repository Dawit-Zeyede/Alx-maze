#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
} SDL_Instance;

typedef struct
{
    float rx, ry;
    int mx, my;
    int dof;
    float distance;
    int side;
} RayHit;

extern int map[mapX * mapY];
extern bool showMap;
extern bool walking;
extern float px, py, pdx, pdy, pa;
extern float headBob;
extern SDL_Texture* wallTexture;
extern SDL_Texture* groundTexture;
extern SDL_Texture* weaponTexture;
extern SDL_Texture* enemyTexture;
extern SDL_Rect mapViewport;
extern SDL_Rect viewport3D;

bool init(SDL_Instance *inst);
float degToRad(int a);
int FixAng(int a);
void drawMap2D(SDL_Renderer *renderer);
bool isWall(float x, float y);
bool parseMap(const char *mapFile);
void movePlayer(float dx, float dy);
void drawPlayer2D(SDL_Renderer *renderer);
void Buttons(SDL_Keycode key);
float distance(float ax, float ay, float bx, float by, float ang);
SDL_Texture *loadTexture(SDL_Instance *inst, const char *path, bool useColorkey);
void drawRays(SDL_Renderer *renderer);
void RayDistance(RayHit *hit, float rx, float ry, float xo, float yo, float ra);
RayHit VerticalIntersection(float ra);
RayHit HorizontalIntersection(float ra);
void WallTexture(SDL_Renderer* renderer, int r, int lineOff, int lineH, int wallslice, int side);
void drawWeaponAndEnemies(SDL_Renderer *renderer);
void drawbasics(SDL_Renderer *renderer);
void initi();
void close(SDL_Instance inst);

#endif
