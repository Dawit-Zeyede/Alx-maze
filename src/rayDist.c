#include "maze.h"
/**
  * RayDist - calculate and updates the distance and poistion.
  * @hit: Data type for ray info.
  * @rx: position X
  * @ry: position Y
  * @xo: increment X
  * @yo: increment Y
  * @ra: current angle
  */
void RayDist(RayHit *hit, float rx, float ry, float xo, float yo, float ra)
{
	int mp;

	/* Iterate to find the intersection point or exit if maximum iteration */
	while (hit->dof < 8)
	{
		hit->mx = (int)(rx) / mapS; /* Calcualate map coordinates */
		hit->my = (int)(ry) / mapS;
		mp = hit->my * mapX + hit->mx;
		/* Check if the ray has wall */
		if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
		{
			hit->rx = rx;
			hit->ry = ry;
			hit->distance = distance(px, py, rx, ry, ra);
			hit->dof = 8; /* Set to 8 to exit the loop */
		}
		else
		{
			/* update ray position for next iteration */
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
	/* Initialize with a large distance(So that the wall is small). */
	hit.distance = 100000;
	hit.side = 1; /* Vertical side hit */
	if (cos(degToRad(ra)) > 0.001) /* Right side */
	{
		/* Calculat initial ray posiion and incremens */
		rx = (((int)px / mapS) * mapS) + mapS;
		ry = (px - rx) * Tan + py;
		xo = mapS;
		yo = -xo * Tan;
	}
	else if (cos(degToRad(ra)) < -0.001) /* Left side */
	{
		/* Calcuate initail ray posions and decremtents */
		rx = (((int)px / mapS) * mapS) - 0.0001;
		ry = (px - rx) * Tan + py;
		xo = -mapS;
		yo = -xo * Tan;
	}
	else /* Parrallel to vertiacal lines */
	{
		rx = px;
		ry = py;
		hit.dof = 8;
		hit.rx = rx;
		hit.ry = ry;
		return (hit);
	}
	/* Calculate distance to intersection point */
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
	if (sin(degToRad(ra)) > 0.001) /* Upper side */
	{
		ry = (((int)py / mapS) * mapS) - 0.0001;
		rx = (py - ry) * Tan + px;
		yo = -mapS;
		xo = -yo * Tan;
	}
	else if (sin(degToRad(ra)) < -0.001) /* Left side */
	{
		ry = (((int)py / mapS) * mapS) + mapS;
		rx = (py - ry) * Tan + px;
		yo = mapS;
		xo = -yo * Tan;
	}
	else /* Parrallel ot the horizontal lines */
	{
		rx = px;
		ry = py;
		hit.dof = 8;
		hit.rx = rx;
		hit.ry = ry;
		return (hit);
	}
	/* Calculate distance to intersection point. */
	RayDist(&hit, rx, ry, xo, yo, ra);
	return (hit);
}
