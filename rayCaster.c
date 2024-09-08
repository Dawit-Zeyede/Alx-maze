#include "maze.h"
/**
  * Wtexture - render the wall.
  * @r: rayIndex
  * @LOff: Y of wall slice
  * @LiH: X of wall slice
  * @Wsli: wall slice(width)
  * @side: for orientation.
  */

void Wtexture(SDL_Renderer *ren, int r, int LOff, int LiH, int Wsli, int side)
{
	if (side == 1)
		SDL_SetTextureColorMod(wallTex, 255, 128, 128);
	else
		SDL_SetTextureColorMod(wallTex, 128, 128, 255);
	SDL_Rect wallSrc = {0, 0, mapS, mapS};
	SDL_Rect wallDest = {r * Wsli, LOff, Wsli, LiH};

	if (SDL_HasIntersection(&mapView, &wallDest))
	{
		int mapAreaBottom = mapView.y + mapView.h;
		int wallDestBottom = wallDest.y + wallDest.h;

		if (wallDestBottom > mapAreaBottom)
		{
			int offsetAdjustment = mapAreaBottom - wallDest.y;

			wallDest.y += offsetAdjustment;
			wallDest.h -= offsetAdjustment;
		}
	}
	SDL_RenderCopy(ren, wallTex, &wallSrc, &wallDest);
}
/**
  * drawWeaponAndEnemies - weapon and enemy.
  * @renderer: rendering material.
  */
void drawWeaponAndEnemies(SDL_Renderer *renderer)
{
	int centerx = (screenWidth / 2);
	int centery = (screenHeight / 2) + 100;
	SDL_Rect weaponRect = { centerx, centery + (int)(headBob * 5), 100, 100};

	SDL_RenderCopy(renderer, weaponTex, NULL, &weaponRect);
	SDL_Rect enemyRect = {600, 120 + (int)(headBob * 5), 80, 80};

	SDL_RenderCopy(renderer, enemyTex, NULL, &enemyRect);
}
/**
  * drawBasics - weapon and enemy.
  * @renderer: rendering material.
  */
void drawBasics(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	if (showMap)
	{
		int c1X = mapX * mapS;
		int c2Y = mapY * mapS;
		int c1W = screenWidth - c1X;
		int c2H = screenHeight - C2Y;
		SDL_Rect ceiling1 = { c1X, 0, c1W, c1Y };
		SDL_Rect ceiling2 = {0, c2Y, screenWidth, c2H};

		mapView.h = c2Y;
		mapView.w = c1X;
		SDL_RenderFillRect(renderer, &ceiling1);
		SDL_RenderFillRect(renderer, &ceiling2);
	}
	else
	{
		SDL_Rect ceiling = {0, 0, screenWidth, screenHeight / 2};

		SDL_RenderFillRect(renderer, &ceiling);
		mapView.h = 0;
		mapView.w = 0;
	}
	SDL_Rect floor = {0, screenHeight / 2, screenWidth, screenHeight / 2 };

	SDL_RenderCopy(renderer, groundTex, NULL, &floor);
}
/**
 * drawRays - Draws rays and handles weapon and enemy rendering.
 * @renderer: SDL renderer for drawing.
 */
void drawRays(SDL_Renderer *renderer)
{
	drawBasics(renderer);
	float vx, vy, r, rx, ry, ra, disV, disH;
	int side, wallslice = screenWidth / NumRays;
	ra = FixAng(pa + 30);

	for (r = 0; r < NumRays; r++)
	{
		RayHit vHit = VerticalIntersection(ra), hHit = HorizontalIntersection(ra);
		vx = vHit.rx, vy = vHit.ry, disV = vHit.distance;
		rx = hHit.rx, ry = hHit.ry, disH = hHit.distance, side = hHit.side;
		SDL_SetRenderDrawColor(renderer, 0, 204, 0, 255);
		if (disV < disH)
		{
			rx = vx, ry = vy, disH = disV;
			SDL_SetRenderDrawColor(renderer, 0, 153, 0, 255);
			side = vHit.side;
		}
		if (showMap)
			SDL_RenderDrawLine(renderer, (int)px, (int)py, (int)rx, (int)ry);
		int ca = FixAng(pa - ra), lineH = (mapS * (screenHeight - 85)) / disH;
		disH *= cos(degToRad(ca));
		int lineOff = (screenHeight / 2) - (lineH >> 1) + (int)(headBob * 5);

		if (lineH > (screenHeight - 85))
			lineH = screenHeight;
		Wtexture(renderer, r, lineOff, lineH, wallslice, side);
		ra = FixAng(ra - 1);
	}
	drawWeaponAndEnemies(renderer);
}
