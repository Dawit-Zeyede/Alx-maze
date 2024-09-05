#include "maze.h"

void drawPlayer2D(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_Rect rect = {(int)px - 4, (int)py - 4, 8, 8};
	SDL_RenderFillRect(renderer, &rect);
}
void drawMap2D(SDL_Renderer *renderer)
{
	int x, int y, int x0, int y0;

	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			int mapIndex = y * mapS + x;
			if (map[mapIndex] == 1)
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			x0 = x * mapS;
			y0 = y * mapS;
			SDL_Rect rect = { x0, y0, mapS - 2, mapS - 2 };
			SDK_RenderFillRect(renderer, &rect);
		}
	}
}
void Buttons(SDL_Keycode key)
{
	float moveSpeed = 5.0f;
	float rotSpeed = 5.0f;
	
	if (key == SDLK_a)
	{
		pa += 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == SDLK_d)
	{
		pa -= 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == SDLK_w)
		movePlayer(pdx * moveSpeed, pdy * moveSpeed);
	if (key == SDLK_s)
		movePlayer(pdx * moveSpeed, pdy * moveSpeed);
}
void movePlayer(float dx, float dy)
{
	float newX = px + dx;
	float newY = py + dy;

	if (!isWall(newX, py))
		px = newX;
	if (!isWall(px, newY))
		py = newY;
}
