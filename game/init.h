#ifndef _INIT_H_
#define _INIT_H_

#include <genesis.h>

#define SYSTEM_GPU_SAFE(x)	do \
							{ \
								SYS_disableInts(); \
								x \
								SYS_enableInts(); \
							} while(0);

#define CONTROLLER_STATE_NONE		0
#define CONTROLLER_STATE_ONE_3BTN	1
#define CONTROLLER_STATE_ONE_6BTN	2
#define CONTROLLER_STATE_TWO_3BTN	4
#define CONTROLLER_STATE_TWO_6BTN	8

void system_init(u8 *controller);
void system_endFrame();

#endif // _INIT_H_
