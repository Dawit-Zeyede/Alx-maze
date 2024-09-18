#include "maze.h"
/**
  * parseMap - Extract the file and fill the map.
  * @mapFile: path the mapfile.
  * Return: true at success.
  */
bool parseMap(const char *mapFile)
{
	/* Open the map file for reading */
	FILE *file = fopen(mapFile, "r");
	int x = 0;
	int y = 0;
	char ch;

	if (!file)
	{
		/* Print an error message if the file cannot be opened */
		printf("Failed to open map file: %s\n", mapFile);
		return (false);
	}
	/* Read the file until the end of the file (EOF) */
	while ((ch = fgetc(file)) != EOF)
	{
		/* If a newline character is found, move to the next row */
		if (ch == '\n')
		{
			y++;
			x = 0;
			/* stop if the number of rows exceeds the mpa's height */
			if (y >= mapY)
				break;
		}
		/* If a valid character ('0' or '1') is found, fill the map */
		else if (ch == '0' || ch == '1')
		{
			/* Only fill if within the map's width */
			if (x < mapX)
			{
				/* Convert character to integer and store in teh map */
				map[y * mapX + x] = ch - '0';
				x++;
			}
		}
	}
	/* Close the file after reading */
	fclose(file);
	return (true);
}
