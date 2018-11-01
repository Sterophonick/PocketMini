#include <libheart.h>
#include "mem.h"
#include "cpu.h"

const u8 ADD8(uint8_t A, uint8_t B)
{
	register uint8_t RES;
	minx.F &= MINX_FLAG_SAVE_NUL;
	switch (minx.F & 0x30) {
	case 0x00: // Normal
		RES = A + B;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES < A) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x80) != 0) && (((A ^ B) & 0x80) == 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 128) minx.F |= MINX_FLAG_SIGN;
		return RES & 0xFF;
	case 0x10: // BCD
		if ((uint8_t)((A & 15) + (B & 15)) >= 10) {
			RES = A + B + 6;
		} else {
			RES = A + B;
		}
		if (RES >= 0xA0) RES += 0x60;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES < A) minx.F |= MINX_FLAG_CARRY;	
		return RES & 0xFF;
	case 0x20: // Nibble
		RES = (A & 15) + (B & 15);
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x8) != 0) && (((A ^ B) & 0x8) == 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 8) minx.F |= MINX_FLAG_SIGN;
		return RES & 0x0F;
	default:   // BCD and Nibble
		if ((uint8_t)((A & 15) + (B & 15)) >= 10) {
			RES = (A & 15) + (B & 15) + 6;
		} else {
			RES = (A & 15) + (B & 15);
		}
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		return RES & 0x0F;
	}
}

const u8 ADC8(uint8_t A, uint8_t B)
{
	register uint8_t RES;
	register uint8_t CARRY = (minx.F & MINX_FLAG_CARRY) ? 1 : 0;
	minx.F &= MINX_FLAG_SAVE_NUL;
	switch (minx.F & 0x30) {
	case 0x00: // Normal
		RES = A + B + CARRY;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES < A) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x80) != 0) && (((A ^ B) & 0x80) == 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 128) minx.F |= MINX_FLAG_SIGN;
		return RES & 0xFF;
	case 0x10: // BCD
		if ((uint8_t)((A & 15) + (B & 15) + CARRY) >= 10) {
			RES = A + B + CARRY + 6;
		} else {
			RES = A + B + CARRY;
		}
		if (RES >= 0xA0) RES += 0x60;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES < A) minx.F |= MINX_FLAG_CARRY;	
		return RES & 0xFF;
	case 0x20: // Nibble
		RES = (A & 15) + (B & 15) + CARRY;
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x8) != 0) && (((A ^ B) & 0x8) == 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 8) minx.F |= MINX_FLAG_SIGN;
		return RES & 0x0F;
	default:   // BCD and Nibble
		if ((uint8_t)((A & 15) + (B & 15) + CARRY) >= 10) {
			RES = (A & 15) + (B & 15) + CARRY + 6;
		} else {
			RES = (A & 15) + (B & 15) + CARRY;
		}
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		return RES & 0x0F;
	}
}

u8 SUB8(uint8_t A, uint8_t B)
{
	register uint8_t RES;
	minx.F &= MINX_FLAG_SAVE_NUL;
	switch (minx.F & 0x30) {
	case 0x00: // Normal
		RES = A - B;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (A < B) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x80) != 0) && (((A ^ B) & 0x80) != 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 128) minx.F |= MINX_FLAG_SIGN;
		return RES & 0xFF;
	case 0x10: // BCD
		if ((uint8_t)((A & 15) - (B & 15)) >= 10) {
			RES = A - B - 6;
		} else {
			RES = A - B;
		}
		if (RES >= 0xA0) RES -= 0x60;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (A < B) minx.F |= MINX_FLAG_CARRY;	
		return RES & 0xFF;
	case 0x20: // Nibble
		RES = (A & 15) - (B & 15);
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x8) != 0) && (((A ^ B) & 0x8) != 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 8) minx.F |= MINX_FLAG_SIGN;
		return RES & 0x0F;
	default:   // BCD and Nibble
		if ((uint8_t)((A & 15) - (B & 15)) >= 10) {
			RES = (A & 15) - (B & 15) - 6;
		} else {
			RES = (A & 15) - (B & 15);
		}
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		return RES & 0x0F;
	}
}

u8 SBC8(uint8_t A, uint8_t B)
{
	register uint8_t RES;
	register uint8_t CARRY = (minx.F & MINX_FLAG_CARRY) ? 1 : 0;
	minx.F &= MINX_FLAG_SAVE_NUL;
	switch (minx.F & 0x30) {
	case 0x00: // Normal
		RES = A - B - CARRY;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (A < B) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x80) != 0) && (((A ^ B) & 0x80) != 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 128) minx.F |= MINX_FLAG_SIGN;
		return RES & 0xFF;
	case 0x10: // BCD
		if ((uint8_t)((A & 15) - (B & 15) - CARRY) >= 10) {
			RES = A - B - CARRY - 6;
		} else {
			RES = A - B - CARRY;
		}
		if (RES >= 0xA0) RES -= 0x60;
		if (RES == 0) minx.F |= MINX_FLAG_ZERO;
		if (A < B) minx.F |= MINX_FLAG_CARRY;	
		return RES & 0xFF;
	case 0x20: // Nibble
		RES = (A & 15) - (B & 15) - CARRY;
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		if ((((A ^ RES) & 0x8) != 0) && (((A ^ B) & 0x8) != 0)) minx.F |= MINX_FLAG_OVERFLOW;
		if (RES & 8) minx.F |= MINX_FLAG_SIGN;
		return RES & 0x0F;
	default:   // BCD and Nibble
		if ((uint8_t)((A & 15) - (B & 15) - CARRY) >= 10) {
			RES = (A & 15) - (B & 15) - CARRY - 6;
		} else {
			RES = (A & 15) - (B & 15) - CARRY;
		}
		if ((RES & 15) == 0) minx.F |= MINX_FLAG_ZERO;
		if (RES >= 16) minx.F |= MINX_FLAG_CARRY;
		return RES & 0x0F;
	}
}

u8 OR8(uint8_t A, uint8_t B)
{
	A |= B;
	minx.F &= MINX_FLAG_SAVE_CO;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 128) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 AND8(uint8_t A, uint8_t B)
{
	A &= B;
	minx.F &= MINX_FLAG_SAVE_CO;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 128) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 XOR8(uint8_t A, uint8_t B)
{
	A ^= B;
	minx.F &= MINX_FLAG_SAVE_CO;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 128) minx.F |= MINX_FLAG_SIGN;
	return A;
}

void JMPS(uint16_t OFFSET)
{
	minx.PC.B._I = minx.U1;
	minx.U2 = minx.U1;
	minx.PC.W.L = minx.PC.W.L + OFFSET - 1;
}

void JMPU(uint16_t ADDR)
{
	minx.PC.B._I = minx.U1;
	minx.U2 = minx.U1;
	minx.PC.W.L = ADDR;
}

u8 SWAP(uint8_t A)
{
	return (A << 4) | (A >> 4);
}

u8 POP(void)
{
	register uint8_t data;
	data = MinxCPU_OnRead(1, minx.SP.D);
	minx.SP.W.L++;
	return data;
}
void PUSH(uint8_t A)
{
	minx.SP.W.L--;
	//MinxCPU_OnWrite(1, minx.SP.D, A);
}

u8 Fetch8(void)
{
	if (minx.PC.W.L & 0x8000) {
		// Banked area
		minx.IR = MinxCPU_OnRead(1, (minx.PC.W.L++ & 0x7FFF) | (minx.PC.B._I << 15));
	} else {
		// Unbanked area
		minx.IR = MinxCPU_OnRead(1, minx.PC.W.L++);
	}
	return minx.IR;
}

u16 Fetch16(void)
{
	uint8_t LB = Fetch8();
	return (Fetch8() << 8) | LB;
}

void CALLS(uint16_t OFFSET)
{
	PUSH(minx.PC.B._I);
	PUSH(minx.PC.B.H);
	PUSH(minx.PC.B.L);
	minx.PC.B._I = minx.U1;
	minx.U2 = minx.U1;
	minx.PC.W.L = minx.PC.W.L + OFFSET - 1;
}

u16 S8_TO_16(int8_t a)
{
	return (a & 0x80) ? (0xFF00 | a) : a;
}

u8 DEC8(uint8_t A)
{
	A--;
	minx.F &= MINX_FLAG_SAVE_COS;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	return A;
}

u16 DEC16(uint16_t A)
{
	A--;
	minx.F &= MINX_FLAG_SAVE_COS;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	return A;
}

u8 INC8(uint8_t A)
{
	A++;
	minx.F &= MINX_FLAG_SAVE_COS;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	return A;
}

u16 INC16(uint16_t A)
{
	A++;
	minx.F &= MINX_FLAG_SAVE_COS;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	return A;
}

u16 SUB16(uint16_t A, uint16_t B)
{
	register uint16_t RES;
	RES = A - B;
	minx.F &= MINX_FLAG_SAVE_NUL;
	if (RES == 0) minx.F |= MINX_FLAG_ZERO;
	if (A < B) minx.F |= MINX_FLAG_CARRY;
	if ((((A ^ RES) & 0x8000) != 0) && (((A ^ B) & 0x8000) != 0)) minx.F |= MINX_FLAG_OVERFLOW;
	if (RES & 0x8000) minx.F |= MINX_FLAG_SIGN;
	return (uint16_t)RES;
}

void MUL(void)
{
	minx.F &= MINX_FLAG_SAVE_NUL;
	minx.HL.W.L = (uint16_t)minx.HL.B.L * (uint16_t)minx.BA.B.L;
	if (minx.HL.W.L == 0) minx.F |= MINX_FLAG_ZERO;
	if (minx.HL.W.L & 0x8000) minx.F |= MINX_FLAG_SIGN;
}

void DIV(void)
{
	uint16_t RES;
	minx.F &= MINX_FLAG_SAVE_NUL;
	if (minx.BA.B.L == 0) {
		//MinxCPU_OnException(EXCEPTION_DIVISION_BY_ZERO, 0);
		return;
	}
	RES = minx.HL.W.L / minx.BA.B.L;
	if (RES < 256) {
		minx.HL.B.H = minx.HL.W.L % minx.BA.B.L;
		minx.HL.B.L = (uint8_t)RES;
		if (minx.HL.B.L == 0) minx.F |= MINX_FLAG_ZERO;
		if (minx.HL.B.L & 0x80) minx.F |= MINX_FLAG_SIGN;
	} else minx.F |= (MINX_FLAG_OVERFLOW | MINX_FLAG_SIGN);
}

void Set_U(uint8_t val)
{
	if (val != minx.U2) minx.Shift_U = 2;
	minx.U1 = val;
	minx.U2 = minx.U1;
	//MinxCPU_OnIRQHandle(minx.F, minx.Shift_U);
}

void STOP(void)
{
	minx.Status = MINX_STATUS_STOP;
	//MinxCPU_OnSleep(MINX_SLEEP_STOP);
}

void HALT(void)
{
	minx.Status = MINX_STATUS_HALT;
	//MinxCPU_OnSleep(MINX_SLEEP_HALT);
}

u16 ADD16(uint16_t A, uint16_t B)
{
	register uint16_t RES;
	RES = A + B;
	minx.F &= MINX_FLAG_SAVE_NUL;
	if (RES == 0) minx.F |= MINX_FLAG_ZERO;
	if (RES < A) minx.F |= MINX_FLAG_CARRY;
	if ((((A ^ RES) & 0x8000) != 0) && (((A ^ B) & 0x8000) == 0)) minx.F |= MINX_FLAG_OVERFLOW;
	if (RES & 0x8000) minx.F |= MINX_FLAG_SIGN;
	return (uint16_t)RES;
}

u16 ADC16(uint16_t A, uint16_t B)
{
	register uint16_t RES;
	RES = A + B + ((minx.F & MINX_FLAG_CARRY) ? 1 : 0);
	minx.F &= MINX_FLAG_SAVE_NUL;
	if (RES == 0) minx.F |= MINX_FLAG_ZERO;
	if (RES < A) minx.F |= MINX_FLAG_CARRY;
	if ((((A ^ RES) & 0x8000) != 0) && (((A ^ B) & 0x8000) == 0)) minx.F |= MINX_FLAG_OVERFLOW;
	if (RES & 0x8000) minx.F |= MINX_FLAG_SIGN;
	return (uint16_t)RES;
}

u8 SAL(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_NUL;
	if (A & 0x80) minx.F |= MINX_FLAG_CARRY;
	if ((!(A & 0x40)) != (!(A & 0x80))) minx.F |= MINX_FLAG_OVERFLOW;
	A = A << 1;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 SHL(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_O;
	if (A & 0x80) minx.F |= MINX_FLAG_CARRY;
	A = A << 1;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 SAR(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_NUL;
	if (A & 0x01) minx.F |= MINX_FLAG_CARRY;
	A = (A & 0x80) | (A >> 1);
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 SHR(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_O;
	if (A & 0x01) minx.F |= MINX_FLAG_CARRY;
	A = A >> 1;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 ROLC(uint8_t A)
{
	register uint8_t CARRY = (minx.F & MINX_FLAG_CARRY) ? 1 : 0;
	minx.F &= MINX_FLAG_SAVE_O;
	if (A & 0x80) minx.F |= MINX_FLAG_CARRY;
	A = (A << 1) | CARRY;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 ROL(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_O;
	if (A & 0x80) minx.F |= MINX_FLAG_CARRY;
	A = (A << 1) | (A >> 7);
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 RORC(uint8_t A)
{
	register uint8_t CARRY = (minx.F & MINX_FLAG_CARRY) ? 0x80 : 0x00;
	minx.F &= MINX_FLAG_SAVE_O;
	if (A & 0x01) minx.F |= MINX_FLAG_CARRY;
	A = (A >> 1) | CARRY;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 ROR(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_O;
	if (A & 0x01) minx.F |= MINX_FLAG_CARRY;
	A = (A >> 1) | (A << 7);
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u8 MNOT(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_CO;
	A = A ^ 0xFF;
	if (A == 0) minx.F |= MINX_FLAG_ZERO;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;	
}

u8 NEG(uint8_t A)
{
	minx.F &= MINX_FLAG_SAVE_NUL;
	A = -A;
	if (A == 0) minx.F |= MINX_FLAG_ZERO; else minx.F |= MINX_FLAG_CARRY;
	if (A == 0x80) minx.F |= MINX_FLAG_OVERFLOW;
	if (A & 0x80) minx.F |= MINX_FLAG_SIGN;
	return A;
}

u16 SBC16(uint16_t A, uint16_t B)
{
	register uint16_t RES;
	RES = A - B - ((minx.F & MINX_FLAG_CARRY) ? 1 : 0);
	minx.F &= MINX_FLAG_SAVE_NUL;
	if (RES == 0) minx.F |= MINX_FLAG_ZERO;
	if (A < B) minx.F |= MINX_FLAG_CARRY;
	if ((((A ^ RES) & 0x8000) != 0) && (((A ^ B) & 0x8000) != 0)) minx.F |= MINX_FLAG_OVERFLOW;
	if (RES & 0x8000) minx.F |= MINX_FLAG_SIGN;
	return (uint16_t)RES;
}