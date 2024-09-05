#include "maze.h"
/**
  * drawPlayer2D - draws player as a specific rectagle.
  * @renderer: drawing material.
  */
void drawPlayer2D(SDL_Renderer *renderer)
{
	SDL_Rect rect = {(int)px - 2, (int)py - 2, 4, 4};

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}
/**
  * drawMap2D - draws the map.
  * @renderer: drawing material.
  */
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
/**
  * movePlayer - moves  the player with dx and check for collision.
  * @dx: moving dimension in x.
  * @dy: moving dimension in y.
  */
void movePlayer(float dx, float dy)
{
	float newX = px + dx;
	float newY = py + dy;

	if (!isWall(newX, py))
		px = newX;
	if (!isWall(px, newY))
		py = newY;
}
