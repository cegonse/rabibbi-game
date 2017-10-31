#include "init.h"
#include "gfx.h"
#include "character.h"
#include "tween.h"
#include "room.h"
#include "game_state.h"
#include "gui_controller.h"

static u8 twoPlayers = FALSE;
static u8 gameState = GAME_STATE_INIT;
static character_t playerOneCharacter;
static character_t playerTwoCharacter;
static room_t *currentRoom = NULL;
static gui_state_t guiState;
static s16 roomTransform_x = 0, roomTransform_y = 0;

int main()
{
	system_init();

	// Instantiate the player character
	character_init(&playerOneCharacter, &character_def, 40, 50, &roomTransform_x, &roomTransform_y,
		character_def.palette->data, 1, FIX16(1.5), FIX16(4.0));

	// Load the first room
	currentRoom = &rabbibis_den_room_1;
	room_load(currentRoom, &roomTransform_x, &roomTransform_y);

	gui_init(&guiState, 1);

	gameState = GAME_STATE_PLAYING;

	// Controller state
	u16 firstPadState = 0;
	u16 secondPadState = 0;

	while (1)
	{
		if (gameState == GAME_STATE_PLAYING)
		{
			// Update player one
			firstPadState = JOY_readJoypad(JOY_1);
			character_joyToAxis(firstPadState, &(playerOneCharacter.accel_x), &(playerOneCharacter.accel_y), 1);
			character_update(&playerOneCharacter, currentRoom);

			// Update player two
			if (twoPlayers)
			{
				secondPadState = JOY_readJoypad(JOY_2);
			}
		}

		system_endFrame();
	}

	return (0);
}

//-------------------------------------------------------------

void game_change_room_event(room_t *room, s16 spawn_x, s16 spawn_y)
{
	gameState = GAME_STATE_CHANGING_ROOM;

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

	__character_transform(&playerOneCharacter);

	if (twoPlayers)
	{
	}

	gameState = GAME_STATE_PLAYING;
}

