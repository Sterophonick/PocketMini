#include <libheart.h>
#include "mem.h"
#include "cpu.h"
#include "lang.h"

void MinxCPU_OnException(int type, uint32_t ir)
{
	hrt_ClearTiledText();
	switch (type) {
		case EXCEPTION_UNKNOWN_INSTRUCTION:
				hrt_PrintOnTilemap(0, 0, (char*)gl_exception_types[0]);
		case EXCEPTION_CRASH_INSTRUCTION:
			hrt_PrintOnTilemap(0, 0, (char*)gl_exception_types[1]);
		case EXCEPTION_UNSTABLE_INSTRUCTION:
			hrt_PrintOnTilemap(0, 0, (char*)gl_exception_types[2]);
		case EXCEPTION_DIVISION_BY_ZERO:
			hrt_PrintOnTilemap(0, 0, (char*)gl_exception_types[3]);
		default:
			return;
	}
	while(1)
	{
		hrt_VblankIntrWait();
	}
}