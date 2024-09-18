#include "maze.h"
/**
  * Wtexture - render the wall.
  * @ren: rendering tool.
  * @r: rayIndex
  * @LOff: Y of wall slice
  * @LiH: X of wall slice
  * @Wsli: wall slice(width)
  * @side: for orientation.
  */

void Wtexture(SDL_Renderer *ren, int r, int LOff, int LiH, int Wsli, int side)
{
	if (side == 1) /* Orientation for vertical walls */
		SDL_SetTextureColorMod(wallTex, 255, 128, 128);
	else /* Oreintation for horizonatal walls */
		SDL_SetTextureColorMod(wallTex, 128, 128, 255);
	SDL_Rect wallSrc = {0, 0, mapS, mapS}; /* wall slice source */
	SDL_Rect wallDest = {r * Wsli, LOff, Wsli, LiH}; /* wall slice destination */

	if (SDL_HasIntersection(&mapView, &wallDest)) /* map and wall intersection */
	{
		int mapAreaBottom = mapView.y + mapView.h; /* Bottom for the map */
		int wallDestBottom = wallDest.y + wallDest.h; /* Upper for the map */

		if (wallDestBottom > mapAreaBottom) /* Adustment on point */
		{
			int offsetAdjustment = mapAreaBottom - wallDest.y; /* offset */

			wallDest.y += offsetAdjustment;
			wallDest.h -= offsetAdjustment;
		}
	}
	SDL_RenderCopy(ren, wallTex, &wallSrc, &wallDest); /* Draw wall slice */
}
/**
  * drawWeaponAndEnemies - weapon and enemy.
  * @renderer: rendering material.
  */
void drawWeaponAndEnemies(SDL_Renderer *renderer)
{
	/* Center of the screen for the weapon */
	int centerx = (screenWidth / 2);
	int centery = (screenHeight / 2) + 100;
	/* Apply headbob effect */
	SDL_Rect weaponRect = { centerx, centery + (int)(headBob * 5), 100, 100};

	SDL_RenderCopy(renderer, weaponTex, NULL, &weaponRect); /* Draw the weapon */
	SDL_Rect enemyRect = {600, 120 + (int)(headBob * 5), 80, 80};

	SDL_RenderCopy(renderer, enemyTex, NULL, &enemyRect);
}
/**
  * drawBasics - Ground and sky.
  * @renderer: rendering material.
  */
void drawBasics(SDL_Renderer *renderer)
{
	/* Set for sky color */
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	if (showMap) /* check for intersection */
	{
		/* set it so that no intersection */
		int c1X = mapX * mapS;
		int c2Y = mapY * mapS;
		int c1W = screenWidth - c1X;
		int c2H = screenHeight - c2Y;
		SDL_Rect ceiling1 = { c1X, 0, c1W, c2Y };
		SDL_Rect ceiling2 = {0, c2Y, screenWidth, c2H};

		mapView.h = c2Y;
		mapView.w = c1X;
		SDL_RenderFillRect(renderer, &ceiling1); /* Draw the upper sky */
		SDL_RenderFillRect(renderer, &ceiling2); /* Draw the lower sky */
	}
	else /* if no intersection, then one celing is enough */
	{
		SDL_Rect ceiling = {0, 0, screenWidth, screenHeight / 2};

		SDL_RenderFillRect(renderer, &ceiling);
		mapView.h = 0;
		mapView.w = 0;
	}
	/* Render the ground */
	SDL_Rect floor = {0, screenHeight / 2, screenWidth, screenHeight / 2 };

	SDL_RenderCopy(renderer, groundTex, NULL, &floor);
}
/**
 * drawRays - Draws rays and handles weapon and enemy rendering.
 * @renderer: SDL renderer for drawing.
 */
void drawRays(SDL_Renderer *renderer)
{
	drawBasics(renderer); /* Draw floor and ceiling */
	float vx, vy, r, rx, ry, ra, disV, disH;
	int side, wallslice = screenWidth / NumRays;

	ra = FixAng(pa + 30); /* Fix draw angle */
	for (r = 0; r < NumRays; r++) /* Iterate over each ray(60 */
	{
		/* Check for the first vertical and horizontal hit */
		RayHit vHit = VerticalIntersection(ra), hHit = HorizontalIntersection(ra);

		/* Calculate both vertical and borizontal distance */
		vx = vHit.rx, vy = vHit.ry, disV = vHit.distance;
		rx = hHit.rx, ry = hHit.ry, disH = hHit.distance, side = hHit.side;
		SDL_SetRenderDrawColor(renderer, 0, 204, 0, 255);
		if (disV < disH) /* check for first hit anoung Vert and Hort */
		{
			rx = vx, ry = vy, disH = disV; /* Vertical dist */
			SDL_SetRenderDrawColor(renderer, 0, 153, 0, 255);
			side = vHit.side; /* set side to 1 meanign vert */
		}
		if (showMap) /* Draw map */
			SDL_RenderDrawLine(renderer, (int)px, (int)py, (int)rx, (int)ry);
		int ca = FixAng(pa - ra);

		disH *= cos(degToRad(ca));
		int lineH = (mapS * (screenHeight - 85)) / disH;
		int lineOff = (screenHeight / 2) - (lineH >> 1) + (int)(headBob * 5);

		/* if lineH is high, then make it compatible */
		if (lineH > (screenHeight - 85))
			lineH = screenHeight;
		Wtexture(renderer, r, lineOff, lineH, wallslice, side);
		ra = FixAng(ra - 1);
	}
	drawWeaponAndEnemies(renderer); /* Draw weapin and Enemies */
}
