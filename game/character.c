#include "character.h"


//-------------------------------------------------------------

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, s16 *rtx, s16 *rty, const u16 *pal, u8 palIndex, fix16 maxSpeed, fix16 friction)
{
	ptr->position_x = x;
	ptr->position_y = y;
	ptr->int_vel_x = 0;
	ptr->int_vel_y = 0;
	ptr->room_transform_x = rtx;
	ptr->room_transform_y = rty;
	ptr->max_speed = maxSpeed;
	ptr->friction = friction;
	ptr->vel_x = 0;
	ptr->vel_y = 0;
	ptr->accel_x = 0;
	ptr->accel_y = 0;
	ptr->frame = 0;
	ptr->frame_count = 0;

	VDP_setPalette(PAL0 + palIndex, pal);
	ptr->sprite = SPR_addSprite(spr, x, y, TILE_ATTR(PAL0 + palIndex, FALSE, FALSE, FALSE));
	ptr->animation = CHARACTER_ANIMATION_DOWN_IDLE;
	SPR_setAnim(ptr->sprite, ptr->animation);
	SPR_update();
}

//-------------------------------------------------------------

void character_update(character_t *ptr, room_t *room)
{
	__character_move(ptr, room);
	__character_animate(ptr);
	__character_transform(ptr);
}

//-------------------------------------------------------------

inline void __character_move(character_t *ptr, room_t *room)
{
	// X axis
	if (ptr->accel_x != 0)
	{
		if (abs(ptr->vel_x) < ptr->max_speed)
		{
			ptr->vel_x += ptr->accel_x;
		}
	}
	else
	{
		if (ptr->vel_x > 0)
		{
			ptr->vel_x -= ptr->friction;

			if (ptr->vel_x < 0)
			{
				ptr->vel_x = 0;
			}
		}
		else if (ptr->vel_x < 0)
		{
			ptr->vel_x += ptr->friction;

			if (ptr->vel_x > 0)
			{
				ptr->vel_x = 0;
			}
		}
	}

	// Y axis
	if (ptr->accel_y != 0)
	{
		if (abs(ptr->vel_y) < ptr->max_speed)
		{
			ptr->vel_y += ptr->accel_y;
		}
	}
	else
	{
		if (ptr->vel_y > 0)
		{
			ptr->vel_y -= ptr->friction;

			if (ptr->vel_y < 0)
			{
				ptr->vel_y = 0;
			}
		}
		else if (ptr->vel_y < 0)
		{
			ptr->vel_y += ptr->friction;

			if (ptr->vel_y > 0)
			{
				ptr->vel_y = 0;
			}
		}
	}

	// Handle speed
	ptr->int_vel_x = fix16ToInt(ptr->vel_x);
	ptr->int_vel_y = fix16ToInt(ptr->vel_y);

	// Handle warp triggers
	__character_check_warp(ptr, ptr->int_vel_x, ptr->int_vel_y, room);

	// Handle collisions
    if (!__character_collide(ptr, ptr->int_vel_x, 0, room))
	{
		ptr->position_x += ptr->int_vel_x;
	}

	if (!__character_collide(ptr, 0, ptr->int_vel_y, room))
	{
		ptr->position_y += ptr->int_vel_y;
	}
}

//-------------------------------------------------------------

inline u8 __character_collide(character_t *ptr, s16 dx, s16 dy, room_t *room)
{
	s16 x, y, w, h;
	u8 collide = 0;

	const s16 chr_x = ptr->position_x + dx;
	const s16 chr_y = ptr->position_y + dy;
	const s16 chr_w = CHARACTER_SPRITE_WIDTH;
	const s16 chr_h = CHARACTER_SPRITE_HEIGHT;

	// Test against all the collision edges in the room
	for (u8 i = 0; i < room->collisionBoxes * 4; i += 4)
	{
		x = room->collisionData[i];
		y = room->collisionData[i+1];
		w = room->collisionData[i+2];
		h = room->collisionData[i+3];

		collide = (chr_x < x + w && chr_x + chr_w > x && chr_y < y + h && chr_h + chr_y > y);
		if (collide) return collide;
	}

	return collide;
}

//-------------------------------------------------------------

inline void __character_check_warp(character_t *ptr, s16 dx, s16 dy, room_t *room)
{
	s16 x, y, w, h;
	u8 collide = 0;

	const s16 chr_x = ptr->position_x + dx;
	const s16 chr_y = ptr->position_y + dy;
	const s16 chr_w = CHARACTER_SPRITE_WIDTH;
	const s16 chr_h = CHARACTER_SPRITE_HEIGHT;

	// Test against all the collision edges in the room
	for (u8 i = 0; i < room->warpBoxes * 4; i += 4)
	{
		x = room->warpData[i];
		y = room->warpData[i+1];
		w = room->warpData[i+2];
		h = room->warpData[i+3];

		collide = (chr_x < x + w && chr_x + chr_w > x && chr_y < y + h && chr_h + chr_y > y);

		if (collide)
		{
			room_t *targetRoom = ROOM_LIST[room->warpTargetRooms[i]];
			game_change_room_event(targetRoom, room->warpTargetRoomsSpawn_x[i], room->warpTargetRoomsSpawn_y[i]);
			return;
		}
	}
}

//-------------------------------------------------------------

inline void __character_animate(character_t *ptr)
{
	if (ptr->animation == CHARACTER_ANIMATION_DOWN_IDLE || ptr->animation == CHARACTER_ANIMATION_UP_IDLE ||
		ptr->animation == CHARACTER_ANIMATION_SIDE_IDLE)
	{
		if (ptr->vel_y > 0)
		{
			ptr->animation = CHARACTER_ANIMATION_DOWN_WALK;
			SPR_setAnim(ptr->sprite, ptr->animation);
			ptr->frame = 0;
		}
		else if (ptr->vel_y < 0)
		{
			ptr->animation = CHARACTER_ANIMATION_UP_WALK;
			SPR_setAnim(ptr->sprite, ptr->animation);
			ptr->frame = 0;
		}

		if (ptr->vel_x > 0)
		{
			ptr->animation = CHARACTER_ANIMATION_SIDE_WALK;
			SPR_setHFlip(ptr->sprite, FALSE);
			SPR_setAnim(ptr->sprite, ptr->animation);
			ptr->frame = 0;
		}
		else if (ptr->vel_x < 0)
		{
			ptr->animation = CHARACTER_ANIMATION_SIDE_WALK;
			SPR_setHFlip(ptr->sprite, TRUE);
			SPR_setAnim(ptr->sprite, ptr->animation);
			ptr->frame = 0;
		}
	}

	if (ptr->animation == CHARACTER_ANIMATION_DOWN_WALK)
	{
		if (ptr->vel_y == 0)
		{
			ptr->animation = CHARACTER_ANIMATION_DOWN_IDLE;
			SPR_setAnim(ptr->sprite, ptr->animation);
			ptr->frame = 0;
		}
	}

	if (ptr->animation == CHARACTER_ANIMATION_UP_WALK)
	{
		if (ptr->vel_y == 0)
		{
			ptr->animation = CHARACTER_ANIMATION_UP_IDLE;
			SPR_setAnim(ptr->sprite, ptr->animation);
			ptr->frame = 0;
		}
	}

	if (ptr->animation == CHARACTER_ANIMATION_SIDE_WALK)
	{
		if (ptr->vel_x == 0)
		{
			ptr->animation = CHARACTER_ANIMATION_SIDE_IDLE;
			SPR_setAnim(ptr->sprite, ptr->animation);
			ptr->frame = 0;
		}
	}

	// Handle animation frames
	if (ptr->animation == CHARACTER_ANIMATION_DOWN_WALK ||
		ptr->animation == CHARACTER_ANIMATION_SIDE_WALK ||
		ptr->animation == CHARACTER_ANIMATION_UP_WALK)
	{
		ptr->frame_count++;

		if (ptr->frame_count == CHARACTER_ANIMATION_FRAMES_PER_TRANSITION)
		{
			SPR_setFrame(ptr->sprite, ptr->frame);
			ptr->frame++;
			ptr->frame_count = 0;
		
			if (ptr->frame == CHARACTER_ANIMATION_WALK_FRAMES)
			{
				ptr->frame = 0;
			}
		}
	}
}

//-------------------------------------------------------------

inline void __character_transform(character_t *ptr)
{
	if (ptr->position_x + *ptr->room_transform_x < CHARACTER_SCROLL_LEFT_LIMIT || ptr->position_x + *ptr->room_transform_x > VDP_getScreenWidth() - CHARACTER_SCROLL_RIGHT_LIMIT)
	{
		*ptr->room_transform_x -= ptr->int_vel_x;
		VDP_setHorizontalScroll(PLAN_A, *ptr->room_transform_x);
	}

	if (ptr->position_y - *ptr->room_transform_y < CHARACTER_SCROLL_UP_LIMIT || ptr->position_y - *ptr->room_transform_y > VDP_getScreenHeight() - CHARACTER_SCROLL_DOWN_LIMIT)
	{
		*ptr->room_transform_y += ptr->int_vel_y;
		VDP_setVerticalScroll(PLAN_A, *ptr->room_transform_y);
	}

	SPR_setPosition(ptr->sprite, ptr->position_x + *ptr->room_transform_x, ptr->position_y - *ptr->room_transform_y);
}

//-------------------------------------------------------------

void character_joyToAxis(u16 state, fix16 *vx, fix16 *vy)
{
	*vx = character_speed_table_x[state & 0x0F];
	*vy = character_speed_table_y[state & 0x0F];
}

