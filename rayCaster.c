#include "maze.h"
/**
  * RayDistance - calculate and updates the distance and poistion.
  * @rx: position X
  * @ry: position Y
  * @xo: increment X
  * @yo: increment Y
  * @ra: current angle
  */
void RayDistance(RayHit *hit, float rx, float ry, float xo, float yo, float ra)
{
	int mp;

	while (hit->dof < 8)
	{
		hit->mx = (int)(rx) / mapS;
		hit->my = (int)(ry) / mapS;
		mp = hit->my * mapX + hit->mx;
		if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
		{
			hit->rx = rx;
			hit->ry = ry;
			hit->distance = distance(px, py, rx, ry, ra);
			hit->dof = 8;
		}
		else
		{
			rx += xo;
			ry += yo;
			hit->dof++;
		}
	}
}
/**
  * VerticalIntersection - Vertical intersection and distance from the player.
  * @ra: angle faced by the player.
  * Return: the whole info about the contact.
  */
RayHit VerticalIntersection(float ra)
{
	RayHit hit;
	float Tan = tan(degToRad(ra));
	float rx, ry, xo, yo;

	hit.dof = 0;
	hit.distance = 100000;
	hit.side = 1;
	if (cos(degToRad(ra)) > 0.001)
	{
		rx = (((int)px / mapS) * mapS) + mapS;
		ry = (px - rx) * Tan + py;
		xo = mapS;
		yo = -xo * Tan;
	}
	else if (cos(degToRad(ra)) < -0.001)
	{
		rx = (((int)px / mapS) * mapS) - 0.0001;
		ry = (px - rx) * Tan + py;
		xo = -mapS;
		yo = -xo * Tan;
	}
	else
	{
		rx = px;
		ry = py;
		hit.dof = 8;
		hit.rx = rx;
		hit.ry = ry;
		return (hit);
	}
	RayDistance(&hit, rx, ry, xo, yo, ra);
	return (hit);
}
/**
  * HorizontalIntersection - Vertical intersection and distance.
  * @ra: angle faced by the player.
  * Return: the whole info about the contact.
  */
RayHit HorizontalIntersection(float ra)
{
	RayHit hit;
	float rx, ry, xo, yo;
	float Tan = 1.0 / tan(degToRad(ra));

	hit.dof = 0;
	hit.distance = 100000;
	hit.side = 0;
	if (sin(degToRad(ra)) > 0.001)
	{
		ry = (((int)py / mapS) * mapS) - 0.0001;
		rx = (py - ry) * Tan + px;
		yo = -mapS;
		xo = -yo * Tan;
	}
	else if (sin(degToRad(ra)) < -0.001)
	{
		ry = (((int)py / mapS) * mapS) + mapS;
		rx = (py - ry) * Tan + px;
		yo = mapS;
		xo = -yo * Tan;
	}
	else
	{
		rx = px;
		ry = py;
		hit.dof = 8;
		hit.rx = rx;
		hit.ry = ry;
		return (hit);
	}
	RayDistance(&hit, rx, ry, xo, yo, ra);
	return (hit);
}
/**
  * WallTexture - render the wall.
  * @r: rayIndex
  * @lineOff: Y of wall slice
  * @lineH: X of wall slice
  * @side: for orientation.
  */

void WallTexture(SDL_Renderer *renderer, int r, int lineOff, int lineH, int wallslice, int side)
{
	if (side == 1)
		SDL_SetTextureColorMod(wallTexture, 255, 128, 128);
	else
		SDL_SetTextureColorMod(wallTexture, 128, 128, 255);
	SDL_Rect wallSrc = {0, 0, mapS, mapS};
	SDL_Rect wallDest = {r * wallslice, lineOff, wallslice, lineH};	
	if (SDL_HasIntersection(&mapViewport, &wallDest))
	{
		int mapAreaBottom = mapViewport.y + mapViewport.h;
		int wallDestBottom = wallDest.y + wallDest.h;

		if (wallDestBottom > mapAreaBottom)
		{
			int offsetAdjustment = mapAreaBottom - wallDest.y;
			
			wallDest.y += offsetAdjustment;
			wallDest.h -= offsetAdjustment;
		}
	}
	SDL_RenderCopy(renderer, wallTexture, &wallSrc, &wallDest);
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
	
	SDL_RenderCopy(renderer, weaponTexture, NULL, &weaponRect);
	/**
	SDL_Rect enemyRect = {600, 120 + (int)(headBob * 5), 80, 80};
	SDL_RenderCopy(renderer, enemyTexture, NULL, &enemyRect);
	*/
}

void drawBasics(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	if (showMap)
	{
		SDL_Rect ceiling1 = { mapX * mapS, 0, (screenWidth - mapX * mapS), mapX * mapS };
		SDL_Rect ceiling2 = {0, mapY * mapS, screenWidth, screenHeight - mapY * mapS};
		SDL_RenderFillRect(renderer, &ceiling1);
		SDL_RenderFillRect(renderer, &ceiling2);
		mapViewport.h = mapY * mapS;
		mapViewport.w = mapX * mapS;
	}
	else
	{
		SDL_Rect ceiling = {0, 0, screenWidth, screenHeight / 2};
		SDL_RenderFillRect(renderer, &ceiling);
		mapViewport.h = 0;
		mapViewport.w = 0;
	}
	SDL_Rect floor = {0, screenHeight / 2, screenWidth, screenHeight / 2 };
	SDL_RenderCopy(renderer, groundTexture, NULL, &floor);
}
/**
  * drawBasics - weapon and enemy.
  * @renderer: rendering material.
  */
void drawRays(SDL_Renderer* renderer)
{
	drawBasics(renderer);
	int side;
	float vx, vy, r, rx, ry, ra, disV, disH;
	int wallslice = screenWidth / NumRays;
	
	ra = FixAng(pa + 30);
	for (r = 0; r < NumRays; r++)
	{
		RayHit verticalHit = VerticalIntersection(ra);
		vx = verticalHit.rx;
		vy = verticalHit.ry;
		disV = verticalHit.distance;
		RayHit horizontalHit = HorizontalIntersection(ra);
		rx = horizontalHit.rx;
		ry = horizontalHit.ry;
		disH = horizontalHit.distance;
		side = horizontalHit.side;
		SDL_SetRenderDrawColor(renderer, 0, 204, 0, 255);
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disH = disV;
			SDL_SetRenderDrawColor(renderer, 0, 153, 0, 255);
			side = verticalHit.side;
		}
		if (showMap)
			SDL_RenderDrawLine(renderer, (int)px, (int)py, (int)rx, (int)ry);
		int ca = FixAng(pa - ra);
		
		disH = disH * cos(degToRad(ca));
		int lineH = (mapS * (screenHeight - 85)) / disH;
		int lineOff = (screenHeight / 2) - (lineH >> 1) + (int)(headBob * 5);
		if (lineH > (screenHeight - 85))
			lineH =screenHeight;
		renderWallTexture(renderer, r, lineOff, lineH, wallslice, side);
		ra = FixAng(ra - 1);
	}
	drawWeaponAndEnemies(renderer);
}
