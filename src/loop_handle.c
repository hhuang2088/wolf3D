#include "wolf3d.h"

int 			loop_handle(t_state *state)
{
	img_clear_and_destroy(state);
	state->player->view_angle = fmod(state->player->view_angle +
		PLAYER_FOV_CHANGE_PER_KEY_PRESS, 360);
	img_update_and_display(state);
	return (1);
}
