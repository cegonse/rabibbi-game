#ifndef _GUI_CONTROLLER_H_
#define _GUI_CONTROLLER_H_

#include <genesis.h>
#include "gui.h"

#define GUI_HP_BAR_SEGMENTS			8
#define GUI_HP_BAR_SEGMENT_SIZE		10
#define GUI_HP_BAR_SPACING			16

#define GUI_HP_PLAY_ONE_X			10
#define GUI_HP_PLAY_ONE_Y			10

#define GUI_HP_PLAY_TWO_X			10
#define GUI_HP_PLAY_TWO_Y			25

typedef struct gui_state
{
	Sprite *player_one_enabled_bar[GUI_HP_BAR_SEGMENTS];
	Sprite *player_one_disabled_bar[GUI_HP_BAR_SEGMENTS];
	Sprite *player_two_enabled_bar[GUI_HP_BAR_SEGMENTS];
	Sprite *player_two_disabled_bar[GUI_HP_BAR_SEGMENTS];
	Sprite *player_one_rabbit;
	Sprite *player_two_rabbit;
} gui_state_t;

void gui_init(gui_state_t *state, u8 character_pal_index);
void gui_show_hp(gui_state_t *state, u8 player);
void gui_on_hp_change(gui_state_t *state, u8 player, u8 segments);

#endif // _GUI_CONTROLLER_H_
