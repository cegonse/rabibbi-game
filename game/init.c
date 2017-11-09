#include "init.h"


//-------------------------------------------------------------

void system_init(u8 *controller)
{
	u8 joyState1, joyState2;

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
			VDP_setScreenWidth320();
			VDP_setScreenHeight240();
		}
		else
		{
			VDP_setScreenWidth320();
			VDP_setScreenHeight224();
		}

		// Detect connected controllers
		joyState1 = JOY_getJoypadType(PORT_1);
		joyState2 = JOY_getJoypadType(PORT_2);

		if (joyState1 == JOY_TYPE_PAD3)
		{
			*controller |= CONTROLLER_STATE_ONE_3BTN;
		}
		else if (joyState1 == JOY_TYPE_PAD6)
		{
			*controller |= CONTROLLER_STATE_ONE_6BTN;
		}

		if (joyState2 == JOY_TYPE_PAD3)
		{
			*controller |= CONTROLLER_STATE_TWO_3BTN;
		}
		else if (joyState2 == JOY_TYPE_PAD6)
		{
			*controller |= CONTROLLER_STATE_TWO_6BTN;
		}
	)
}

//-------------------------------------------------------------

void system_endFrame()
{
	// Draw and wait for VBlank
	SPR_update();
	VDP_waitVSync();
}
