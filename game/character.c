#include "character.h"


extern fix16* DELTA_TIME;

//-------------------------------------------------------------

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, const u16 *pal, u8 palIndex)
{
	ptr->position_x = x;
	ptr->position_y = y;

	VDP_setPalette(PAL0 + palIndex, pal);
	ptr->sprite = SPR_addSprite(spr, x, y, TILE_ATTR(PAL0 + palIndex, TRUE, FALSE, FALSE));
	SPR_setAnim(ptr->sprite, CHARACTER_ANIMATION_DOWN_IDLE);
	SPR_update();
}

//-------------------------------------------------------------

void character_update(character_t *ptr)
{
	// Handle acceleration
	fix16 ax = fix16Mul(intToFix16(ptr->accel_x), *DELTA_TIME);
	fix16 ay = fix16Mul(intToFix16(ptr->accel_y), *DELTA_TIME);
	ptr->vel_x += ax;
	ptr->vel_y += ay;

	// Handle speed
	ptr->position_x += fix16ToInt(ptr->vel_x);
	ptr->position_y += fix16ToInt(ptr->vel_y);

	// Transform position and move sprite
	SPR_setPosition(ptr->sprite, ptr->position_x, ptr->position_y);
}

//-------------------------------------------------------------

void character_joyToAxis(u16 state, s8 *vx, s8 *vy)
{
	if (state & BUTTON_LEFT)
	{
		*vx = 1;
	}
 	else if (state & BUTTON_RIGHT)
	{
		*vx = -1;
	}
	else
	{
		*vx = 0;
	}

	if (state & BUTTON_UP)
	{
		*vy = 1;
	}
	else if (state & BUTTON_DOWN)
	{
		*vy = -1;
	}
	else
	{
		*vy = 0;
	}
}
