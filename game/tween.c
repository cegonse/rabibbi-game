#include "tween.h"

static tween_state_t tween_state;
static const fix16 th = FIX16(3.0);
static const fix16 tw = FIX16(2.0);
static const fix16 one = FIX16(1.0);

//-------------------------------------------------------------

void tween_init()
{
	memset(&tween_state, 0, sizeof(tween_state_t));

	for (u8 i = 0; i < MAX_TWEENS; ++i)
	{
		tween_state.tweens[i].id = -1;
	}
}

//-------------------------------------------------------------

tween_t* do_tween(u8 tweenType, fix16 *value, u16 frames, s8 id, fix16 from, fix16 to, tween_finished_callback_t finishedCallback)
{
	tween_t *tw = NULL;

	// Return early if the tweening queue is full	
	if (tween_state.count == MAX_TWEENS) return tw;

	// Get the first tween available from the list and initialize
	for (u8 i = 0; i < MAX_TWEENS; ++i)
	{
		if (tween_state.tweens[i].id == -1)
		{
			tw = &tween_state.tweens[i];
			tween_state.count++;
			break;
		}
	}

	tw->type = tweenType;
	tw->id = id;
	tw->from = from;
	tw->to = to;
	tw->value = value;
	tw->frames = frames;
	
	tw->current_frame = 0;
	tw->finish_callback = finishedCallback;
	
	return tw;
}

//-------------------------------------------------------------

void tween_smoothstep(fix16 *x)
{
	// x = ((x) * (x) * (3 - 2 * (x)))
	fix16 v = *x, y = FIX16(0.0);
	*x = fix16Mul(v,v);
	y = th - fix16Mul(tw, v);
	*x = fix16Mul(*x, y);
}

//-------------------------------------------------------------

void tween_update()
{
	tween_t *curr = NULL;

	// Return early if there are no active tweens
	if (tween_state.count == 0) return;

	// Cycle through all the tweens and update them
	for (u8 i = 0; i < tween_state.count; ++i)
	{
		if (tween_state.tweens[i].id != -1)
		{
			curr = &tween_state.tweens[i];
			curr->current_frame++;

			fix16 v = fix16Div(intToFix16(curr->current_frame), intToFix16(curr->frames));

			// Update the tweened value
			if (curr->type == TWEEN_SMOOTH)
			{
				tween_smoothstep(&v);
			}

			// (A * v) + (B * (1 - v))
			*(curr->value) = fix16Mul(curr->to, v) + fix16Mul(curr->from, one - v);

			// If the tween has reached the final value, remove and call
			// the finish callback
			if (*(curr->value) >= curr->to)
			{
				u8 id = curr->id;
				tween_state.count--;

				curr->id = -1;

				if (curr->finish_callback != NULL)
				{
					curr->finish_callback(id);
				}
			}
		}
	}
}

