#include "wolf3d.h"

int		av_verify_input(int argc, char **argv)
{
	if (argc != 2 && argv)
	{
		ft_printf("Usage:\n./wolf3d [map file location]\n");
		return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_state		*state;

	state = state_init();
	state->mlx = mlx_init();
	state->win = mlx_new_window(state->mlx,
		WINDOW_SIZE_X, WINDOW_SIZE_Y, "Wolf 3D");
	state->img = mlx_new_image(state->mlx, IMG_SIZE_X, IMG_SIZE_Y);
	state->img_addr = mlx_get_data_addr (state->img,
		&state->bits_per_pixel, &state->size_line, &state->endian);
	state->bytes_per_pixel = state->bits_per_pixel / 8;
	state->rgb = (t_rgb*)malloc(sizeof(t_rgb));
	state->map = av_get_map(argc, argv, state);
	map_set_start_location(state, state->map);
	state->player = player_init(state->start_x * STD_LEN,
															state->start_y * STD_LEN);
	ray_get_column_heights(state);
	img_draw_background(state);
	state->rgb->r = 190;
	state->rgb->g = 190;
	state->rgb->b = 190;
	ray_get_column_heights(state);
	state->player->view_angle = fmod(state->player->view_angle, 360);
	mlx_put_image_to_window (state->mlx, state->win, state->img,
													WIN_PAD_X, WIN_PAD_Y);
	mlx_hook(state->win, 2, 0, keyboard_input_handle, state);
	mlx_loop(state->mlx);
	return (1);
}
