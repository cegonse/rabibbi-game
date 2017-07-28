#include "init.h"


//-------------------------------------------------------------

void system_init()
{
	SYSTEM_GPU_SAFE
	(
		// Init the sprite engine
		SPR_init(16,256,256);

		// For debugging purposes
		VDP_setTextPlan(PLAN_B);
	)
}

