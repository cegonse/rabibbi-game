#include "gui_controller.h"


//-------------------------------------------------------------

void gui_init(gui_state_t *state, u8 chrPalIndex)
{
	state->player_one_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_filled_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	/*state->player_one_disabled_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_empty_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));*/

	state->player_two_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_filled_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	/*state->player_two_disabled_bar[0] = SPR_addSprite(&gui_hud_lifebar_begin_empty_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));*/

	for (u8 i = 1; i < GUI_HP_BAR_SEGMENTS - 1; ++i)
	{
		state->player_one_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_filled_def, 
			GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
		/*state->player_one_disabled_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_empty_def, 
			GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));*/

		state->player_two_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_filled_def, 
			GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
		/*state->player_two_disabled_bar[i] = SPR_addSprite(&gui_hud_lifebar_segment_empty_def, 
			GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + i * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));*/
	}

	state->player_one_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_filled_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	/*state->player_one_disabled_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_empty_def, 
		GUI_HP_PLAY_ONE_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_ONE_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));*/

	state->player_two_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_filled_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	/*state->player_two_disabled_bar[GUI_HP_BAR_SEGMENTS - 1] = SPR_addSprite(&gui_hud_lifebar_end_empty_def, 
		GUI_HP_PLAY_TWO_X + GUI_HP_BAR_SPACING + (GUI_HP_BAR_SEGMENTS - 1) * GUI_HP_BAR_SEGMENT_SIZE, GUI_HP_PLAY_TWO_Y, 
		TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));*/
	
	state->player_one_rabbit = SPR_addSprite(&gui_hud_rabbit_def, GUI_HP_PLAY_ONE_X, GUI_HP_PLAY_ONE_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->player_two_rabbit = SPR_addSprite(&gui_hud_rabbit_def, GUI_HP_PLAY_TWO_X, GUI_HP_PLAY_TWO_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

	state->carrot = SPR_addSprite(&gui_hud_carrot_def, GUI_CARROT_X, GUI_CARROT_Y, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->carrot_left_number = SPR_addSprite(&gui_hud_number_0_def, GUI_CARROT_X + GUI_CARROT_LEFT_NUMBER_X_OFFSET, 
		GUI_CARROT_Y + GUI_CARROT_LEFT_NUMBER_Y_OFFSET, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));
	state->carrot_right_number = SPR_addSprite(&gui_hud_number_0_def, GUI_CARROT_X + GUI_CARROT_RIGHT_NUMBER_X_OFFSET, 
		GUI_CARROT_Y + GUI_CARROT_RIGHT_NUMBER_Y_OFFSET, TILE_ATTR(PAL0 + chrPalIndex, TRUE, FALSE, FALSE));

	// Load the pause menu to the B plane and to the palette 3
	u8 x = pause_menu_PlaneA_WIDTH-1;
	u8 y = pause_menu_PlaneA_HEIGHT-1;
	
	SYSTEM_GPU_SAFE
	(
		VDP_loadTileSet(&pause_menu_tiles_def, TILE_USERINDEX + 256, TRUE);
		VDP_setPalette(PAL0 + 3, pause_menu_pal_def.data);
		VDP_setHorizontalScroll(PLAN_B, 0);
		VDP_setVerticalScroll(PLAN_B, 0);
	
		do
		{
			if (pause_menu_PlaneA[x+pause_menu_PlaneA_WIDTH*y] != 0)
			{
				VDP_setTileMapXY(PLAN_B,
					TILE_ATTR_FULL(PAL0 + 3,TRUE,FALSE,FALSE,TILE_USERINDEX + pause_menu_PlaneA[x+pause_menu_PlaneA_WIDTH*y] + 256 -1),
					x, y);
			}

			if (x != 0) {
				--x;
			} else {
				if (y != 0) {
					x = pause_menu_PlaneA_WIDTH-1;
					--y;
				} else {
					break;
				}
			}
		} while (x + y != 0);
	)
}

//-------------------------------------------------------------

void gui_show_hp(gui_state_t *state, u8 player)
{
}

//-------------------------------------------------------------

void gui_on_hp_change(gui_state_t *state, u8 player, u8 segments)
{
	if (player == 1)
	{
		if (segments == 0)
		{
			
		}
	}
	else
	{
	}
}

