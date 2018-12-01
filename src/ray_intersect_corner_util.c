#include "wolf3d.h"

void ray_intersect_nw_corner_handle(double x_new, double y_new,
																double *diff_x, double *diff_y, t_state *state)
{
	int	int_x;
	int	int_y;

	int_x = util_convert_to_int_coord(x_new, STD_LEN);
	int_y = util_convert_to_int_coord(y_new, STD_LEN);
	if (int_x - 1 >= 0)
	{
		if (state->map[int_y][int_x - 1] == '1')
			*diff_x += 64.0;
	}
	if (int_y - 1 >= 0)
	{
		if (state->map[int_y - 1][int_x] == '1')
			*diff_y += 64.0;
	}
}

void ray_intersect_ne_corner_handle(double x_new, double y_new,
																double *diff_x, double *diff_y, t_state *state)
{
	int	int_x;
	int	int_y;

	int_x = util_convert_to_int_coord(x_new, STD_LEN);
	int_y = util_convert_to_int_coord(y_new, STD_LEN);
	if (int_x + 1 < state->map_width)
	{
		if (state->map[int_y][int_x + 1] == '1')
			*diff_x += 64.0;
	}
	if (int_y - 1 >= 0)
	{
		if (state->map[int_y - 1][int_x] == '1')
			*diff_y += 64.0;
	}
}

void ray_intersect_sw_corner_handle(double x_new, double y_new,
																double *diff_x, double *diff_y, t_state *state)
{
	int	int_x;
	int	int_y;

	int_x = util_convert_to_int_coord(x_new, STD_LEN);
	int_y = util_convert_to_int_coord(y_new, STD_LEN);
	if (int_x - 1 >= 0)
	{
		if (state->map[int_y][int_x - 1] == '1')
			*diff_x += 64.0;
	}
	if (int_y + 1 < state->map_height)
	{
		if (state->map[int_y + 1][int_x] == '1')
			*diff_y += 64.0;
	}
}

void ray_intersect_se_corner_handle(double x_new, double y_new,
																double *diff_x, double *diff_y, t_state *state)
{
	int	int_x;
	int	int_y;

	int_x = util_convert_to_int_coord(x_new, STD_LEN);
	int_y = util_convert_to_int_coord(y_new, STD_LEN);
	if (int_x + 1 < state->map_width)
	{
		if (state->map[int_y][int_x + 1] == '1')
			*diff_x += 64.0;
	}
	if (int_y + 1 < state->map_height)
	{
		if (state->map[int_y + 1][int_x] == '1')
			*diff_y += 64.0;
	}
}
