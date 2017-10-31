#include "room.h"


#define ROOM_PALETTE_INDEX	2

//-------------------------------------------------------------

void room_load(const room_t *room, s16 *room_transform_x, s16 *room_transform_y)
{
	VDP_loadTileSet(room->tilesetData, TILE_USERINDEX, TRUE);
	VDP_setPalette(PAL0 + ROOM_PALETTE_INDEX, room->paletteData->data);

	// Clear the map with the background color
	VDP_fillTileMap(VDP_PLAN_A, TILE_ATTR_FULL(PAL0 + ROOM_PALETTE_INDEX, FALSE, FALSE, FALSE, TILE_USERINDEX + room->tilesetData->numTile - 1), 0, 64*64);

	// Move the tile plane to center the room
	*room_transform_x = VDP_getScreenWidth()/2 - 8*room->planeWidth/2;
	*room_transform_y = -VDP_getScreenHeight()/2 + 8*room->planeHeight/2;
	
	VDP_setHorizontalScroll(PLAN_A, *room_transform_x);
	VDP_setVerticalScroll(PLAN_A, *room_transform_y);

	// Load the tilemap data
	u16 currentTile = 0;
	for (u8 x = 0; x < room->planeWidth; ++x)
	{
		for (u8 y = 0; y < room->planeHeight; ++y)
		{
			currentTile = room->planeData[x+room->planeWidth*y];

			if (currentTile == 0) continue;
			--currentTile;

			VDP_setTileMapXY(PLAN_A,
				TILE_ATTR_FULL(PAL0 + ROOM_PALETTE_INDEX,FALSE,FALSE,FALSE,TILE_USERINDEX + currentTile),
				x, y);
		}
	}
}

