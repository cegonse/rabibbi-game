#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "genesis.h"

#define CHARACTER_ANIMATION_DOWN_IDLE		0
#define CHARACTER_ANIMATION_DOWN_WALK		1
#define CHARACTER_ANIMATION_SIDE_IDLE		2
#define CHARACTER_ANIMATION_SIDE_WALK		3
#define CHARACTER_ANIMATION_UP_IDLE			4
#define CHARACTER_ANIMATION_UP_WALK			5

#define CHARACTER_SCROLL_UP_LIMIT       30
#define CHARACTER_SCROLL_DOWN_LIMIT     150
#define CHARACTER_SCROLL_LEFT_LIMIT     30
#define CHARACTER_SCROLL_RIGHT_LIMIT    250

typedef struct character
{
	s16 position_x;
	s16 position_y;

	fix16 vel_x;
	fix16 vel_y;
	s8 accel_x;
	s8 accel_y;

	Sprite *sprite;
} character_t;

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, const u16 *pal, u8 palIndex);

void character_update(character_t *ptr);

void character_joyToAxis(u16 joy, s8 *vx, s8 *vy);

#endif // _CHARACTER_H_
