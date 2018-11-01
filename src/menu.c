#include <libheart.h>
#include "mem.h"
#include "cpu.h"
#include "lang.h"

void menu()
{
	hrt_ClearTiledText();
	u8 returns[3];
	u8 disploop;
	u8 arpos;
	REG_BG2VOFS = 160;
	for(disploop = 0; disploop < 8; disploop++)
	{
		hrt_PrintOnTilemap(1, 7+disploop, (char*)gl_main_menu_options[disploop]);
	}
	hrt_PrintOnTilemap(0, 19, (char*)gl_credit_ln0);
	hrt_PrintOnTilemap(0, 20, (char*)gl_credit_ln1);
	for(disploop = 0; disploop < 266-166; disploop+=2)
	{
		REG_BG2VOFS = disploop+166;
		hrt_VblankIntrWait();
	}
	
	arpos = 0;
	while(!(keyDown(KEY_B)))
	{
		hrt_VblankIntrWait();
		hrt_PrintOnTilemap(0, 7+arpos, "*");
		if(keyDown(KEY_DOWN))
		{
			hrt_PrintOnTilemap(0, 7+arpos, " ");
			if(!(arpos > 5))
			{
				arpos++;
			}
			hrt_PrintOnTilemap(0, 7+arpos, "*");
			while(keyDown(KEY_DOWN))
			{
				hrt_VblankIntrWait();
			}
		}
		if(keyDown(KEY_UP))
		{
			hrt_PrintOnTilemap(0, 7+arpos, " ");
			if(arpos > 0)
			{
				arpos--;
			}
			hrt_PrintOnTilemap(0, 7+arpos, "*");
			while(keyDown(KEY_UP))
			{
				hrt_VblankIntrWait();
			}
		}
		if(keyDown(KEY_A))
		{
			if(arpos == 0)
			{
				for(disploop = 264; disploop < 160; disploop-=2)
				{
					REG_BG2VOFS = disploop;
					hrt_VblankIntrWait();
				}
			}
			if(arpos == 6)
			{
				hrt_EZ4Exit();
			}
		}
	}
}