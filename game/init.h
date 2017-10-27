#ifndef _INIT_H_
#define _INIT_H_

#include <genesis.h>

#define SYSTEM_GPU_SAFE(x)	do \
							{ \
								SYS_disableInts(); \
								x \
								SYS_enableInts(); \
							} while(0);

void system_init();
void system_endFrame();

#endif // _INIT_H_
