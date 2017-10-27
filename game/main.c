#include "init.h"
#include "gfx.h"
#include "character.h"
#include "tween.h"
#include "room.h"
#include "game_state.h"
#include "gui_controller.h"

#include "rooms/rabbibis_den_room_1.h"

static u8 two_players = FALSE;
static u8 game_state = GAME_STATE_INIT;
static character_t playerOneCharacter;
static character_t playerTwoCharacter;
static room_t *currentRoom = NULL;
static gui_state_t guiState;

int main()
{
	system_init();

	// Instantiate the player character
	character_init(&playerOneCharacter, &character_def, 40, 50, character_def.palette->data, 1, FIX16(1.5), FIX16(4.0));

	// Load the first room
	currentRoom = &rabbibis_den_room_1;
	room_load(currentRoom);

	gui_init(&guiState, 1);

	// Controller state
	u16 firstPadState = 0;
	u16 secondPadState = 0;

	while (1)
	{
		// Read joypad
		firstPadState = JOY_readJoypad(JOY_1);
		secondPadState = JOY_readJoypad(JOY_2);

		character_joyToAxis(firstPadState, &(playerOneCharacter.accel_x), &(playerOneCharacter.accel_y), 1);
		character_update(&playerOneCharacter, currentRoom);

		system_endFrame();
	}

	return (0);
}

