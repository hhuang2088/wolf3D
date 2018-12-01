#include "wolf3d.h"

double	player_convert_fov_to_radians(double field_of_view)
{
	return (((field_of_view / 2) * M_PI) / 180.0);
}

double	player_get_focal_length(int img_size_x)
{
	double	input_in_radians;

	input_in_radians = player_convert_fov_to_radians(PLAYER_FOV);
	return (((double)img_size_x / 2) / tan(input_in_radians));
}

double	player_get_angle_between_rays(int img_size_x)
{
	return (PLAYER_FOV / img_size_x);
}

t_player *player_init(double start_x, double start_y)
{
	t_player *player;

	player = (t_player*)malloc(sizeof(t_player));
	player->position_x = start_x;
	player->position_y = start_y;
	player->view_angle = ANGLE_ABSOLUTE_NORTH;
	player->focal_length = player_get_focal_length(IMG_SIZE_X);
	return (player);
}
