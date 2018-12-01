#include "wolf3d.h"

void 		img_clear_and_destroy(t_state *state)
{
	mlx_clear_window(state->mlx, state->win);
	mlx_destroy_image(state->mlx, state->img);
}

void img_draw_background(t_state *state)
{
	int		row;
	int		col;
	int		i;
	int		j;

	row = 0;
	i = IMG_SIZE_Y / 5;
	j = IMG_SIZE_X / 5;
	state->rgb->r = 140;
	state->rgb->g = 19;
	state->rgb->b = 172;
	while(row < IMG_SIZE_Y / 2)
	{
		col = 0;
		if (row % i == 0)
			state->rgb->r += 10;
		while (col < IMG_SIZE_X)
		{
			pixel_draw_single_byte(state, col, row);
			++col;
		}
		++row;
	}
	state->rgb->r = 0;
	state->rgb->g = 167;
	state->rgb->b = 200;
	while(row < IMG_SIZE_Y)
	{
		col = 0;
		if (row % j == 0)
			state->rgb->b += 5;
		while (col < IMG_SIZE_X)
		{
			pixel_draw_single_byte(state, col, row);
			++col;
		}
		++row;
	}
}

void 		img_update_and_display(t_state *state)
{
	state->img = mlx_new_image(state->mlx, IMG_SIZE_X, IMG_SIZE_Y);
	state->img_addr = mlx_get_data_addr (state->img,
		&state->bits_per_pixel, &state->size_line, &state->endian);
	state->bytes_per_pixel = state->bits_per_pixel / 8;
	img_draw_background(state);
	ray_get_column_heights(state);
	mlx_put_image_to_window (state->mlx, state->win, state->img,
													WIN_PAD_X, WIN_PAD_Y);
}

void 		update_color_based_on_intersect_direction(t_state *state)
{
	if (state->intersect_direction == 's')
	{
		//grey
		state->rgb->r = 190;
		state->rgb->g = 190;
		state->rgb->b = 190;
	}
	else if (state->intersect_direction == 'e')
	{
		//pink
		state->rgb->r = 255;
		state->rgb->g = 153;
		state->rgb->b = 153;
	}
	else if (state->intersect_direction == 'n')
	{
		//green
		state->rgb->r = 153;
		state->rgb->g = 255;
		state->rgb->b = 153;
	}
	else if (state->intersect_direction == 'w')
	{
		//blue
		state->rgb->r = 153;
		state->rgb->g = 153;
		state->rgb->b = 255;
	}
}
