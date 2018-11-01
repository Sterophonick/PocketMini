#include <libheart.h>
#include "mem.h"
#include "cpu.h"

int MinxIRQ_MasterIRQ = 0;

void MinxCPU_OnIRQHandle(uint8_t cpuflag, uint8_t shift_u)
{
	// Disable or enable master interrupt and check for interrupts
	if (shift_u) {
		MinxIRQ_MasterIRQ = 0;
	} else {
		if ((cpuflag & 0xC0) == 0xC0) MinxIRQ_MasterIRQ = 0;
		else {
			MinxIRQ_MasterIRQ = 1;
			MinxIRQ_Process();
		}
	}
}

int MinxIRQ_Create(void)
{
	// Reset
	MinxIRQ_Reset(1);

	return 1;
}

void MinxIRQ_Destroy(void)
{
}

void MinxIRQ_Reset(int hardreset)
{
	// Master IRQ enable
	MinxIRQ_MasterIRQ = 1;
	PMR_IRQ_ACT1 = 0x00;
	PMR_IRQ_ACT2 = 0x00;
	PMR_IRQ_ACT3 = 0x00;
	PMR_IRQ_ACT4 = 0x00;
}

void MinxIRQ_SetIRQ(uint8_t intr)
{
	switch(intr) {
		case 0x03: // PRC Copy Complete
			PMR_IRQ_ACT1 |= 0x80;
			break;
		case 0x04: // PRC Frame Divider Overflow
			PMR_IRQ_ACT1 |= 0x40;
			break;
		case 0x05: // Timer 2-B Underflow
			PMR_IRQ_ACT1 |= 0x20;
			break;
		case 0x06: // Timer 2-A Underflow (8-Bits only)
			PMR_IRQ_ACT1 |= 0x10;
			break;
		case 0x07: // Timer 1-B Underflow
			PMR_IRQ_ACT1 |= 0x08;
			break;
		case 0x08: // Timer 1-A Underflow (8-Bits only)
			PMR_IRQ_ACT1 |= 0x04;
			break;
		case 0x09: // Timer 3 Underflow
			PMR_IRQ_ACT1 |= 0x02;
			break;
		case 0x0A: // Timer 3 Pivot
			PMR_IRQ_ACT1 |= 0x01;
			break;
		case 0x0B: // 32 Hz
			PMR_IRQ_ACT2 |= 0x20;
			break;
		case 0x0C: //  8 Hz
			PMR_IRQ_ACT2 |= 0x10;
			break;
		case 0x0D: //  2 Hz
			PMR_IRQ_ACT2 |= 0x08;
			break;
		case 0x0E: //  1 Hz
			PMR_IRQ_ACT2 |= 0x04;
			break;
		case 0x0F: // IR Receiver
			PMR_IRQ_ACT4 |= 0x80;
			break;
		case 0x10: // Shock Sensor
			PMR_IRQ_ACT4 |= 0x40;
			break;
		case 0x13: // Cartridge Ejected
			PMR_IRQ_ACT2 |= 0x02;
			break;
		case 0x14: // Cartridge IRQ
			PMR_IRQ_ACT2 |= 0x01;
			break;
		case 0x15: // Power Key
			PMR_IRQ_ACT3 |= 0x80;
			break;
		case 0x16: // Right Key
			PMR_IRQ_ACT3 |= 0x40;
			break;
		case 0x17: // Left Key
			PMR_IRQ_ACT3 |= 0x20;
			break;
		case 0x18: // Down Key
			PMR_IRQ_ACT3 |= 0x10;
			break;
		case 0x19: // Up Key
			PMR_IRQ_ACT3 |= 0x08;
			break;
		case 0x1A: // C Key
			PMR_IRQ_ACT3 |= 0x04;
			break;
		case 0x1B: // B Key
			PMR_IRQ_ACT3 |= 0x02;
			break;
		case 0x1C: // A Key
			PMR_IRQ_ACT3 |= 0x01;
			break;
	}
	MinxIRQ_Process();
}

uint8_t MinxIRQ_ReadReg(int cpu, uint8_t reg)
{
	// 0x20 to 0x2A
	switch(reg) {
		case 0x20: // IRQ Priority 1
			return PMR_IRQ_PRI1;
		case 0x21: // IRQ Priority 2
			return PMR_IRQ_PRI2;
		case 0x22: // IRQ Priority 3
			return PMR_IRQ_PRI3 & 0x03;
		case 0x23: // IRQ Enable 1
			return PMR_IRQ_ENA1;
		case 0x24: // IRQ Enable 2
			return PMR_IRQ_ENA2 & 0x3F;
		case 0x25: // IRQ Enable 3
			return PMR_IRQ_ENA3;
		case 0x26: // IRQ Enable 4
			return PMR_IRQ_ENA4 & 0xF7;
		case 0x27: // IRQ Active 1
			return PMR_IRQ_ACT1;
		case 0x28: // IRQ Active 2
			return PMR_IRQ_ACT2 & 0x3F;
		case 0x29: // IRQ Active 3
			return PMR_IRQ_ACT3;
		case 0x2A: // IRQ Active 4
			return PMR_IRQ_ACT4 & 0xF7;
		default:   // Unused
			return 0;
	}
}

void MinxIRQ_WriteReg(int cpu, uint8_t reg, uint8_t val)
{
	// 0x20 to 0x2A
	switch(reg) {
		case 0x20: // IRQ Priority 1
			PMR_IRQ_PRI1 = val;
			MinxIRQ_Process();
			return;
		case 0x21: // IRQ Priority 2
			PMR_IRQ_PRI2 = val;
			MinxIRQ_Process();
			return;
		case 0x22: // IRQ Priority 3
			PMR_IRQ_PRI3 = val;
			MinxIRQ_Process();
			return;
		case 0x23: // IRQ Enable 1
			PMR_IRQ_ENA1 = val;
			MinxIRQ_Process();
			return;
		case 0x24: // IRQ Enable 2
			PMR_IRQ_ENA2 = val & 0x3F;
			MinxIRQ_Process();
			return;
		case 0x25: // IRQ Enable 3
			PMR_IRQ_ENA3 = val;
			MinxIRQ_Process();
			return;
		case 0x26: // IRQ Enable 4
			PMR_IRQ_ENA4 = val & 0xF7;
			MinxIRQ_Process();
			return;
		case 0x27: // IRQ Active 1
			if (cpu) PMR_IRQ_ACT1 &= ~val;
			else PMR_IRQ_ACT1 = val;
			return;
		case 0x28: // IRQ Active 2
			if (cpu) PMR_IRQ_ACT2 &= ~val;
			else PMR_IRQ_ACT2 = val & 0x3F;
			return;
		case 0x29: // IRQ Active 3
			if (cpu) PMR_IRQ_ACT3 &= ~val;
			else PMR_IRQ_ACT3 = val;
			return;
		case 0x2A: // IRQ Active 4
			if (cpu) PMR_IRQ_ACT4 &= ~val;
			else PMR_IRQ_ACT4 = val & 0xF7;
			return;
		default:   // Unused
			return;
	}
}

void MinxIRQ_Process(void)
{
	// TODO! Need to emulate the priority system... bah...
	if (!MinxIRQ_MasterIRQ) return;

	if (PMR_IRQ_PRI1 & 0xC0) {
		if ((PMR_IRQ_ENA1 & 0x80) && (PMR_IRQ_ACT1 & 0x80)) { MinxIRQ_OnIRQ(0x03); return; }
		if ((PMR_IRQ_ENA1 & 0x40) && (PMR_IRQ_ACT1 & 0x40)) { MinxIRQ_OnIRQ(0x04); return; }
	}
	if (PMR_IRQ_PRI1 & 0x30) {
		if ((PMR_IRQ_ENA1 & 0x20) && (PMR_IRQ_ACT1 & 0x20)) { MinxIRQ_OnIRQ(0x05); return; }
		if ((PMR_IRQ_ENA1 & 0x10) && (PMR_IRQ_ACT1 & 0x10)) { MinxIRQ_OnIRQ(0x06); return; }
	}
	if (PMR_IRQ_PRI1 & 0x0C) {
		if ((PMR_IRQ_ENA1 & 0x08) && (PMR_IRQ_ACT1 & 0x08)) { MinxIRQ_OnIRQ(0x07); return; }
		if ((PMR_IRQ_ENA1 & 0x04) && (PMR_IRQ_ACT1 & 0x04)) { MinxIRQ_OnIRQ(0x08); return; }
	}
	if (PMR_IRQ_PRI1 & 0x03) {
		if ((PMR_IRQ_ENA1 & 0x02) && (PMR_IRQ_ACT1 & 0x02)) { MinxIRQ_OnIRQ(0x09); return; }
		if ((PMR_IRQ_ENA1 & 0x01) && (PMR_IRQ_ACT1 & 0x01)) { MinxIRQ_OnIRQ(0x0A); return; }
	}
	if (PMR_IRQ_PRI2 & 0xC0) {
		if ((PMR_IRQ_ENA2 & 0x20) && (PMR_IRQ_ACT2 & 0x20)) { MinxIRQ_OnIRQ(0x0B); return; }
		if ((PMR_IRQ_ENA2 & 0x10) && (PMR_IRQ_ACT2 & 0x10)) { MinxIRQ_OnIRQ(0x0C); return; }
		if ((PMR_IRQ_ENA2 & 0x08) && (PMR_IRQ_ACT2 & 0x08)) { MinxIRQ_OnIRQ(0x0D); return; }
		if ((PMR_IRQ_ENA2 & 0x04) && (PMR_IRQ_ACT2 & 0x04)) { MinxIRQ_OnIRQ(0x0E); return; }
	}
	if (PMR_IRQ_PRI3 & 0x03) {
		if ((PMR_IRQ_ENA4 & 0x80) && (PMR_IRQ_ACT4 & 0x80)) { MinxIRQ_OnIRQ(0x0F); return; }
		if ((PMR_IRQ_ENA4 & 0x40) && (PMR_IRQ_ACT4 & 0x40)) { MinxIRQ_OnIRQ(0x10); return; }
	}
	if (PMR_IRQ_PRI2 & 0x30) {
		if ((PMR_IRQ_ENA2 & 0x02) && (PMR_IRQ_ACT2 & 0x02)) { MinxIRQ_OnIRQ(0x13); return; }
		if ((PMR_IRQ_ENA2 & 0x01) && (PMR_IRQ_ACT2 & 0x01)) { MinxIRQ_OnIRQ(0x14); return; }
	}
	if (PMR_IRQ_PRI2 & 0x0C) {
		if ((PMR_IRQ_ENA3 & 0x80) && (PMR_IRQ_ACT3 & 0x80)) { MinxIRQ_OnIRQ(0x15); return; }
		if ((PMR_IRQ_ENA3 & 0x40) && (PMR_IRQ_ACT3 & 0x40)) { MinxIRQ_OnIRQ(0x16); return; }
		if ((PMR_IRQ_ENA3 & 0x20) && (PMR_IRQ_ACT3 & 0x20)) { MinxIRQ_OnIRQ(0x17); return; }
		if ((PMR_IRQ_ENA3 & 0x10) && (PMR_IRQ_ACT3 & 0x10)) { MinxIRQ_OnIRQ(0x18); return; }
		if ((PMR_IRQ_ENA3 & 0x08) && (PMR_IRQ_ACT3 & 0x08)) { MinxIRQ_OnIRQ(0x19); return; }
		if ((PMR_IRQ_ENA3 & 0x04) && (PMR_IRQ_ACT3 & 0x04)) { MinxIRQ_OnIRQ(0x1A); return; }
		if ((PMR_IRQ_ENA3 & 0x02) && (PMR_IRQ_ACT3 & 0x02)) { MinxIRQ_OnIRQ(0x1B); return; }
		if ((PMR_IRQ_ENA3 & 0x01) && (PMR_IRQ_ACT3 & 0x01)) { MinxIRQ_OnIRQ(0x1C); return; }
	}
	if (PMR_IRQ_PRI2 & 0x03) {
		if ((PMR_IRQ_ENA4 & 0x04) && (PMR_IRQ_ACT4 & 0x04)) { MinxIRQ_OnIRQ(0x1D); return; }
		if ((PMR_IRQ_ENA4 & 0x02) && (PMR_IRQ_ACT4 & 0x02)) { MinxIRQ_OnIRQ(0x1E); return; }
		if ((PMR_IRQ_ENA4 & 0x01) && (PMR_IRQ_ACT4 & 0x01)) { MinxIRQ_OnIRQ(0x1F); return; }
	}
}

int MinxCPU_CallIRQ(uint8_t addr)
{
	if (minx.Status == MINX_STATUS_IRQ) return 0;
	minx.Status = MINX_STATUS_IRQ;
	minx.IRQ_Vector = addr;
	return 1;
}