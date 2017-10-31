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
		// Init the sprite engine with the default VRAM
		// allocation sizes
		SPR_init(0,0,0);

		// For debugging purposes
		VDP_setTextPlan(PLAN_B);

		// Set the scrolling mode
		VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

		// Set the tilemap size
		VDP_setPlanSize(64, 64);

		// Set the appropriate delta time
		if (IS_PALSYSTEM)
		{
			DELTA_TIME = PAL_DELTA_TIME;
			VDP_setScreenWidth320();
			VDP_setScreenHeight240();
		}
		else
		{
			DELTA_TIME = NTSC_DELTA_TIME;
			VDP_setScreenWidth320();
			VDP_setScreenHeight224();
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
