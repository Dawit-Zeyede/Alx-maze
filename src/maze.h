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

/**
  * struct SDL_Instance - Holds the SDL window and renderer.
  * @window: pointer to the SDL window where rendering occurs.
  * @renderer: Pointert to the SDL renderer used to draw within the window.
  *
  * It is used to manage SDL window and renderer together.
  */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;
/**
  * struct RayHit - Structure to manage all of the ray character.
  * @rx: ray X
  * @ry: ray Y
  * @mx: grid pos X
  * @my: grid pos Y
  * @dof: try it 8 times as there is 8 grid.
  * @distance: Calculated distance.
  * @side: top/bottom or right/left
  *
  * This holds info about ther ray at a specific point.
  */
typedef struct RayHit
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
extern SDL_Texture *wallTex;
extern SDL_Texture *groundTex;
extern SDL_Texture *weaponTex;
extern SDL_Texture *enemyTex;
extern SDL_Rect mapView;
extern SDL_Rect view3D;

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
SDL_Texture *loadTexture(SDL_Instance *inst, const char *path, bool useCkey);
void drawRays(SDL_Renderer *renderer);
void RayDis(RayHit *hit, float rx, float ry, float xo, float yo, float ra);
RayHit VerticalIntersection(float ra);
RayHit HorizontalIntersection(float ra);
void Wtexture(SDL_Renderer *ren, int r, int LOff, int LiH, int Wsli, int side);
void drawWeaponAndEnemies(SDL_Renderer *renderer);
void drawbasics(SDL_Renderer *renderer);
void initi(void);
void close(SDL_Instance inst);

#endif
