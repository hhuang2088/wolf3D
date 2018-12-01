#include "wolf3d.h"

static	void 		ray_intersect_corner_handle(double x_new, double y_new,
																						double *diff_x, double *diff_y,
																						int corner, t_state *state)
{
	if (corner == 1)
		ray_intersect_nw_corner_handle(x_new, y_new, diff_x, diff_y, state);
	else if (corner == 2)
		ray_intersect_ne_corner_handle(x_new, y_new, diff_x, diff_y, state);
	else if (corner == 3)
		ray_intersect_sw_corner_handle(x_new, y_new, diff_x, diff_y, state);
	else
		ray_intersect_se_corner_handle(x_new, y_new, diff_x, diff_y, state);
}

static	int			ray_get_intersect_corner(int north, int west)
{
	if (north && west) // upper-left
		return (1);
	else if (north && !west) // upper-right
		return (2);
	else if (!north && west) // lower-left
		return (3);
	return (4); // lower-right;
}

static	char 		ray_determine_intersect_direction(double y_new, double x_new,
																									double angle_degree, t_state *state)
{
	double 	base_x;
	double 	base_y;
	double	round_x;
	double	round_y;
	double	diff_x;
	double	diff_y;
	int			north;
	int			west;
	int			corner;
	char		ret;

	north = 0;
	west = 0;
	base_x = floor(x_new / STD_LEN) * STD_LEN;
	base_y = floor(y_new / STD_LEN) * STD_LEN;
	round_x = round(x_new / STD_LEN) * STD_LEN;
	round_y = round(y_new / STD_LEN) * STD_LEN;
	if (base_x == round_x)
		west = 1;
	if (base_y == round_y)
		north = 1;
	corner = ray_get_intersect_corner(north, west);
	if (north)
		diff_y = y_new - base_y;
	else
		diff_y = round_y - y_new;
	if (west)
		diff_x = x_new - base_x;
	else
		diff_x = round_x - x_new;
	if (diff_x <= 0.15 && diff_y <= 0.15)
		ray_intersect_corner_handle(x_new, y_new, &diff_x, &diff_y, corner, state);
	if (angle_degree == 0.0 || angle_degree == 180.0)
		diff_y = DBL_MAX;
	if (angle_degree == 90.0 || angle_degree == 270.0)
		diff_x = DBL_MAX;
	if (diff_x > diff_y && north)
		ret = 'n';
	else if (diff_x > diff_y && !north)
		ret = 's';
	else if (diff_x < diff_y && west)
		ret = 'w';
	else
		ret = 'e';
	return (ret);
}

static	void 		ray_keep_coords_within_bounds(double *x_new, double *y_new, t_state *state)
{
	double	tmp;

	if ((int)(*y_new / STD_LEN) >= state->map_height)
	{
		tmp = (double)(state->map_height - 0.01) * STD_LEN;
		*y_new = tmp;
	}
	else if ((int)(*y_new / STD_LEN) <= 0)
		*y_new = STD_LEN - 0.01;
	if ((int)(*x_new / STD_LEN) >= state->map_width)
	{
		tmp = (double)(state->map_width - 0.01) * STD_LEN;
		*x_new = tmp;
	}
	else if ((int)(*x_new / STD_LEN) <= 0)
		*x_new = STD_LEN - 0.01;
}

static	int			ray_is_negative_x(double angle_degree)
{
	if (angle_degree > 90.0 && angle_degree < 270.0)
		return (1);
	return (0);
}

static int			ray_is_negative_y(double angle_degree)
{
	if (angle_degree > 180 && angle_degree < 360)
		return (1);
	return (0);
}

static double			ray_get_x_displacement(double angle_degree)
{
	double		x_displacement;
	double		angle_normal;
	double		radian;

	angle_normal = fmod(angle_degree, 360.0);
	radian = (angle_normal * M_PI) / 180.0;
	x_displacement = STD_LEN / tan(radian);
	if (ray_is_negative_y(angle_degree))
		x_displacement = -x_displacement;
	return (x_displacement);
}

static double			ray_get_y_displacement(double angle_degree)
{
	double		y_displacement;
	double		angle_normal;
	double		radian;

	angle_normal = fmod(angle_degree, 360.0);
	radian = (angle_normal * M_PI) / 180.0;
	y_displacement = -STD_LEN * (tan(radian));
	if (ray_is_negative_x(angle_degree))
		y_displacement = -y_displacement;
	return (y_displacement);
}

static double		ray_get_distance_to_wall(double position_x, double position_y,
																											double x_new, double y_new, double angle)
{
	double result;
	double radian;

	radian = (angle * M_PI / 180.0);
	if (angle == 0.0 || angle == 180.0)
		result = sqrt(pow(position_x - x_new, 2) + pow(position_y - y_new, 2));
	else
		result = fabs((position_y - y_new) / sin(radian));
	return (result);
}

double		ray_check_horizontal_intersection(double angle_degree, char **map, t_player *player, t_state *state)
{
	double	x_displacement;
	double	y_displacement;
	double	x_new;
	double 	y_new;
	double	distance;

	x_displacement = ray_get_x_displacement(angle_degree);
	y_displacement = (ray_is_negative_y(angle_degree)) ? STD_LEN : -STD_LEN;
	y_new = (ray_is_negative_y(angle_degree)) ?
											floor(player->position_y / STD_LEN) * STD_LEN + STD_LEN :
											floor(player->position_y / STD_LEN) * STD_LEN - 0.00001;
	x_new = player->position_x + (player->position_y - y_new) / tan(angle_degree * M_PI / 180.0);
	ray_keep_coords_within_bounds(&x_new, &y_new, state);
	while (map[(int)(y_new / STD_LEN)][(int)(x_new / STD_LEN)] != '1')
	{
		y_new += y_displacement;
		x_new += x_displacement;
		ray_keep_coords_within_bounds(&x_new, &y_new, state);
	/*
		if (map[(int)(y_new / STD_LEN)][(int)(x_new / STD_LEN)] != '1')
			map[(int)(y_new / STD_LEN)][(int)(x_new / STD_LEN)] = 'h';
	*/
//		ft_printf("Horizontal intersection: %d, %d\n", (int)(x_new / STD_LEN), (int)(y_new / STD_LEN));
	}
	// looking at trajectory
	/*
	i = 0;
	ft_printf("   01234567890\n");
	while (i < state->map_height)
	{
		ft_printf("%d: %s %d\n", i, map[i], i);
		++i;
	}
	ft_printf("   01234567890\n");
	*/
	// end of looking at trajectory
	distance = ray_get_distance_to_wall(player->position_x, player->position_y, x_new, y_new, angle_degree);
	state->h_intersect_direction = ray_determine_intersect_direction(y_new, x_new, angle_degree, state);
	return (distance);
}

double		ray_check_vertical_intersection(double angle_degree, char **map, t_player *player, t_state *state)
{
	double	x_displacement;
	double	y_displacement;
	double	x_new;
	double 	y_new;
	double	distance;

	if (angle_degree != 180.0 && angle_degree != 0.0)
		y_displacement = ray_get_y_displacement(angle_degree);
	else
		y_displacement = 0;
	x_displacement = (ray_is_negative_x(angle_degree)) ? -STD_LEN : STD_LEN;
	x_new = (ray_is_negative_x(angle_degree)) ?
												floor(player->position_x / STD_LEN) * STD_LEN - 0.00001:
												floor(player->position_x / STD_LEN) * STD_LEN + STD_LEN;
	y_new = player->position_y + (player->position_x - x_new) * tan((angle_degree * M_PI) / 180.0);
	ray_keep_coords_within_bounds(&x_new, &y_new, state);
	while (map[(int)(y_new / STD_LEN)][(int)(x_new / STD_LEN)] != '1')
	{
		y_new += y_displacement;
		x_new += x_displacement;
		ray_keep_coords_within_bounds(&x_new, &y_new, state);
//		ft_printf("Vertical intersection: %d, %d\n", (int)(x_new / STD_LEN), (int)(y_new / STD_LEN));
		/*
		if (map[(int)(y_new / STD_LEN)][(int)(x_new / STD_LEN)] != '1')
			map[(int)(y_new / STD_LEN)][(int)(x_new / STD_LEN)] = 'v';
		*/
	}
	// looking at trajectory
	/*
	i = 0;
	ft_printf("   01234567890\n");
	while (i < state->map_height)
	{
		ft_printf("%d: %s %d\n", i, map[i], i);
		++i;
	}
	ft_printf("   01234567890\n");
	*/
	// end of looking at trajectory
	distance = ray_get_distance_to_wall(player->position_x, player->position_y,
																			x_new, y_new, angle_degree);
	state->v_intersect_direction = ray_determine_intersect_direction(y_new, x_new, angle_degree, state);
	return (distance);
}

double		ray_get_intersection(t_player *player, t_state *state, char **map,
															double angle_degree)
{
	double			h_len;
	double			v_len;

	if (angle_degree != 0 && angle_degree != 180)
		h_len = ray_check_horizontal_intersection(angle_degree, map, player, state);
	else
		h_len = DBL_MAX;
	if (angle_degree != 90 && angle_degree != 270)
		v_len = ray_check_vertical_intersection(angle_degree, map, player, state);
	else
		v_len = DBL_MAX;
	if (h_len <= v_len)
	{
		state->intersect_direction = state->h_intersect_direction;
		return (h_len);
	}
	else
		state->intersect_direction = state->v_intersect_direction;
	return (v_len);
}
