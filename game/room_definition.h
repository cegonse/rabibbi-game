#ifndef _ROOM_DEFINITION_H_
#define _ROOM_DEFINITION_H_

#include <genesis.h>

#define	MAP_MAX_TARGET_ROOMS	4
#define MAX_ROOMS 256

typedef struct room
{
	const s8 planeWidth;
	const s8 planeHeight;
	const s16 spawn_x;
	const s16 spawn_y;
	const u8 collisionBoxes;

	const u16 *planeData;
	const s16 *collisionData;
	const TileSet *tilesetData;
	const Palette *paletteData;

	const u8 warpBoxes;
	const s16 *warpData;
	const u8 warpTargetRooms[MAP_MAX_TARGET_ROOMS];
	const s16 warpTargetRoomsSpawn_x[MAP_MAX_TARGET_ROOMS];
	const s16 warpTargetRoomsSpawn_y[MAP_MAX_TARGET_ROOMS];
} room_t;

#endif
