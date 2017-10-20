#include "character.h"


extern fix16 *dt;

//-------------------------------------------------------------

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, const u16 *pal, u8 palIndex, fix16 maxSpeed, fix16 friction)
{
	ptr->position_x = x;
	ptr->position_y = y;
	ptr->max_speed = maxSpeed;
	ptr->friction = friction;
	ptr->vel_x = 0;
	ptr->vel_y = 0;
	ptr->accel_x = 0;
	ptr->accel_y = 0;
	ptr->frame = 0;

	VDP_setPalette(PAL0 + palIndex, pal);
	ptr->sprite = SPR_addSprite(spr, x, y, TILE_ATTR(PAL0 + palIndex, TRUE, FALSE, FALSE));
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
	fix16 ax = 0, ay = 0;
	s16 vx, vy;

	// X axis
	if (ptr->accel_x != 0)
	{
		if (abs(ptr->vel_x) < ptr->max_speed)
		{
			ax = fix16Mul(ptr->accel_x, *dt);
			ptr->vel_x += ax;
		}
	}
	else
	{
		if (ptr->vel_x > 0)
		{
			ax = fix16Mul(ptr->friction, *dt);
			ptr->vel_x -= ax;

			if (ptr->vel_x < 0)
			{
				ptr->vel_x = 0;
			}
		}
		else if (ptr->vel_x < 0)
		{
			ax = fix16Mul(ptr->friction, *dt);
			ptr->vel_x += ax;

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
			ay = fix16Mul(ptr->accel_y, *dt);
			ptr->vel_y += ay;
		}
	}
	else
	{
		if (ptr->vel_y > 0)
		{
			ay = fix16Mul(ptr->friction, *dt);
			ptr->vel_y -= ay;

			if (ptr->vel_y < 0)
			{
				ptr->vel_y = 0;
			}
		}
		else if (ptr->vel_y < 0)
		{
			ay = fix16Mul(ptr->friction, *dt);
			ptr->vel_y += ay;

			if (ptr->vel_y > 0)
			{
				ptr->vel_y = 0;
			}
		}
	}

	// Handle speed
	vx = fix16ToInt(ptr->vel_x);
	vy = fix16ToInt(ptr->vel_y);

	if (!__character_collide(ptr, vx, vy, room))
	{
		ptr->position_x += vx;
		ptr->position_y += vy;
	}
}

//-------------------------------------------------------------

inline u8 __character_collide(character_t *ptr, s16 dx, s16 dy, room_t *room)
{
	u8 collides = 0;
	s16 x0, y0, xf, yf;
	s16 ddx = dx + ptr->position_x, ddy = dy + ptr->position_y;

	// Test against all the collision edges in the room
	for (u8 i = 0; i < room->collisionEdges * 4; i += 4)
	{
		x0 = room->collisionData[i];
		y0 = room->collisionData[i+1];
		xf = room->collisionData[i+2];
		yf = room->collisionData[i+3];

		if (collides) break;
	}
	
	return collides;
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
		fix16 avgSpeed = fix16Div(abs(ptr->vel_x) + abs(ptr->vel_y), FIX16(2.0));
		
		SPR_setFrame(ptr->sprite, fix16ToInt(ptr->frame));
		ptr->frame += fix16Mul(avgSpeed, *dt);
		
		if (fix16ToInt(ptr->frame) == CHARACTER_ANIMATION_WALK_FRAMES)
		{
			ptr->frame = 0;
		}
	}
}

//-------------------------------------------------------------

inline void __character_transform(character_t *ptr)
{
	SPR_setPosition(ptr->sprite, ptr->position_x, ptr->position_y);
}

//-------------------------------------------------------------

void character_joyToAxis(u16 state, fix16 *vx, fix16 *vy, s8 scale)
{
	*vx = 0;
	*vy = 0;

	// Generate the movement vector
	if (state & BUTTON_LEFT)
	{
		if (state & BUTTON_UP)
		{
			*vx = -FIX16(0.7);
			*vy = -FIX16(0.7);
		}
		else if (state & BUTTON_DOWN)
		{
			*vx = -FIX16(0.7);
			*vy = FIX16(0.7);
		}
		else
		{
			*vx = FIX16(-1.0);
		}
	}
 	else if (state & BUTTON_RIGHT)
	{
		if (state & BUTTON_UP)
		{
			*vx = FIX16(0.7);
			*vy = -FIX16(0.7);
		}
		else if (state & BUTTON_DOWN)
		{
			*vx = FIX16(0.7);
			*vy = FIX16(0.7);
		}
		else
		{
			*vx = FIX16(1.0);
		}
	}
	else if (state & BUTTON_UP)
	{
		*vy = FIX16(-1.0);
	}
	else if (state & BUTTON_DOWN)
	{
		*vy = FIX16(1.0);
	}

	*vx = fix16Mul(*vx, intToFix16(scale));
	*vy = fix16Mul(*vy, intToFix16(scale));
}

