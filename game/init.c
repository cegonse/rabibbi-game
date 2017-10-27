#include "init.h"

static const fix16 NTSC_DELTA_TIME = FIX16(0.17);
static const fix16 PAL_DELTA_TIME = FIX16(0.02);
static fix16 DELTA_TIME;
fix16 *dt;

//-------------------------------------------------------------

void system_init()
{
	SYSTEM_GPU_SAFE
	(
		// Init the sprite engine
		SPR_init(0,0,0);

		// For debugging purposes
		VDP_setTextPlan(PLAN_B);

		// Set the appropriate delta time
		if (IS_PALSYSTEM)
		{
			DELTA_TIME = PAL_DELTA_TIME;
		}
		else
		{
			DELTA_TIME = NTSC_DELTA_TIME;
		}

		dt = &DELTA_TIME;
	)
}

//-------------------------------------------------------------

void system_endFrame()
{
	// Draw and wait for VBlank
	SPR_update();
	VDP_waitVSync();
}
