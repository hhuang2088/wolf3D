#include "wolf3d.h"

static int			map_verify_dimensions(char *dimensions)
{
	int		i;
	int 	spaces;

	i = 0;
	spaces = 0;
	if (!ft_isdigit(dimensions[0]))
		return (0);
	while (dimensions[i])
	{
		if (!ft_isdigit(dimensions[i]) && dimensions[i] != ' ')
			return (0);
		if (dimensions[i] == ' ')
			++spaces;
		++i;
	}
	if (spaces != 1)
	{
		return (0);
	}
	return (1);
}

static void		map_get_dimensions(char *dimensions, int *map_height, int *map_width)
{
	int		i;

	i = 0;
	*map_height = ft_atoi(dimensions);
	while (ft_isdigit(dimensions[i]))
		++i;
	++i;
	*map_width = ft_atoi(dimensions + i);
}

static char		**map_generate(int fh, int map_height, int map_width)
{
	int		y;
	int		x;
	char 	*line;
	char	**map;
	char	**num_split;

	y = 0;
	map = (char**)malloc(sizeof(char*) * (map_height + 1));
	map[map_height] = NULL;
	ft_printf("beginning to generate map\n");
	while (get_next_line(fh, &line))
	{
		num_split = ft_strsplit(line, ' ');
		map[y] = (char*)malloc(sizeof(char) * (map_width + 1));
		map[y][map_width] = '\0';
		x = 0;
		while (x < map_width)
		{
			map[y][x] = num_split[x][0];
			++x;
			free(num_split[x]);
		}
		free(num_split);
		ft_printf("%s\n", line);
		++y;
	}
	ft_printf("after map generation\n");
	return (map);
}

char		**av_get_map(int ac, char **av, t_state *state)
{
	int 	fh;
	char	**ret;
	char	*dimensions;

	if (ac != 2 && av)
	{
		ft_printf("Usage:\n./wolf3d [map file location]");
		return (NULL);
	}
	fh = open(av[1], O_RDONLY);
	get_next_line(fh, &dimensions);
	ft_printf("%s\n", dimensions);
	if (map_verify_dimensions(dimensions))
		map_get_dimensions(dimensions, &state->map_width, &state->map_height);
	else
		return (NULL);
	ret = map_generate(fh, state->map_height, state->map_width);
	return (ret);
}
