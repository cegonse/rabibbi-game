#ifndef _GUI_CONTROLLER_H_
#define _GUI_CONTROLLER_H_

#include <genesis.h>
#include "gui.h"
#include "pause_menu.h"
#include "game_state.h"
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

#define GUI_MENU_ANIMATION_CURVE_OPEN_POINTS		50
#define GUI_MENU_ANIMATION_CURVE_CLOSE_POINTS		25

static const u8 gui_menu_animation_open_curve[GUI_MENU_ANIMATION_CURVE_OPEN_POINTS] = {
	0, 4, 6, 6, 3, 1, 9, 16, 20, 22, 
	21, 17, 11, 3, 10, 24, 37, 47, 56, 63, 
	68, 72, 73, 73, 70, 66, 60, 52, 43, 31, 
	18, 2, 21, 47, 71, 93, 114, 133, 151, 167, 
	182, 195, 207, 217, 225, 232, 238, 241, 244, 245
};

static const u8 gui_menu_animation_close_curve[GUI_MENU_ANIMATION_CURVE_CLOSE_POINTS] = {
	0, 19, 38, 56, 73, 89, 105, 120, 133, 146, 
	159, 170, 181, 191, 200, 208, 215, 222, 227, 232, 
	236, 240, 242, 244, 244
};

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
	u8 menu_frame;
} gui_state_t;

void gui_init(gui_state_t *state, u8 character_pal_index);
void gui_update(gui_state_t *state);

void gui_show_hp(gui_state_t *state, u8 player);
void gui_on_hp_change(gui_state_t *state, u8 player, u8 segments);

#endif // _GUI_CONTROLLER_H_
