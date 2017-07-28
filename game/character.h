#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "genesis.h"

#define CHARACTER_DIRECTION_NONE	0
#define CHARACTER_DIRECTION_DOWN    1
#define CHARACTER_DIRECTION_LEFT    2
#define CHARACTER_DIRECTION_RIGHT   4
#define CHARACTER_DIRECTION_UP      8

#define CHARACTER_ANIMATION_DOWN_IDLE    		 0
#define CHARACTER_ANIMATION_DOWN_WALK    		 1
#define CHARACTER_ANIMATION_DOWN_RIGHT_IDLE		 2
#define CHARACTER_ANIMATION_DOWN_RIGHT_WALK      3
#define CHARACTER_ANIMATION_RIGHT_IDLE			 4
#define CHARACTER_ANIMATION_RIGHT_WALK			 5
#define CHARACTER_ANIMATION_UP_RIGHT_IDLE		 6
#define CHARACTER_ANIMATION_UP_RIGHT_WALK		 7
#define CHARACTER_ANIMATION_UP_IDLE				 8
#define CHARACTER_ANIMATION_UP_WALK				 9
#define CHARACTER_ANIMATION_LEFT_IDLE			 10
#define CHARACTER_ANIMATION_LEFT_WALK			 11
#define CHARACTER_ANIMATION_UP_LEFT_IDLE		 12
#define CHARACTER_ANIMATION_UP_LEFT_WALK		 13
#define CHARACTER_ANIMATION_DOWN_LEFT_IDLE		 14
#define CHARACTER_ANIMATION_DOWN_LEFT_WALK		 15


#define CHARACTER_ANIM_FRAMES           8

#define CHARACTER_SCROLL_UP_LIMIT       30
#define CHARACTER_SCROLL_DOWN_LIMIT     150
#define CHARACTER_SCROLL_LEFT_LIMIT     30
#define CHARACTER_SCROLL_RIGHT_LIMIT    250

#define CHARACTER_BLINK_TIMER	3

typedef struct character
{
	s16 position_x;
	s16 position_y;
	s8 temp_x;
	s8 temp_y;
	s8 tile_x;
	s8 tile_y;
	u8 last_direction;
	u8 moved;
	u8 animation_frame_wait;
	Sprite *sprite;
	u8 current_animation;
	u8 vDirection;
	u8 hDirection;

	u8 blinking;
	u8 blinking_count;
	u8 blinking_frames;
	u8 visible;
} character_t;

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, const u16 *pal,
			u8 palIndex);

void character_destroy(character_t *ptr);

void character_update(character_t *ptr);

void character_moveTo(character_t *ptr, u8 targetDirection, const u16* collisionMap,
			u8 collisionMapWidth, u8 collisionMapHeight, s8 *vScrollDir, s8 *hScrollDir);

u8 character_joyStateToCharacterDirection(u16 joy);

void character_startBlinking(character_t *ptr, u8 count);

#endif // _CHARACTER_H_
