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

	VDP_setPalette(PAL0 + palIndex, pal);
	ptr->sprite = SPR_addSprite(spr, x, y, TILE_ATTR(PAL0 + palIndex, TRUE, FALSE, FALSE));
	ptr->animation = CHARACTER_ANIMATION_DOWN_IDLE;
	SPR_setAnim(ptr->sprite, CHARACTER_ANIMATION_DOWN_IDLE);
	SPR_update();
}

//-------------------------------------------------------------

void character_update(character_t *ptr)
{
	// Handle acceleration
	fix16 ax = 0, ay = 0;

	// X axis
	if (ptr->accel_x != 0)
	{
		if (abs(ptr->vel_x) < ptr->max_speed)
		{
			ax = fix16Mul(intToFix16(ptr->accel_x), *dt);
			ptr->vel_x += ax;
		}
	}
	else
	{
		if (ptr->vel_x > 0)
		{
			ax = fix16Mul(ptr->friction, *dt);
			ptr->vel_x -= ax;
		}
		else if (ptr->vel_x < 0)
		{
			ax = fix16Mul(ptr->friction, *dt);
			ptr->vel_x += ax;
		}
	}

	// Y axis
	if (ptr->accel_y != 0)
	{
		if (abs(ptr->vel_y) < ptr->max_speed)
		{
			ay = fix16Mul(intToFix16(ptr->accel_y), *dt);
			ptr->vel_y += ay;
		}
	}
	else
	{
		if (ptr->vel_y > 0)
		{
			ay = fix16Mul(ptr->friction, *dt);
			ptr->vel_y -= ay;
		}
		else if (ptr->vel_y < 0)
		{
			ay = fix16Mul(ptr->friction, *dt);
			ptr->vel_y += ay;
		}
	}

	// Handle speed
	ptr->position_x += fix16ToInt(ptr->vel_x);
	ptr->position_y += fix16ToInt(ptr->vel_y);

	// Transform position and move sprite
	SPR_setPosition(ptr->sprite, ptr->position_x, ptr->position_y);
}

//-------------------------------------------------------------

void character_joyToAxis(u16 state, s8 *vx, s8 *vy, s8 scale)
{
	if (state & BUTTON_LEFT)
	{
		*vx = -scale;
	}
 	else if (state & BUTTON_RIGHT)
	{
		*vx = scale;
	}
	else
	{
		*vx = 0;
	}

	if (state & BUTTON_UP)
	{
		*vy = -scale;
	}
	else if (state & BUTTON_DOWN)
	{
		*vy = scale;
	}
	else
	{
		*vy = 0;
	}
}
