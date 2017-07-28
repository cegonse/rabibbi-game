#ifndef _TWEEN_H_
#define _TWEEN_H_

#include <genesis.h>

#define TWEEN_LINEAR	0
#define TWEEN_SMOOTH	1
#define MAX_TWEENS		64

typedef void (*tween_finished_callback_t)(s8);

typedef struct tween
{
	s8 id;
	fix16 *value;
	fix16 from;
	fix16 to;
	u16 frames;
	u16 current_frame;
	u8 type;

	tween_finished_callback_t finish_callback;
} tween_t;

typedef struct tween_state
{
	tween_t tweens[MAX_TWEENS];
	u8 count;
} tween_state_t;

void tween_init();
tween_t* do_tween(u8 tweenType, fix16 *value, u16 frames, s8 id, fix16 from, fix16 to, tween_finished_callback_t finishedCallback);
void tween_update();
void tween_smoothstep(fix16 *x);

#endif // _TWEEN_H_
