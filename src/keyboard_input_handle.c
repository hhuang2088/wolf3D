#include "wolf3d.h"

int		keyboard_input_handle(int input, t_state *state)
{
	img_clear_and_destroy(state);
	/*
	else if(input == KEY_S)
		state->player->position_y += PLAYER_MOVEMENT_UNIT;
	else if(input == KEY_A)
		state->player->position_x -= PLAYER_MOVEMENT_UNIT;
	else if(input == KEY_D)
		state->player->position_x += PLAYER_MOVEMENT_UNIT;
	*/
	if (input == KEY_W)
		player_move_forward(&state->player->position_x, &state->player->position_y, state->player->view_angle);
	else if(input == KEY_S)
		player_move_back(&state->player->position_x, &state->player->position_y, state->player->view_angle);
	else if (input == KEY_LEFT_ARROW)
		state->player->view_angle = fmod(state->player->view_angle +
		PLAYER_FOV_CHANGE_PER_KEY_PRESS, 360);
	else if (input == KEY_RIGHT_ARROW)
	{
		state->player->view_angle = fmod(state->player->view_angle -
		PLAYER_FOV_CHANGE_PER_KEY_PRESS, 360);
		if (state->player->view_angle < 0)
			state->player->view_angle = 360.0 + state->player->view_angle; 
	}
	else if(input == KEY_A)
		player_strafe_left(&state->player->position_x, &state->player->position_y, state->player->view_angle);
	else if(input == KEY_D)
		player_strafe_right(&state->player->position_x, &state->player->position_y, state->player->view_angle);
	else if(input == KEY_ESC)
		exit(0);
	img_update_and_display(state);
	return (1);
}
