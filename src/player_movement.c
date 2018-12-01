#include "wolf3d.h"

double		player_get_movement_x_coord(double pos_x, double angle_radian)
{
	return (pos_x + PLAYER_MOVEMENT_UNIT * cos(angle_radian));
}

double		player_get_movement_y_coord(double pos_y, double angle_radian)
{
	return (pos_y - PLAYER_MOVEMENT_UNIT * sin(angle_radian));
}

void 			player_move(double *pos_x, double *pos_y, double angle_degree)
{
	double	radian;

	radian = angle_degree_to_radian(angle_degree);
	*pos_x = *pos_x + PLAYER_MOVEMENT_UNIT * cos(radian);
	*pos_y = *pos_y - PLAYER_MOVEMENT_UNIT * sin(radian);
}

void 			player_strafe_left(double *pos_x, double *pos_y, double angle_degree)
{
double		angle_left;

angle_left = fmod(angle_degree + 90.0, 360.0);
player_move(pos_x, pos_y, angle_left);
}


void 			player_strafe_right(double *pos_x, double *pos_y, double angle_degree)
{
double		angle_right;

angle_right = fmod(angle_degree + 270.0, 360.0);
player_move(pos_x, pos_y, angle_right);
}


void 			player_move_forward(double *pos_x, double *pos_y, double angle_degree)
{
	player_move(pos_x, pos_y, angle_degree);
}

void 			player_move_back(double *pos_x, double *pos_y, double angle_degree)
{
	double		angle_behind;

	angle_behind = fmod(angle_degree + 180.0, 360.0);
	player_move(pos_x, pos_y, angle_behind);
}
