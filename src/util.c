#include "wolf3d.h"

int		util_convert_to_int_coord(double std_coord, double std_len)
{
	int		ret;

	ret = (int)(std_coord / std_len);
	return (ret);
}

double		util_convert_to_std_len(int int_len, double std_len)
{
	double	ret;

	ret = (double)int_len * std_len;
	return (ret);
}
