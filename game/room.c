#include "room.h"
#include "init.h"


//-------------------------------------------------------------

void room_load(const room_t *room, s16 *room_transform_x, s16 *room_transform_y)
{
	u16 currentTile = 0;

	VDP_loadTileSet(room->tilesetData, TILE_USERINDEX, TRUE);

	// Clear the map with the background color
	VDP_fillTileMap(VDP_PLAN_A, TILE_ATTR_FULL(PAL0 + ROOM_PALETTE_INDEX, FALSE, FALSE, FALSE, TILE_USERINDEX + room->tilesetData->numTile - 1), 0, 64*64);

	// Move the tile plane to center the room
	*room_transform_x = VDP_getScreenWidth()/2 - 8*room->planeWidth/2;
	*room_transform_y = -VDP_getScreenHeight()/2 + 8*room->planeHeight/2;
	
	VDP_setHorizontalScroll(PLAN_A, *room_transform_x);
	VDP_setVerticalScroll(PLAN_A, *room_transform_y);

	// Load the tilemap data
	u8 x = room->planeWidth-1, y = room->planeHeight-1;

	SYSTEM_GPU_SAFE
	(
		do
		{
			VDP_setTileMapXY(PLAN_A,
					TILE_ATTR_FULL(PAL0 + ROOM_PALETTE_INDEX,FALSE,FALSE,FALSE,TILE_USERINDEX + room->planeData[x+room->planeWidth*y]-1),
					x, y);

			if (x != 0) {
				--x;
			} else {
				if (y != 0) {
					x = room->planeWidth-1;
					--y;
				} else {
					break;
				}
			}
		} while (x + y != 0);
	)
}

