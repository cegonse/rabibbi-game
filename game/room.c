#include "room.h"


#define ROOM_PALETTE_INDEX	2

//-------------------------------------------------------------

void room_load(const room_t *room)
{
	VDP_loadTileSet(room->tilesetData, TILE_USERINDEX, TRUE);
	VDP_setPalette(PAL0 + ROOM_PALETTE_INDEX, room->paletteData->data);

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

