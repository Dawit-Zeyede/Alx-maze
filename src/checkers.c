#include "maze.h"
/**
  * degToRad - converts deg to Rad.
  * @a: current angle.
  * Return: degree in Rad.
  */
float degToRad(int a)
{
	/* Convert degrees to radians */
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
	/* Adjust angle if it exceeds 359 degrees */
	if (a > 359)
		a -= 360;
	/* Adjust angle if it is less than 0 degrees */
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
	/* Calculat map indices from coordinates */
	int mapXIndex = (int)(x) / mapS;
	int mapYIndex = (int)(y) / mapS;
	int mapIndex = mapYIndex * mapX + mapXIndex;

	/* check for map bound and if there is a wall */
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

	if (key == SDLK_LEFT) /* Rotate player left */
	{
		pa += 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == SDLK_RIGHT) /* Rotate player right */
	{
		pa -= 5;
		pa = FixAng(pa);
		pdx = cos(degToRad(pa));
		pdy = -sin(degToRad(pa));
	}
	if (key == SDLK_a) /* Move player left */
		movePlayer(-pdy * moveSpeed, pdx * moveSpeed);
	if (key == SDLK_d) /* Move player Right */
		movePlayer(pdy * moveSpeed, -pdx * moveSpeed);
	if (key == SDLK_w) /* Move player forward */
	{
		movePlayer(pdx * moveSpeed, pdy * moveSpeed);
		headBob += 0.1f;
		walking = true;
	}
	if (key == SDLK_s) /* Move player backward */
	{
		movePlayer(-pdx * moveSpeed, -pdy * moveSpeed);
		headBob -= 0.1f;
		walking = true;
	}
	if (key == SDLK_m) /* Toggle map visibility */
		showMap = !showMap;
	if (walking) /* Apply head bobing effect if walking */
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
	/* Calculate distance taking angle into account */
	float dis = (cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay));

	return (dis);
}
