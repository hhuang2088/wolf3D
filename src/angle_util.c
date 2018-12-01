#include "wolf3d.h"

double	angle_degree_to_radian(double angle_degree)
{
	return (angle_degree * M_PI / 180.0);
}

double angle_radian_to_degree(double angle_radian)
{
	return (angle_radian * 180.0 / M_PI);
}
