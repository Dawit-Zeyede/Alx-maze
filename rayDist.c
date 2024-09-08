#include "maze.h"
/**
  * RayDist - calculate and updates the distance and poistion.
  * @rx: position X
  * @ry: position Y
  * @xo: increment X
  * @yo: increment Y
  * @ra: current angle
  */
void RayDist(RayHit *hit, float rx, float ry, float xo, float yo, float ra)
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
	RayDist(&hit, rx, ry, xo, yo, ra);
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
	RayDist(&hit, rx, ry, xo, yo, ra);
	return (hit);
}
