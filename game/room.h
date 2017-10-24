#ifndef _ROOM_H_
#define _ROOM_H_

#include <genesis.h>

typedef struct room
{
	const s8 planeWidth;
	const s8 planeHeight;
	const s8 collisionBoxes;

	const u16 *planeData;
	const s16 *collisionData;
	const TileSet *tilesetData;
	const Palette *paletteData;
} room_t;

void room_load(const room_t *room);

#endif // _ROOM_H_
