NAME = wolf3d
HEADER = ./inc/
SRCDIR = ./src/
FLAGS = -g -Wall -Wextra -Werror
CC = gcc
FILES = main.c av_get_map.c state_init.c player_init.c map_util.c ray_util.c\
				ray_get_intersection.c pixel_util.c loop_handle.c player_movement.c \
				keyboard_input_handle.c img_util.c angle_util.c util.c \
				ray_intersect_corner_util.c

OPTIONS = -I$(HEADER) $(FLAGS)
LIBDIR = ./libft/
LIBFT = $(LIBDIR)libft.a
LIBLINK = -L$(LIBDIR) -lft
PFDIR = ./ft_printf/
PRINTF = $(PFDIR)ft_printf.a
PFLINK = -L$(PFDIR) -lftprintf
LIBMLXDIR = ./minilibx_macos/
LIBMLX = $(LIBMLXDIR)libmlx.a
LIBMLXLINK = -L$(LIBMLXDIR) -lmlx
FRAMEWORK = -framework OpenGL -framework AppKit
SRC = $(addprefix $(SRCDIR), $(FILES))
OBJ = $(FILES:.c=.o)

.PHONY: all clean fclean re

all: libft printf libmlx $(NAME)

libft: $(LIBFT)

printf: $(PRINTF)

libmlx: $(LIBMLX)

$(LIBFT):
	make -C $(LIBDIR)

$(PRINTF):
	make -C $(PFDIR)

$(LIBMLX):
	make -C $(LIBMLXDIR)

main.o: $(SRCDIR)main.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)main.c

state_init.o: $(SRCDIR)state_init.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)state_init.c

player_init.o: $(SRCDIR)player_init.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)player_init.c

av_get_map.o: $(SRCDIR)main.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)av_get_map.c

util.o: $(SRCDIR)util.c $(HEADER)wolf3d.h
	$(CC) $(OPTIONS) -c $(SRCDIR)util.c

ray_get_intersection.o: $(SRCDIR)ray_get_intersection.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)ray_get_intersection.c

ray_intersect_corner_util.o: $(SRCDIR)ray_intersect_corner_util.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)ray_intersect_corner_util.c

ray_util.o: $(SRCDIR)ray_util.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)ray_util.c

pixel_util.o: $(SRCDIR)pixel_util.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)pixel_util.c

img_util.o: $(SRCDIR)img_util.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)img_util.c

loop_handle.o: $(SRCDIR)loop_handle.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)loop_handle.c

map_util.o: $(SRCDIR)map_util.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)map_util.c

angle_util.o: $(SRCDIR)angle_util.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)angle_util.c

keyboard_input_handle.o: $(SRCDIR)keyboard_input_handle.c $(HEADER)wolf3d.h
	 $(CC) $(OPTIONS) -c $(SRCDIR)keyboard_input_handle.c

player_movement.o: $(SRCDIR)player_movement.c $(HEADER)wolf3d.h
	$(CC) $(OPTIONS) -c $(SRCDIR)player_movement.c


$(NAME): $(OBJ)
	$(CC) $(LIBLINK) $(PFLINK) $(LIBMLXLINK) $(OBJ) $(FRAMEWORK) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
