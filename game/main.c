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

	/*// Load the map tileset and palette to the GPU
	VDP_loadTileSet(&basic_tiles_def, TILE_USERINDEX, TRUE);
	VDP_setPalette(2, tiles_pal_def.data);
	
	// Draw the the test map
	u16 currentTile = 0;
	for (u8 x = 0; x < testmap_PlaneA_WIDTH; ++x)
	{
		for (u8 y = 0; y < testmap_PlaneA_HEIGHT; ++y)
		{
			currentTile = testmap_PlaneA[x+testmap_PlaneA_WIDTH*y];

			if (currentTile == 0) continue;
			--currentTile;

			VDP_setTileMapXY(PLAN_A,
				TILE_ATTR_FULL(PAL2,FALSE,FALSE,FALSE,TILE_USERINDEX + currentTile),
				x, y);
		}
	}*/

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
