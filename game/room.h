#ifndef _ROOM_H_
#define _ROOM_H_

#include <genesis.h>
#include "gfx.h"
#include "game_state.h"
#include "rooms/rabbibis_den_room_1.h"
#include "rooms/rabbibis_den_room_2.h"

//-------------------------------------------------------------

static const room_t *ROOM_LIST[MAX_ROOMS] = {
	&rabbibis_den_room_1,
	&rabbibis_den_room_2
};

//-------------------------------------------------------------

void room_load(const room_t *room, s16 *room_transform_x, s16 *room_transform_y);

#endif // _ROOM_H_
