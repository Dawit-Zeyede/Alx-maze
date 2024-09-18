#include "maze.h"
/**
  * drawPlayer2D - draws player as a specific rectagle.
  * @renderer: drawing material.
  */
void drawPlayer2D(SDL_Renderer *renderer)
{
	/* Define the rectangle representing the player */
	SDL_Rect rect = {(int)px - 2, (int)py - 2, 4, 4};

	/* Set the color for the player rectangle(yellow) */
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect); /* Render the player rectangle */
}
/**
  * drawMap2D - draws the map.
  * @renderer: drawing material.
  */
void drawMap2D(SDL_Renderer *renderer)
{
	int x, y, x0, y0;

	/* Loop through each cell of the map */
	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			int mapIndex = y * mapX + x; /* Index in a map */

			if (map[mapIndex] == 1) /* Set color based on map value */
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); /* White for walls */
			else
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /* Black for empty */
			/* Calculate position and size of the cell rectangle */
			x0 = x * mapS;
			y0 = y * mapS;
			SDL_Rect rect = { x0, y0, mapS - 2, mapS - 2 };

			SDL_RenderFillRect(renderer, &rect); /* Render the rect */
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

	/* Check for collisions in the x direction */
	if (!isWall(newX, py))
		px = newX;
	/* Check for collisions in the y direction */
	if (!isWall(px, newY))
		py = newY;
}
