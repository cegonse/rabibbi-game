#ifndef _ROOM_H_
#define _ROOM_H_

typedef struct room
{
	u16 *planeData;
	s16 *collisionData;
	TileSet *tilesetData;
	Palette *paletteData;
} room_t;

void room_load(const room_t *room);

#endif // _ROOM_H_
