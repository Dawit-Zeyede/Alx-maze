#include "maze.h"
/**
  * parseMap - Extract the file and fill the map.
  * @mapFile: path the mapfile.
  * Return: true at success.
  */
bool parseMap(const char *mapFile)
{
	FILE *file = fopen(mapFile, "r");
	int x = 0;
	int y = 0;
	char ch;

	if (!file)
	{
		printf("Failed to open map file: %s\n", mapFile);
		return (false);
	}
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			y++;
			x = 0;
			if (y >= mapY)
				break;
		}
		else if (ch == '0' || ch == '1')
		{
			if (x < mapX)
			{
				map[y * mapX + x] = ch - '0';
				x++;
			}
		}
	}
	fclose(file);
	return (true);
}
