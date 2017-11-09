#include "init.h"
#include "gfx.h"
#include "character.h"
#include "tween.h"
#include "room.h"
#include "game_state.h"
#include "gui_controller.h"

static u8 twoPlayers = FALSE;
static u8 controllerState = CONTROLLER_STATE_NONE;
static u8 gameState = GAME_STATE_INIT;
static character_t playerOneCharacter;
static character_t playerTwoCharacter;
static room_t *currentRoom = NULL;
static gui_state_t guiState;
static s16 roomTransform_x = 0, roomTransform_y = 0;

int main()
{
	system_init(&controllerState);

	// Load the first room
	currentRoom = &rabbibis_den_room_1;
	VDP_setPalette(PAL0 + ROOM_PALETTE_INDEX, currentRoom->paletteData->data);
	room_load(currentRoom, &roomTransform_x, &roomTransform_y);

	gui_init(&guiState, CHARACTER_PALETTE_INDEX);

	// Instantiate the player character
	character_init(&playerOneCharacter, &character_def, 40, 50, &roomTransform_x, &roomTransform_y,
		character_def.palette->data, CHARACTER_PALETTE_INDEX, FIX16(1.5), FIX16(4.0));

	gameState = GAME_STATE_PLAYING;

	// Controller state
	u16 firstPadState = 0;
	u16 secondPadState = 0;

	while (1)
	{
		firstPadState = JOY_readJoypad(JOY_1);
		if (twoPlayers) secondPadState = JOY_readJoypad(JOY_2);

		if (gameState == GAME_STATE_PLAYING)
		{
			// Check pause button
			if (firstPadState & BUTTON_START || secondPadState & BUTTON_START)
			{
				guiState.menu_state = GUI_MENU_SHOWING;
				gameState = GAME_STATE_PAUSING;
			}

			// Update player one
			character_joyToAxis(firstPadState, &(playerOneCharacter.accel_x), &(playerOneCharacter.accel_y));
			character_update(&playerOneCharacter, currentRoom);

			// Update player two
			if (twoPlayers)
			{
				character_joyToAxis(secondPadState, &(playerTwoCharacter.accel_x), &(playerTwoCharacter.accel_y));
				character_update(&playerTwoCharacter, currentRoom);
			}
		}
		else if (gameState == GAME_STATE_PAUSING)
		{
			if (guiState.menu_state == GUI_MENU_VISIBLE)
			{
				gameState = GAME_STATE_PAUSED;
			}
		}
		else if (gameState == GAME_STATE_UNPAUSING)
		{
			if (guiState.menu_state == GUI_MENU_HIDDEN)
			{
				gameState = GAME_STATE_PLAYING;
			}
		}
		else if (gameState == GAME_STATE_PAUSED)
		{
			// Check pause button
			if (firstPadState & BUTTON_START || secondPadState & BUTTON_START)
			{
				guiState.menu_state = GUI_MENU_HIDING;
				gameState = GAME_STATE_UNPAUSING;
			}
		}

		gui_update(&guiState);
		system_endFrame();
	}

	return (0);
}

//-------------------------------------------------------------

void game_change_room_event(room_t *room, s16 spawn_x, s16 spawn_y)
{
	gameState = GAME_STATE_CHANGING_ROOM;

	// Fade room out
	VDP_setPalette(PAL0 + ROOM_PALETTE_INDEX, currentRoom->paletteData->data);
	VDP_fadePalOut(PAL0 + ROOM_PALETTE_INDEX, 3, FALSE);

	// Fade characters out
	VDP_fadePalOut(PAL0 + CHARACTER_PALETTE_INDEX, 3, FALSE);

	currentRoom = room;
	room_load(currentRoom, &roomTransform_x, &roomTransform_y);
	
	// Move players to spawn and adjust camera to fit
	// players
	playerOneCharacter.position_x = spawn_x;
	playerOneCharacter.position_y = spawn_y;

	if (playerOneCharacter.position_x + roomTransform_x < CHARACTER_SCROLL_LEFT_LIMIT)
	{
		roomTransform_x += CHARACTER_SCROLL_LEFT_LIMIT;
	}
	else if (playerOneCharacter.position_x + roomTransform_x > VDP_getScreenWidth() - CHARACTER_SCROLL_RIGHT_LIMIT)
	{
		roomTransform_x -= CHARACTER_SCROLL_RIGHT_LIMIT;
	}

	if (playerOneCharacter.position_y - roomTransform_y < CHARACTER_SCROLL_UP_LIMIT)
	{
		roomTransform_y -= playerOneCharacter.position_y + CHARACTER_SCROLL_UP_LIMIT;
	}
	else if (playerOneCharacter.position_y - roomTransform_y > VDP_getScreenHeight() - CHARACTER_SCROLL_DOWN_LIMIT)
	{
		roomTransform_y += playerOneCharacter.position_y - CHARACTER_SCROLL_DOWN_LIMIT;
	}

	VDP_setHorizontalScroll(PLAN_A, roomTransform_x);
	VDP_setVerticalScroll(PLAN_A, roomTransform_y);

	// Update characters
	SPR_setPosition(playerOneCharacter.sprite, playerOneCharacter.position_x + roomTransform_x, playerOneCharacter.position_y - roomTransform_y);

	if (twoPlayers)
	{
		SPR_setPosition(playerTwoCharacter.sprite, playerTwoCharacter.position_x + roomTransform_x, playerTwoCharacter.position_y - roomTransform_y);
	}

	SPR_update();

	// Fade characters in
	VDP_fadePalIn(PAL0 + CHARACTER_PALETTE_INDEX, character_def.palette->data, 3, FALSE);

	// Fade room in
	VDP_fadePalIn(PAL0 + ROOM_PALETTE_INDEX, room->paletteData->data, 3, FALSE);

	gameState = GAME_STATE_PLAYING;
}

