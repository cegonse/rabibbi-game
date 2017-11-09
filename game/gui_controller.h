#ifndef _GUI_CONTROLLER_H_
#define _GUI_CONTROLLER_H_

#include <genesis.h>
#include "gui.h"
#include "pause_menu.h"
#include "init.h"

#define GUI_HP_BAR_SEGMENTS			8
#define GUI_HP_BAR_SEGMENT_SIZE		10
#define GUI_HP_BAR_SPACING			16

#define GUI_HP_PLAY_ONE_X			10
#define GUI_HP_PLAY_ONE_Y			10

#define GUI_HP_PLAY_TWO_X			10
#define GUI_HP_PLAY_TWO_Y			25

#define GUI_CARROT_X				260
#define GUI_CARROT_Y				13

#define GUI_CARROT_LEFT_NUMBER_X_OFFSET		20
#define GUI_CARROT_LEFT_NUMBER_Y_OFFSET		4
#define GUI_CARROT_RIGHT_NUMBER_X_OFFSET		28
#define GUI_CARROT_RIGHT_NUMBER_Y_OFFSET		4

#define GUI_MENU_VISIBLE		0
#define GUI_MENU_SHOWING		1
#define GUI_MENU_HIDING			2
#define GUI_MENU_HIDDEN			3

typedef struct gui_state
{
	Sprite *player_one_bar[GUI_HP_BAR_SEGMENTS];
	Sprite *player_two_bar[GUI_HP_BAR_SEGMENTS];
	Sprite *player_one_rabbit;
	Sprite *player_two_rabbit;

	Sprite *carrot;
	Sprite *carrot_left_number;
	Sprite *carrot_right_number;

	u8 menu_state;
	u8 menu_position_y;
} gui_state_t;

void gui_init(gui_state_t *state, u8 character_pal_index);
void gui_update(gui_state_t *state);

void gui_show_hp(gui_state_t *state, u8 player);
void gui_on_hp_change(gui_state_t *state, u8 player, u8 segments);

#endif // _GUI_CONTROLLER_H_
