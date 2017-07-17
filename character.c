#include "character.h"


//-------------------------------------------------------------

void character_init(character_t *ptr, const SpriteDefinition *spr, s16 x, s16 y, const u16 *pal, u8 palIndex)
{
	ptr->position_x = x;
	ptr->position_y = y;
	ptr->temp_x = x % 8;
	ptr->temp_y = y % 8;
	ptr->tile_x = x / 8;
	ptr->tile_y = y / 8;
	ptr->last_direction = CHARACTER_DIRECTION_DOWN;
	ptr->moved = FALSE;
	ptr->animation_frame_wait = 0;

	ptr->blinking = FALSE;
	ptr->blinking_count = 0;
	ptr->blinking_frames = 0;
	ptr->visible = TRUE;

	VDP_setPalette(PAL0 + palIndex, pal);
	ptr->sprite = SPR_addSprite(spr, x, y, TILE_ATTR(PAL0 + palIndex, TRUE, FALSE, FALSE));
	SPR_setAnim(ptr->sprite, CHARACTER_DIRECTION_DOWN);
	SPR_update();
}

//-------------------------------------------------------------

void character_destroy(character_t *ptr)
{
	SPR_releaseSprite(ptr->sprite);
}

//-------------------------------------------------------------

void character_update(character_t *ptr)
{
	// Handle blinking
	if (ptr->blinking)
	{
		ptr->blinking_frames++;

		if (ptr->blinking_frames == CHARACTER_BLINK_TIMER)
		{
			ptr->blinking_frames = 0;
			ptr->blinking_count--;

			if (ptr->visible)
			{
				ptr->visible = FALSE;
				SPR_setVisibility(ptr->sprite, HIDDEN);
			}
			else
			{
				ptr->visible = TRUE;
				SPR_setVisibility(ptr->sprite, VISIBLE);
			}

			if (ptr->blinking_count == 0)
			{
				ptr->blinking = FALSE;
				ptr->visible = TRUE;
				SPR_setVisibility(ptr->sprite, VISIBLE);
			}
		}
	}

	// Handle position
	SPR_setPosition(ptr->sprite, ptr->position_x, ptr->position_y);

	// Handle animation
	if (!ptr->moved)
	{
		SPR_setFrame(ptr->sprite, 0);
	}
	else
	{
		++(ptr->animation_frame_wait);

		if (ptr->animation_frame_wait == CHARACTER_ANIM_FRAMES)
		{
			SPR_nextFrame(ptr->sprite);
			ptr->animation_frame_wait = 0;
		}
	}
}

//-------------------------------------------------------------

inline void character_startBlinking(character_t *ptr, u8 count)
{
	if (ptr->blinking) return;

	ptr->blinking_count = count;
	ptr->blinking_frames = 0;
	ptr->blinking = TRUE;
}

//-------------------------------------------------------------

u8 character_joyStateToCharacterDirection(u16 joy)
{
	u16 state = JOY_readJoypad(joy);
	u8 direction = CHARACTER_DIRECTION_NONE;

	if (state & BUTTON_LEFT)
	{
		direction |= CHARACTER_DIRECTION_LEFT;
	}

	if (state & BUTTON_RIGHT)
	{
		direction |= CHARACTER_DIRECTION_RIGHT;
	}

	if (state & BUTTON_UP)
	{
		direction |= CHARACTER_DIRECTION_UP;
	}

	if (state & BUTTON_DOWN)
	{
		direction |= CHARACTER_DIRECTION_DOWN;
	}

	return direction;
}

//-------------------------------------------------------------

void character_moveTo(character_t *ptr, u8 targetDirection, const u16* collisionMap, u8 collisionMapWidth,
	u8 collisionMapHeight, s8 *vScrollDir, s8 *hScrollDir)
{
	if (targetDirection == CHARACTER_DIRECTION_NONE)
	{
		*(vScrollDir) = 0;
		*(hScrollDir) = 0;
		ptr->moved = FALSE;
		return;
	}

	u16 tileId;

	if (targetDirection & CHARACTER_DIRECTION_UP)
	{
		u8 collision = FALSE;

		// Check if the character can advance to the next tile
		// If the next tile is a collider, only advance the
		// character if it is not in a tile boundary
		tileId = collisionMap[ptr->tile_x + collisionMapWidth * (ptr->tile_y - 1)];
		if (tileId != 0) collision = TRUE;

		if (ptr->position_y == CHARACTER_SCROLL_UP_LIMIT)
		{
			// Does the next step lead to the next tile?
			if (ptr->temp_y - 1 == -8)
			{
				// Only move if the next tile is not a collider
				if (!collision)
				{
					ptr->temp_y = 0;
					ptr->tile_y--;
					ptr->moved = TRUE;
					ptr->last_direction = CHARACTER_ANIMATION_UP;
					*(vScrollDir) = -1;
				}
				else
				{
					*(vScrollDir) = 0;
				}
			}
			else
			{
				// Move normally
				ptr->temp_y--;
				ptr->moved = TRUE;
				ptr->last_direction = CHARACTER_ANIMATION_UP;
				*(vScrollDir) = -1;
			}
		}
		else
		{
			// Does the next step lead to the next tile?
            if (ptr->temp_y - 1 == -8)
            {
				// Only move if the next tile is not a collider
        	    if (!collision)
                {
					ptr->temp_y = 0;
					ptr->tile_y--;
					ptr->position_y--;
					ptr->last_direction = CHARACTER_ANIMATION_UP;
					ptr->moved = TRUE;
				}
			}
			else
			{
				// Move normally
				ptr->temp_y--;
				ptr->position_y--;
				ptr->last_direction = CHARACTER_ANIMATION_UP;
				ptr->moved = TRUE;
			}
		}
	}

	if (targetDirection & CHARACTER_DIRECTION_DOWN)
	{
		u8 collision = FALSE;

		// Check if the character can advance to the next tile
		// If the next tile is a collider, only advance the
		// character if it is not in a tile boundary
		tileId = collisionMap[ptr->tile_x + collisionMapWidth * (ptr->tile_y + 1)];
		if (tileId != 0) collision = TRUE;

		if (ptr->position_y == CHARACTER_SCROLL_DOWN_LIMIT)
		{
			// Does the next step lead to the next tile?
			if (ptr->temp_y + 1 == 8)
			{
				// Only move if the next tile is not a collider
				if (!collision)
				{
					ptr->temp_y = 0;
					ptr->tile_y++;
					ptr->moved = TRUE;
					ptr->last_direction = CHARACTER_ANIMATION_DOWN;
					*(vScrollDir) = 1;
				}
				else
				{
					*(vScrollDir) = 0;
				}
			}
			else
			{
				// Move normally
				ptr->temp_y++;
				ptr->moved = TRUE;
				ptr->last_direction = CHARACTER_ANIMATION_DOWN;
				*(vScrollDir) = 1;
			}
		}
		else
		{
			// Does the next step lead to the next tile?
            if (ptr->temp_y + 1 == 8)
            {
				// Only move if the next tile is not a collider
        	    if (!collision)
                {
					ptr->temp_y = 0;
					ptr->tile_y++;
					ptr->position_y++;
					ptr->last_direction = CHARACTER_ANIMATION_DOWN;
					ptr->moved = TRUE;
				}
			}
			else
			{
				// Move normally
				ptr->temp_y++;
				ptr->position_y++;
				ptr->last_direction = CHARACTER_ANIMATION_DOWN;
				ptr->moved = TRUE;
			}
		}
	}

	if (targetDirection & CHARACTER_DIRECTION_LEFT)
	{
		u8 collision = FALSE;

		// Check if the character can advance to the next tile
		// If the next tile is a collider, only advance the
		// character if it is not in a tile boundary
		tileId = collisionMap[ptr->tile_x - 1 + collisionMapWidth * ptr->tile_y];
		if (tileId != 0) collision = TRUE;

		if (ptr->position_x == CHARACTER_SCROLL_LEFT_LIMIT)
		{
			// Does the next step lead to the next tile?
			if (ptr->temp_x - 1 == -8)
			{
				// Only move if the next tile is not a collider
				if (!collision)
				{
					ptr->temp_x = 0;
					ptr->tile_x--;
					ptr->moved = TRUE;
					ptr->last_direction = CHARACTER_ANIMATION_LEFT;
					*(hScrollDir) = 1;
				}
				else
				{
					*(hScrollDir) = 0;
				}
			}
			else
			{
				// Move normally
				ptr->temp_x--;
				ptr->last_direction = CHARACTER_ANIMATION_LEFT;
				ptr->moved = TRUE;
				*(hScrollDir) = 1;
			}
		}
		else
		{
			// Does the next step lead to the next tile?
            if (ptr->temp_x - 1 == -8)
            {
				// Only move if the next tile is not a collider
                if (!collision)
                {
					ptr->temp_x = 0;
					ptr->tile_x--;
					ptr->position_x--;
					ptr->last_direction = CHARACTER_ANIMATION_LEFT;
					ptr->moved = TRUE;
				}
			}
			else
			{
				// Move normally
				ptr->temp_x--;
				ptr->position_x--;
				ptr->last_direction = CHARACTER_ANIMATION_LEFT;
				ptr->moved = TRUE;
			}
		}

		if (ptr->moved)
		{
			ptr->last_direction = CHARACTER_ANIMATION_LEFT;
			SPR_setAnim(ptr->sprite, ptr->last_direction);
		}
	}

	if (targetDirection & CHARACTER_DIRECTION_RIGHT)
	{
		u8 collision = FALSE;

		// Check if the character can advance to the next tile
		// If the next tile is a collider, only advance the
		// character if it is not in a tile boundary
		tileId = collisionMap[ptr->tile_x + 1 + collisionMapWidth * ptr->tile_y];
		if (tileId != 0) collision = TRUE;

		if (ptr->position_x == CHARACTER_SCROLL_RIGHT_LIMIT)
		{
			// Does the next step lead to the next tile?
			if (ptr->temp_x + 1 == 8)
			{
				// Only move if the next tile is not a collider
				if (!collision)
				{
					ptr->temp_x = 0;
					ptr->tile_x++;
					ptr->moved = TRUE;
					ptr->last_direction = CHARACTER_ANIMATION_RIGHT;
					*(hScrollDir) = -1;
				}
				else
				{
					*(hScrollDir) = 0;
				}
			}
			else
			{
				// Move normally
				ptr->temp_x++;
				ptr->moved = TRUE;
				ptr->last_direction = CHARACTER_ANIMATION_RIGHT;
				*(hScrollDir) = -1;
			}
		}
		else
		{
			// Does the next step lead to the next tile?
            if (ptr->temp_x + 1 == 8)
            {
				// Only move if the next tile is not a collider
        	    if (!collision)
                {
					ptr->temp_x = 0;
					ptr->tile_x++;
					ptr->position_x++;
					ptr->last_direction = CHARACTER_ANIMATION_RIGHT;
					ptr->moved = TRUE;
				}
			}
			else
			{
				// Move normally
				ptr->temp_x++;
				ptr->position_x++;
				ptr->last_direction = CHARACTER_ANIMATION_RIGHT;
				ptr->moved = TRUE;
			}
		}
	}

	// Handle the animation
	if (ptr->moved)
	{
		SPR_setAnim(ptr->sprite, ptr->last_direction);
	}
}

