#include "maze.h"
/**
  * degToRad - converts deg to Rad.
  * @a: current angle.
  * Return: degree in Rad.
  */
float degToRad(int a)
{
	float pa_Rad = a * M_PI / 180;
	return (pa_Rad);
}
/**
  * FixAng - fix angle less than 0 and greter than 360.
  * @a: current angle.
  * Return: Fixed angle.
  */
int FixAng(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}
/**
  * isWall - check the collison
  * @x: X cordinate
  * @y: Y coordinate
  * Return: true for heat.
  */
bool isWall(float x, float y)
{
	int mapXIndex = (int)(x) / mapS;
	int mapYIndex = (int)(y) / mapS;
	int mapIndex = mapYIndex * mapS + mapXIndex;

	if ((mapYIndex >= 0
				&& mapYIndex < mapY
				&& mapXIndex >= 0
				&& mapXIndex < mapX
				&& map[mapIndex]) == 1)
		return (true);
	return (false);
}
/**
  * Buttons - change the player posion and angle accordingly
  * @key: The key pressed
  */
void Buttons(SDL_Keycode key)
{
	float moveSpeed = 3.0f;

	if (key == SDLK_LEFT)
	{
		pa += 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == SDLK_RIGHT)
	{
		pa -= 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == SDLK_a)
		movePlayer(-pdy * moveSpeed, pdx * moveSpeed);
	if (key == SDLK_d)
		movePlayer(pdy * moveSpeed, -pdx * moveSpeed);
	if (key == SDLK_w)
	{
		movePlayer(pdx * moveSpeed, pdy * moveSpeed);
		headBob += 0.1f;
		walking = true;
	}
	if (key == SDLK_s)
	{
		movePlayer(-pdx * moveSpeed, -pdy * moveSpeed);
		headBob -= 0.1f;
		walking = true;
	}
	if (key == SDLK_m)
		showMap = !showMap;
	if (walking)
	{
		headBob = sin(headBob);
		walking = false;
	}
}
/**
  * distance - formual for the distance.
  * @ax: intial X
  * @ay: intial Y
  * @bx: final X
  * @by: final Y
  * @ang: current angle
  * Return: distance
  */

float distance(float ax, float ay, float bx, float by, float ang)
{
	float dis = (cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay));
	return (dis);
}
