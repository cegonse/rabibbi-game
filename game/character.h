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

#define CHARACTER_ANIMATION_WALK_FRAMES		8

typedef struct character
{
	s16 position_x;
	s16 position_y;

	fix16 vel_x;
	fix16 vel_y;
	fix16 max_speed;
	fix16 friction;
	fix16 accel_x;
	fix16 accel_y;

	u8 animation;
	fix16 frame;
	Sprite *sprite;
} character_t;

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, const u16 *pal, u8 palIndex, fix16 maxSpeed, fix16 friction);

void character_update(character_t *ptr);

void character_joyToAxis(u16 joy, fix16 *vx, fix16 *vy, s8 scale);

// Private members

void __character_animate(character_t *ptr);
void __character_move(character_t *ptr);
void __character_transform(character_t *ptr);

#endif // _CHARACTER_H_
