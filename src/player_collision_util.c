#include "wolf3d.h"

int				player_collide_with_wall(t_player *player, t_state *state, double angle_radian)
{
	double 	total_radius;
	double	angle_degree;
	double 	projected_x;
	double 	projected_y;
	double	v_len;
	double	h_len;

	total_radius = (player->focal_length + PLAYER_BUFFER_SPACE) *
									cos(angle_radian);
	angle_degree = angle_radian_to_degree(angle_radian);
	projected_x = player_get_movement_x_coord(player->position_x, angle_radian);
	projected_y = player_get_movement_y_coord(player->position_y, angle_radian);
	v_len = ray_check_vertical_intersection(angle_degree, state->map, player, state);
	h_len = ray_check_horizontal_intersection(angle_degree, state->map, player, state);
	if (h_len <= v_len)
	{
		if (h_len < total_radius)
			return (1);
	}
	else
	{
		if (v_len < total_radius)
			return (1)
	}
	return (0);
}
