#include "character.h"


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
	// Handle speed
	ptr->position_x += ptr->vel_x;
	ptr->position_y += ptr->vel_y;

	// Transform position and move sprite
	SPR_setPosition(ptr->sprite, ptr->position_x, ptr->position_y);
}

//-------------------------------------------------------------

void character_joyToSpeed(u16 joy, s8 *vx, s8 *vy)
{
	u16 state = JOY_readJoypad(joy);

	if (state & BUTTON_LEFT)
	{
		*vx = 1;
	}

	if (state & BUTTON_RIGHT)
	{
		*vx = -1;
	}

	if (state & BUTTON_UP)
	{
		*vy = 1;
	}

	if (state & BUTTON_DOWN)
	{
		*vy = -1;
	}
}
