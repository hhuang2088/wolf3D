#include "wolf3d.h"

void 	map_set_start_location(t_state *state, char **map)
{
	int		x;
	int		y;

	y = 0;
	while (y < state->map_height)
	{
		x = 0;
		while (x < state->map_width)
		{
			if (map[y][x] == '2')
			{
				state->start_x = x;
				state->start_y = y;
				return;
			}
			++x;
		}
		++y;
	}
}
