#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <genesis.h>
#include "room.h"
#include "game_state.h"

#define CHARACTER_ANIMATION_DOWN_IDLE		0
#define CHARACTER_ANIMATION_DOWN_WALK		1
#define CHARACTER_ANIMATION_SIDE_IDLE		2
#define CHARACTER_ANIMATION_SIDE_WALK		3
#define CHARACTER_ANIMATION_UP_IDLE			4
#define CHARACTER_ANIMATION_UP_WALK			5

#define CHARACTER_SCROLL_UP_LIMIT       80
#define CHARACTER_SCROLL_DOWN_LIMIT     80
#define CHARACTER_SCROLL_LEFT_LIMIT     100
#define CHARACTER_SCROLL_RIGHT_LIMIT    120

#define CHARACTER_ANIMATION_WALK_FRAMES		8
#define CHARACTER_ANIMATION_FRAMES_PER_TRANSITION		6

#define CHARACTER_SPRITE_WIDTH			24
#define CHARACTER_SPRITE_HEIGHT			24

#define CHARACTER_SHADOW_OFFSET_X		4
#define CHARACTER_SHADOW_OFFSET_Y		18

static const fix16 character_speed_table_x[0xB] =
{
	FIX16(0.0), // 0x00
	FIX16(0.0), // 0x01 UP
	FIX16(0.0), // 0x02 DOWN
	FIX16(0.0), // 0x03
	FIX16(-0.5), // 0x04 LEFT
	FIX16(-0.2), // 0x05 UP_LEFT
	FIX16(-0.2), // 0x06 DOWN_LEFT
	FIX16(0.0), // 0x07
	FIX16(1.0), // 0x08 RIGHT
	FIX16(0.6), // 0x09 UP_RIGHT
	FIX16(0.6)  // 0x0A DOWN_RIGHT
};

static const fix16 character_speed_table_y[0xB] =
{
	FIX16(0.0), // 0x00
	FIX16(-0.5), // 0x01 UP
	FIX16(1.0), // 0x02 DOWN
	FIX16(0.0), // 0x03
	FIX16(0.0), // 0x04 LEFT
	FIX16(-0.2), // 0x05 UP_LEFT
	FIX16(0.6), // 0x06 DOWN_LEFT
	FIX16(0.0), // 0x07
	FIX16(0.0), // 0x08 RIGHT
	FIX16(-0.2), // 0x09 UP_RIGHT
	FIX16(0.6)  // 0x0A DOWN_RIGHT
};

typedef struct character
{
	s16 position_x;
	s16 position_y;
	s16 int_vel_x;
	s16 int_vel_y;
	s16 *room_transform_x;
	s16 *room_transform_y;

	fix16 vel_x;
	fix16 vel_y;
	fix16 max_speed;
	fix16 friction;
	fix16 accel_x;
	fix16 accel_y;

	u8 animation;
	u8 frame;
	u8 frame_count;
	Sprite *sprite;
	Sprite *shadow;
	Sprite *punch;
} character_t;

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, s16 *rtx, s16 *rty, const u16 *pal, u8 palIndex, fix16 maxSpeed, fix16 friction);
void character_update(character_t *ptr, room_t *room);
void character_joyToAxis(u16 joy, fix16 *vx, fix16 *vy);

// Private members

void __character_animate(character_t *ptr);
void __character_move(character_t *ptr, room_t *room);
void __character_transform(character_t *ptr);
u8 __character_collide(character_t *ptr, s16 dx, s16 dy, room_t *room);
void __character_check_warp(character_t *ptr, s16 dx, s16 dy, room_t *room);

#endif // _CHARACTER_H_
