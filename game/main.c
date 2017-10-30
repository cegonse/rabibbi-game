#include "init.h"
#include "gfx.h"
#include "character.h"
#include "tween.h"
#include "room.h"
#include "game_state.h"
#include "gui_controller.h"

static u8 twoPlayers = FALSE;
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
		// Update player one
		firstPadState = JOY_readJoypad(JOY_1);
		character_joyToAxis(firstPadState, &(playerOneCharacter.accel_x), &(playerOneCharacter.accel_y), 1);
		character_update(&playerOneCharacter, currentRoom);

		// Update player two
		if (twoPlayers)
		{
			secondPadState = JOY_readJoypad(JOY_2);
		}

		system_endFrame();
	}

	return (0);
}

//-------------------------------------------------------------

void game_change_room_event(room_t *room, s16 spawn_x, s16 spawn_y)
{
	currentRoom = room;
	room_load(currentRoom);
	
	// Move players to spawn
	playerOneCharacter.position_x = spawn_x;
	playerOneCharacter.position_y = spawn_y;
	__character_transform(&playerOneCharacter);

	if (twoPlayers)
	{
	}
}

