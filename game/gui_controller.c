#include "gui_controller.h"


//-------------------------------------------------------------

void gui_init(gui_state_t *state, u8 chrPalIndex)
{
	state->player_one_enabled_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_filled_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->player_one_disabled_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_empty_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

	state->player_two_enabled_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_filled_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->player_two_disabled_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_empty_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

	SPR_setVisibility(state->player_one_disabled_bar[0], HIDDEN);
	SPR_setVisibility(state->player_two_disabled_bar[0], HIDDEN);
	SPR_setVisibility(state->player_one_enabled_bar[0], VISIBLE);
	SPR_setVisibility(state->player_two_enabled_bar[0], VISIBLE);

	for (u8 i = 1; i < GUI_HP_BAR_SEGMENTS - 1; ++i)
	{
		state->player_one_enabled_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_filled_def, 
			GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
		state->player_one_disabled_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_empty_def, 
			GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

		state->player_two_enabled_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_filled_def, 
			GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
		state->player_two_disabled_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_empty_def, 
			GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

		SPR_setVisibility(state->player_one_disabled_bar[i], HIDDEN);
		SPR_setVisibility(state->player_two_disabled_bar[i], HIDDEN);
		SPR_setVisibility(state->player_one_enabled_bar[i], VISIBLE);
		SPR_setVisibility(state->player_two_enabled_bar[i], VISIBLE);
	}

	state->player_one_enabled_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_filled_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->player_one_disabled_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_empty_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

	state->player_two_enabled_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_filled_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->player_two_disabled_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_empty_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

	SPR_setVisibility(state->player_one_disabled_bar[GUI_HP_BAR_SEGMENTS - 1], HIDDEN);
	SPR_setVisibility(state->player_two_disabled_bar[GUI_HP_BAR_SEGMENTS - 1], HIDDEN);
	SPR_setVisibility(state->player_one_enabled_bar[GUI_HP_BAR_SEGMENTS - 1], VISIBLE);
	SPR_setVisibility(state->player_two_enabled_bar[GUI_HP_BAR_SEGMENTS - 1], VISIBLE);
	
	state->player_one_rabbit = SPR_addSprite(&gui_hud_rabbit_def, GUI_HP_PLAY_ONE_X, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->player_two_rabbit = SPR_addSprite(&gui_hud_rabbit_def, GUI_HP_PLAY_TWO_X, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

	SPR_setVisibility(state->player_one_rabbit, VISIBLE);
	SPR_setVisibility(state->player_one_rabbit, VISIBLE);
}

//-------------------------------------------------------------

void gui_show_hp(gui_state_t *state, u8 player)
{
}

//-------------------------------------------------------------

void gui_on_hp_change(gui_state_t *state, u8 player, u8 segments)
{
}

