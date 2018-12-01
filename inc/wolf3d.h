#ifndef WOLF3D_H
# define WOLF3D_H
# include <math.h>
# include <limits.h>
# include <stdio.h>
# include <float.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/inc/ft_printf.h"
# include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Carbon.framework/Versions/A/Frameworks/HIToolbox.framework/Versions/A/Headers/Events.h"
#define WINDOW_SIZE_X 960
#define WINDOW_SIZE_Y 600
#define IMG_SIZE_X 960
#define IMG_SIZE_Y 600
#define ANGLE_ABSOLUTE_NORTH 90.0
#define PLAYER_MOVEMENT_UNIT 2.0
#define PLAYER_FOV 60.0
#define PLAYER_FOV_CHANGE_PER_KEY_PRESS 0.5
#define PLAYER_HEIGHT 32.0
#define STD_LEN 64.0
#define	WIN_PAD_X 0
#define WIN_PAD_Y 0
#define	KEY_W 13
#define KEY_S 1
#define KEY_A 0
#define KEY_D 2
#define KEY_R 15
#define KEY_LEFT_ARROW 123
#define KEY_RIGHT_ARROW 124
#define KEY_ESC 53
#define PLAYER_BUFFER_SPACE 10.0

typedef struct 		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct 		s_player
{
	double			position_x;
	double			position_y;
	double			view_angle;
	double			focal_length;
}					t_player;

typedef struct 		s_state
{
	char			**map;
	char			**pixel_map;
	void 			*mlx;
	void 			*win;
	void 			*img;
	char 			*img_addr;
	int 			endian;
	int				bits_per_pixel;
	int				bytes_per_pixel;
	int				size_line;
	int 			map_width;
	int				map_height;
	int				std_cell_len;
	int				start_x;
	int				start_y;
	char			v_intersect_direction;
	char			h_intersect_direction;
	char			intersect_direction;
	t_player		*player;
	t_rgb			*rgb;
}					t_state;

t_state		*state_init(void);
char		**av_get_map(int argc, char **argv, t_state *state);
t_player 	*player_init(double start_x, double start_y);
void 		map_set_start_location(t_state *state, char **map);
double 		ray_get_intersection(t_player *player, t_state *state, char **map, double angle_degree);
int			ray_get_column_heights(t_state *state);
void 		pixel_draw_single_byte(t_state *state, int col, int row);
int 		loop_handle(t_state *state);
int			keyboard_input_handle(int input, t_state *state);
void 		img_clear_and_destroy(t_state *state);
void 		img_update_and_display(t_state *state);
double		angle_degree_to_radian(double angle_degree);
double 		angle_radian_to_degree(double angle_radian);
void 		player_move(double *pos_x, double *pos_y, double angle_degree);
void 		player_move_forward(double *pos_x, double *pos_y, double angle_degree);
void 		player_move_back(double *pos_x, double *pos_y, double angle_degree);
void 		player_strafe_right(double *pos_x, double *pos_y, double angle_degree);
void 		player_strafe_left(double *pos_x, double *pos_y, double angle_degree);
double		player_get_movement_x_coord(double pos_x, double angle_radian);
double		player_get_movement_y_coord(double pos_y, double angle_radian);
double		ray_check_vertical_intersection(double angle_degree, char **map,
											t_player *player, t_state *state);
double		ray_check_horizontal_intersection(double angle_degree, char **map,
											t_player *player, t_state *state);
void 		img_draw_background(t_state *state);
void 		update_color_based_on_intersect_direction(t_state *state);
int			util_convert_to_int_coord(double std_coord, double std_len);
double		util_convert_to_std_len(int int_len, double std_len);
void 		ray_intersect_nw_corner_handle(double x_new, double y_new,
								double *diff_x, double *diff_y, t_state *state);
void 		ray_intersect_ne_corner_handle(double x_new, double y_new,
								double *diff_x, double *diff_y, t_state *state);
void 		ray_intersect_sw_corner_handle(double x_new, double y_new,
								double *diff_x, double *diff_y, t_state *state);
void 		ray_intersect_se_corner_handle(double x_new, double y_new,
								double *diff_x, double *diff_y, t_state *state);
#endif
