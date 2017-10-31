// Created with tiled2c.js
#ifndef _rabbibis_den_room_1_
#define _rabbibis_den_room_1_

#include "../room_definition.h"
#define rabbibis_den_room_1_PlaneA_HEIGHT	16
#define rabbibis_den_room_1_PlaneA_WIDTH	16

static const u16 rabbibis_den_room_1_PlaneA[256] = {
	44, 44, 44, 44, 44, 78, 1, 2, 1, 2, 73, 44, 44, 44, 44, 44, 
	44, 114, 91, 90, 91, 94, 17, 18, 17, 18, 89, 90, 91, 90, 115, 44, 
	44, 46, 111, 112, 109, 110, 1, 2, 1, 2, 105, 106, 111, 112, 41, 44, 
	44, 62, 127, 128, 125, 126, 5, 6, 1, 2, 121, 122, 127, 128, 57, 44, 
	93, 94, 143, 144, 141, 142, 21, 22, 17, 18, 137, 138, 143, 144, 89, 90, 
	109, 110, 159, 160, 157, 158, 17, 18, 17, 18, 153, 154, 159, 160, 105, 106, 
	125, 126, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 121, 122, 
	141, 142, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 137, 138, 
	157, 158, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 153, 154, 
	1, 2, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 1, 2, 
	1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 
	17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 
	1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 
	13, 14, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 17, 18, 9, 10, 
	29, 30, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 25, 26, 
	45, 130, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 131, 42, 
};

#define rabbibis_den_room_1_COLLISION_EDGE_COUNT	13

static const s16 rabbibis_den_room_1_collision_data[52] = {
	8, 24, 40, 8,
	40, 0, 8, 24,
	0, 48, 16, 8,
	8, 32, 8, 16,
	80, 0, 8, 24,
	80, 24, 40, 8,
	112, 48, 16, 8,
	112, 32, 8, 16,
	0, 104, 16, 8,
	8, 112, 8, 16,
	16, 120, 96, 8,
	112, 104, 16, 8,
	112, 112, 8, 16,
};

#define rabbibis_den_room_1_WARP_EDGE_COUNT	3

static const s16 rabbibis_den_room_1_warp_data[12] = {
	0, 56, 8, 48,
	48, 0, 32, 8,
	120, 56, 8, 48,
};

static const room_t rabbibis_den_room_1 = {	.tilesetData = &rabbibisden_tiles_def,
	.paletteData = &rabbibisden_tiles_pal_def,
	.planeWidth = 16,
	.planeHeight = 16,
	.planeData = rabbibis_den_room_1_PlaneA,
	.collisionBoxes = 13,
	.collisionData = rabbibis_den_room_1_collision_data,
	.warpBoxes = 3,
	.warpData = rabbibis_den_room_1_warp_data,
	.warpTargetRooms = {
		1,
		2,
		3,
		0,
	},
	.warpTargetRoomsSpawn_x = {
		330,
		0,
		0,
		0,
	},
	.warpTargetRoomsSpawn_y = {
		142,
		0,
		0,
		0,
	},
};

#endif // _rabbibis_den_room_1_
