#include <libheart.h>
#include "cpu.h"
#include "mem.h"

#define PM_CYCLE_LIMIT 

u32 pc HRT_EWRAM_DATA;

int main()
{
	hrt_Init();
	hrt_InitTiledText(2);
	MinxIRQ_Create();
	hrt_DSPSetBGMode(0);
	hrt_DSPEnableBG(2);
	hrt_DSPDisableForceBlank();
	MinxMMIO[256] = 0xFF;
	u32 cycles;
	while(1)
	{
		hrt_VblankIntrWait();
		GetKeypad();
		MergeKeyData();
		cycles+=CPU();
		if(keyDown(KEY_R))
		{
			if(keyDown(KEY_L)) menu();
		}
	}
	return 0;
}