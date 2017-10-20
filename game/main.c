#include <genesis.h>
#include "gfx.h"
#include "testmap.h"
#include "character.h"
#include "init.h"
#include "tween.h"
#include "map.h"

static character_t playerChara;

int main()
{
	system_init();

	room_load(rabbibis_den_room_1);

	// Instantiate the player character
	character_init(&playerChara, &character_def, 40, 50, character_def.palette->data, 1, FIX16(1.5), FIX16(4.0));

	// Controller state
	u16 firstPadState = 0;
	u16 secondPadState = 0;

	while (1)
	{
		// Read joypad
		firstPadState = JOY_readJoypad(JOY_1);
		secondPadState = JOY_readJoypad(JOY_2);

		character_joyToAxis(firstPadState, &(playerChara.accel_x), &(playerChara.accel_y), 3);
		character_update(&playerChara);

		// Draw and wait for VBlank
		SPR_update();
		VDP_waitVSync();
	}

	return (0);
}
