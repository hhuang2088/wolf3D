#include "wolf3d.h"

t_state		*state_init(void)
{
	t_state		*ret;

	if (!(ret = (t_state*)malloc(sizeof(t_state))))
		return (0);
	ret->mlx = NULL;
	ret->img = NULL;
	ret->img_addr = NULL;
	ret->map = NULL;
	ret->pixel_map = NULL;
	ret->map_width = 0;
	ret->map_height = 0;
	ret->std_cell_len = 0;
	ret->endian = 0;
	ret->size_line = 0;
	ret->bytes_per_pixel = 0;
	ret->player = NULL;
	ret->start_x = 0;
	ret->start_y = 0;
	ret->rgb = NULL;
	ret->h_intersect_direction = 's';
	ret->v_intersect_direction = 's';
	ret->intersect_direction = 's';
	return (ret);
}
