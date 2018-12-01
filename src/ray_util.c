#include "wolf3d.h"

static double		ray_get_angle(double focal_length, int ray_x, int img_size_x)
{
	double	x_len;

	x_len = (double)ray_x - ((double)img_size_x / 2.0);
	return (atan2(focal_length, x_len));
}

static	void 		column_draw(t_state *state, int	height, int col)
{
	int		height_half;
	int		y_val;

	if (height <= IMG_SIZE_Y)
		height_half = height / 2;
	else
		height_half = IMG_SIZE_Y / 2;
	y_val = (IMG_SIZE_Y / 2) - height_half;
	while(y_val < (IMG_SIZE_Y / 2) + height_half)
		pixel_draw_single_byte(state, col, y_val++);
}

int		ray_get_column_heights(t_state *state)
{
	double	column_height;
	double	distance;
	int			i;
	double	angle;
	double	angle_displacement;
	double	angle_degree;
	double 	z;

	i = 0;
	while (i < IMG_SIZE_X)
	{
		angle = ray_get_angle(state->player->focal_length, i,
													IMG_SIZE_X);
		angle_displacement = angle_radian_to_degree(angle) - 90.0;
		angle_degree = angle_displacement + state->player->view_angle;
		if (angle_degree < 0)
			angle_degree = 360.0 + angle_degree;
		distance = ray_get_intersection(state->player,
																		state, state->map,
																		angle_degree);
		update_color_based_on_intersect_direction(state);
		z = distance * cos(angle - angle_degree_to_radian(90.0));
		column_height = round((STD_LEN / z * state->player->focal_length));
		column_draw(state, (int)column_height, i);
		++i;
	}
	return (1);
}
