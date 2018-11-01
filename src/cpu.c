#include <libheart.h>
#include "mem.h"
#include "cpu.h"
TMinxCPU minx HRT_EWRAM_DATA;;

extern u32 pc;

int CPUCE();
int CPUCF();
int CPUSPCE(void);
int CPUSPCF(void);

/* decides what to do for each instruction */

int CPU()
{
	uint8_t I8A, I8B;
	uint16_t I16;
		pc++;
	switch(MinxROM[pc-1])
	{
		case 0: //ADD A, A
			minx.BA.B.L = ADD8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 1: //add a, b
			minx.BA.B.L = ADD8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 2: //add a, #nn
			I8A = Fetch8();
			minx.BA.B.L = ADD8(minx.BA.B.L, I8A);
			return 8;
		case 3: //add a, [hl]
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 4: //add a, [n+#nn]
			I8A = Fetch8();
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 5: //add a, [#nnnn]
			I16 = Fetch16();
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 6: //add a, [x]
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 7: //add a, [y]
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		case 0x08: // ADC A, A
			minx.BA.B.L = ADC8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 0x09: // ADC A, B
			minx.BA.B.L = ADC8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x0A:
			I8A = Fetch8();
			minx.BA.B.L = ADC8(minx.BA.B.L, I8A);
			return 8;
		case 0x0B: // ADC A, [HL]
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 0x0C:
			I8A = Fetch8();
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 0x0D:
			I16 = Fetch16();
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 0x0E: // ADC A, [X]
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 0x0F: // ADC A, [Y]
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		case 0x10: // SUB A, A
			minx.BA.B.L = SUB8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 0x11: // SUB A, B
			minx.BA.B.L = SUB8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x12: //sub a, #nn
			I8A = Fetch8();
			minx.BA.B.L = SUB8(minx.BA.B.L, I8A);
			return 8;
		case 0x13: // SUB A, [HL]
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 0x14:
			I8A = Fetch8();
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 0x15:
			I16 = Fetch16();
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 0x16: // SUB A, [X]
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 0x17: // SUB A, [Y]
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		case 0x18: // SBC A, A
			minx.BA.B.L = SBC8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 0x19: // SBC A, B
			minx.BA.B.L = SBC8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x1A:
			I8A = Fetch8();
			minx.BA.B.L = SBC8(minx.BA.B.L, I8A);
			return 8;
		case 0x1B: // SBC A, [HL]
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 0x1C:
			I8A = Fetch8();
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 0x1D:
			I16 = Fetch16();
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 0x1E: // SBC A, [X]
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 0x1F: // SBC A, [Y]
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		case 0x20: // AND A, A
			minx.BA.B.L = AND8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 0x21: // AND A, B
			minx.BA.B.L = AND8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x22:
			I8A = Fetch8();
			minx.BA.B.L = AND8(minx.BA.B.L, I8A);
			return 8;
		case 0x23: // AND A, [HL]
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 0x24:
			I8A = Fetch8();
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 0x25:
			I16 = Fetch16();
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 0x26: // AND A, [X]
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 0x27: // AND A, [Y]
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		case 0x28: // OR A, A
			minx.BA.B.L = OR8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 0x29: // OR A, B
			minx.BA.B.L = OR8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x2A:
			I8A = Fetch8();
			minx.BA.B.L = OR8(minx.BA.B.L, I8A);
			return 8;
		case 0x2B: // OR A, [HL]
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 0x2C:
			I8A = Fetch8();
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 0x2D:
			I16 = Fetch16();
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 0x2E: // OR A, [X]
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 0x2F: // OR A, [Y]
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		case 0x30: // CMP A, A
			SUB8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 0x31: // CMP A, B
			SUB8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x32:
			I8A = Fetch8();
			SUB8(minx.BA.B.L, I8A);
			return 8;
		case 0x33: // CMP A, [HL]
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 0x34:
			I8A = Fetch8();
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 0x35:
			I16 = Fetch16();
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 0x36: // CMP A, [X]
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 0x37: // CMP A, [Y]
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		case 0x38: // XOR A, A
			minx.BA.B.L = XOR8(minx.BA.B.L, minx.BA.B.L);
			return 8;
		case 0x39: // XOR A, B
			minx.BA.B.L = XOR8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x3A:
			I8A = Fetch8();
			minx.BA.B.L = XOR8(minx.BA.B.L, I8A);
			return 8;
		case 0x3B: // XOR A, [HL]
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.HL.D));
			return 8;
		case 0x3C:
			I8A = Fetch8();
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 12;
		case 0x3D:
			I16 = Fetch16();
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16));
			return 16;
		case 0x3E: // XOR A, [X]
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.X.D));
			return 8;
		case 0x3F: // XOR A, [Y]
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, minx.Y.D));
			return 8;
		
		case 0x40: //MOV A,A
			return 4;
		case 0x41: //MOV A, B
			minx.BA.B.L = minx.BA.B.H;
			return 4;
		case 0x42: // MOV A, L
			minx.BA.B.L = minx.HL.B.L;
			return 4;
		case 0x43: // MOV A, H
			minx.BA.B.L = minx.HL.B.H;
			return 4;
		case 0x44: // MOV A, [N+#nn]
			I8A = Fetch8();
			minx.BA.B.L = MinxCPU_OnRead(1, minx.N.D + I8A);
			return 12;
		case 0x45: // MOV A, [HL]
			minx.BA.B.L = MinxCPU_OnRead(1, minx.HL.D);
			return 8;
		case 0x46: // MOV A, [X]
			minx.BA.B.L = MinxCPU_OnRead(1, minx.X.D);
			return 8;
		case 0x47: // MOV A, [Y]
			minx.BA.B.L = MinxCPU_OnRead(1, minx.Y.D);
			return 8;	
		case 0x48: // MOV B, A
			minx.BA.B.H = minx.BA.B.L;
			return 4;
		case 0x49: // MOV B, B
			return 4;
		case 0x4A: // MOV B, L
			minx.BA.B.H = minx.HL.B.L;
			return 4;
		case 0x4B: // MOV B, H
			minx.BA.B.H = minx.HL.B.H;
			return 4;
		case 0x4C: // MOV B, [N+#nn]
			I8A = Fetch8();
			minx.BA.B.H = MinxCPU_OnRead(1, minx.N.D + I8A);
			return 12;
		case 0x4D: // MOV B, [HL]
			minx.BA.B.H = MinxCPU_OnRead(1, minx.HL.D);
			return 8;
		case 0x4E: // MOV B, [X]
			minx.BA.B.H = MinxCPU_OnRead(1, minx.X.D);
			return 8;
		case 0x4F: // MOV B, [Y]
			minx.BA.B.H = MinxCPU_OnRead(1, minx.Y.D);
			return 8;
		case 0x50: // MOV L, A
			minx.HL.B.L = minx.BA.B.L;
			return 4;
		case 0x51: // MOV L, B
			minx.HL.B.L = minx.BA.B.H;
			return 4;
		case 0x52: // MOV L, L
			return 4;
		case 0x53: // MOV L, H
			minx.HL.B.L = minx.HL.B.H;
			return 4;
		case 0x54: // MOV L, [N+#nn]
			I8A = Fetch8();
			minx.HL.B.L = MinxCPU_OnRead(1, minx.N.D + I8A);
			return 12;
		case 0x55: // MOV L, [HL]
			minx.HL.B.L = MinxCPU_OnRead(1, minx.HL.D);
			return 8;
		case 0x56: // MOV L, [X]
			minx.HL.B.L = MinxCPU_OnRead(1, minx.X.D);
			return 8;
		case 0x57: // MOV L, [Y]
			minx.HL.B.L = MinxCPU_OnRead(1, minx.Y.D);
			return 8;
		case 0x58: // MOV H, A
			minx.HL.B.H = minx.BA.B.L;
			return 4;
		case 0x59: // MOV H, B
			minx.HL.B.H = minx.BA.B.H;
			return 4;
		case 0x5A: // MOV H, L
			minx.HL.B.H = minx.HL.B.L;
			return 4;
		case 0x5B: // MOV H, H
			return 4;
		case 0x5C: // MOV H, [N+#nn]
			I8A = Fetch8();
			minx.HL.B.H = MinxCPU_OnRead(1, minx.N.D + I8A);
			return 12;
		case 0x5D: // MOV H, [HL]
			minx.HL.B.H = MinxCPU_OnRead(1, minx.HL.D);
			return 8;
		case 0x5E: // MOV H, [X]
			minx.HL.B.H = MinxCPU_OnRead(1, minx.X.D);
			return 8;
		case 0x5F: // MOV H, [Y]
			minx.HL.B.H = MinxCPU_OnRead(1, minx.Y.D);
			return 8;
		case 0x60: // MOV [X], A
			MinxCPU_OnWrite(1, minx.X.D, minx.BA.B.L);
			return 8;
		case 0x61: // MOV [X], B
			MinxCPU_OnWrite(1, minx.X.D, minx.BA.B.H);
			return 8;
		case 0x62: // MOV [X], L
			MinxCPU_OnWrite(1, minx.X.D, minx.HL.B.L);
			return 8;
		case 0x63: // MOV [X], H
			MinxCPU_OnWrite(1, minx.X.D, minx.HL.B.H);
			return 8;
		case 0x64: // MOV [X], [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 16;
		case 0x65: // MOV [X], [HL]
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, minx.HL.D));
			return 12;
		case 0x66: // MOV [X], [X]
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, minx.X.D));
			return 12;
		case 0x67: // MOV [X], [Y]
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, minx.Y.D));
			return 12;

		case 0x68: // MOV [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, minx.BA.B.L);
			return 8;
		case 0x69: // MOV [HL], B
			MinxCPU_OnWrite(1, minx.HL.D, minx.BA.B.H);
			return 8;
		case 0x6A: // MOV [HL], L
			MinxCPU_OnWrite(1, minx.HL.D, minx.HL.B.L);
			return 8;
		case 0x6B: // MOV [HL], H
			MinxCPU_OnWrite(1, minx.HL.D, minx.HL.B.H);
			return 8;
		case 0x6C: // MOV [HL], [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 16;
		case 0x6D: // MOV [HL], [HL]
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, minx.HL.D));
			return 12;
		case 0x6E: // MOV [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, minx.X.D));
			return 12;
		case 0x6F: // MOV [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, minx.Y.D));
			return 12;

		case 0x70: // MOV [Y], A
			MinxCPU_OnWrite(1, minx.Y.D, minx.BA.B.L);
			return 8;
		case 0x71: // MOV [Y], B
			MinxCPU_OnWrite(1, minx.Y.D, minx.BA.B.H);
			return 8;
		case 0x72: // MOV [Y], L
			MinxCPU_OnWrite(1, minx.Y.D, minx.HL.B.L);
			return 8;
		case 0x73: // MOV [Y], H
			MinxCPU_OnWrite(1, minx.Y.D, minx.HL.B.H);
			return 8;
		case 0x74: // MOV [Y], [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, minx.N.D + I8A));
			return 16;
		case 0x75: // MOV [Y], [HL]
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, minx.HL.D));
			return 12;
		case 0x76: // MOV [Y], [X]
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, minx.X.D));
			return 12;
		case 0x77: // MOV [Y], [Y]
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, minx.Y.D));
			return 12;

		case 0x78: // MOV [N+#nn], A
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, minx.BA.B.L);
			return 8;
		case 0x79: // MOV [N+#nn], B
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, minx.BA.B.H);
			return 8;
		case 0x7A: // MOV [N+#nn], L
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, minx.HL.B.L);
			return 8;
		case 0x7B: // MOV [N+#nn], H
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, minx.HL.B.H);
			return 8;
		case 0x7C: // NOTHING #nn
			I8A = Fetch8();
			return 64;
		case 0x7D: // MOV [N+#nn], [HL]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, MinxCPU_OnRead(1, minx.HL.D));
			return 16;
		case 0x7E: // MOV [N+#nn], [X]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, MinxCPU_OnRead(1, minx.X.D));
			return 16;
		case 0x7F: // MOV [N+#nn], [Y]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, MinxCPU_OnRead(1, minx.Y.D));
			return 16;

		case 0x80: // INC A
			minx.BA.B.L = INC8(minx.BA.B.L);
			return 8;
		case 0x81: // INC B
			minx.BA.B.H = INC8(minx.BA.B.H);
			return 8;
		case 0x82: // INC L
			minx.HL.B.L = INC8(minx.HL.B.L);
			return 8;
		case 0x83: // INC H
			minx.HL.B.H = INC8(minx.HL.B.H);
			return 8;
		case 0x84: // INC N
			minx.N.B.H = INC8(minx.N.B.H);
			return 8;
		case 0x85: // INC [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, INC8(MinxCPU_OnRead(1, minx.N.D + I8A)));
			return 16;
		case 0x86: // INC [HL]
			MinxCPU_OnWrite(1, minx.HL.D, INC8(MinxCPU_OnRead(1, minx.HL.D)));
			return 12;
		case 0x87: // INC SP
			minx.SP.W.L = INC16(minx.SP.W.L);
			return 8;

		case 0x88: // DEC A
			minx.BA.B.L = DEC8(minx.BA.B.L);
			return 8;
		case 0x89: // DEC B
			minx.BA.B.H = DEC8(minx.BA.B.H);
			return 8;
		case 0x8A: // DEC L
			minx.HL.B.L = DEC8(minx.HL.B.L);
			return 8;
		case 0x8B: // DEC H
			minx.HL.B.H = DEC8(minx.HL.B.H);
			return 8;
		case 0x8C: // DEC N
			minx.N.B.H = DEC8(minx.N.B.H);
			return 8;
		case 0x8D: // DEC [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, DEC8(MinxCPU_OnRead(1, minx.N.D + I8A)));
			return 16;
		case 0x8E: // DEC [HL]
			MinxCPU_OnWrite(1, minx.HL.D, DEC8(MinxCPU_OnRead(1, minx.HL.D)));
			return 12;
		case 0x8F: // DEC SP
			minx.SP.W.L = DEC16(minx.SP.W.L);
			return 8;

		case 0x90: // INC BA
			minx.BA.W.L = INC16(minx.BA.W.L);
			return 8;
		case 0x91: // INC HL
			minx.HL.W.L = INC16(minx.HL.W.L);
			return 8;
		case 0x92: // INC X
			minx.X.W.L = INC16(minx.X.W.L);
			return 8;
		case 0x93: // INC Y
			minx.Y.W.L = INC16(minx.Y.W.L);
			return 8;

		case 0x94: // TST A, B
			AND8(minx.BA.B.L, minx.BA.B.H);
			return 8;
		case 0x95: // TST [HL], #nn
			I8A = Fetch8();
			AND8(MinxCPU_OnRead(1, minx.HL.D), I8A);
			return 12;
		case 0x96: // TST A, #nn
			I8A = Fetch8();
			AND8(minx.BA.B.L, I8A);
			return 8;
		case 0x97: // TST B, #nn
			I8A = Fetch8();
			AND8(minx.BA.B.H, I8A);
			return 8;

		case 0x98: // DEC BA
			minx.BA.W.L = DEC16(minx.BA.W.L);
			return 8;
		case 0x99: // DEC HL
			minx.HL.W.L = DEC16(minx.HL.W.L);
			return 8;
		case 0x9A: // DEC X
			minx.X.W.L = DEC16(minx.X.W.L);
			return 8;
		case 0x9B: // DEC Y
			minx.Y.W.L = DEC16(minx.Y.W.L);
			return 8;

		case 0x9C: // AND F, #nn
			I8A = Fetch8();
			minx.F = minx.F & I8A;
			MinxCPU_OnIRQHandle(minx.F, minx.Shift_U);
			return 12;
		case 0x9D: // OR F, #nn
			I8A = Fetch8();
			minx.F = minx.F | I8A;
			MinxCPU_OnIRQHandle(minx.F, minx.Shift_U);
			return 12;
		case 0x9E: // XOR F, #nn
			I8A = Fetch8();
			minx.F = minx.F ^ I8A;
			MinxCPU_OnIRQHandle(minx.F, minx.Shift_U);
			return 12;
		case 0x9F: // MOV F, #nn
			I8A = Fetch8();
			minx.F = I8A;
			MinxCPU_OnIRQHandle(minx.F, minx.Shift_U);
			return 12;
		case 0xA0: // PUSH BA
			PUSH(minx.BA.B.H);
			PUSH(minx.BA.B.L);
			return 16;
		case 0xA1: // PUSH HL
			PUSH(minx.HL.B.H);
			PUSH(minx.HL.B.L);
			return 16;
		case 0xA2: // PUSH X
			PUSH(minx.X.B.H);
			PUSH(minx.X.B.L);
			return 16;
		case 0xA3: // PUSH Y
			PUSH(minx.Y.B.H);
			PUSH(minx.Y.B.L);
			return 16;
		case 0xA4: // PUSH N
			PUSH(minx.N.B.H);
			return 12;
		case 0xA5: // PUSH I
			PUSH(minx.HL.B._I);
			return 12;
		case 0xA6: // PUSHX
			PUSH(minx.X.B._I);
			PUSH(minx.Y.B._I);
			return 16;
		case 0xA7: // PUSH F
			PUSH(minx.F);
			return 12;
			
		case 0xA8: // POP BA
			minx.BA.B.L = POP();
			minx.BA.B.H = POP();
			return 12;
		case 0xA9: // POP HL
			minx.HL.B.L = POP();
			minx.HL.B.H = POP();
			return 12;
		case 0xAA: // POP X
			minx.X.B.L = POP();
			minx.X.B.H = POP();
			return 12;
		case 0xAB: // POP Y
			minx.Y.B.L = POP();
			minx.Y.B.H = POP();
			return 12;
		case 0xAC: // POP N
			minx.N.B.H = POP();
			return 8;
		case 0xAD: // POP I
			minx.HL.B._I = POP();
			minx.N.B._I = minx.HL.B._I;
			return 8;
		case 0xAE: // POPX
			minx.Y.B._I = POP();
			minx.X.B._I = POP();
			return 12;
		case 0xB0: // MOV A, #nn
			I8A = Fetch8();
			minx.BA.B.L = I8A;
			return 8;
		case 0xB1: // MOV B, #nn
			I8A = Fetch8();
			minx.BA.B.H = I8A;
			return 8;
		case 0xB2: // MOV L, #nn
			I8A = Fetch8();
			minx.HL.B.L = I8A;
			return 8;
		case 0xB3: // MOV H, #nn
			I8A = Fetch8();
			minx.HL.B.H = I8A;
			return 8;
		case 0xB4: // MOV N, #nn
			I8A = Fetch8();
			minx.N.B.H = I8A;
			return 8;
		case 0xC8: // XCHG BA, HL
			I16 = minx.HL.W.L;
			minx.HL.W.L = minx.BA.W.L;
			minx.BA.W.L = I16;
			return 12;
		case 0xC9: // XCHG BA, X
			I16 = minx.X.W.L;
			minx.X.W.L = minx.BA.W.L;
			minx.BA.W.L = I16;
			return 12;			
		case 0xCA: // XCHG BA, Y
			I16 = minx.Y.W.L;
			minx.Y.W.L = minx.BA.W.L;
			minx.BA.W.L = I16;
			return 12;			
		case 0xCB: // XCHG BA, SP
			I16 = minx.SP.W.L;
			minx.SP.W.L = minx.BA.W.L;
			minx.BA.W.L = I16;
			return 12;			
		case 0xCC: // XCHG A, B
			I8A = minx.BA.B.H;
			minx.BA.B.H = minx.BA.B.L;
			minx.BA.B.L = I8A;
			return 8;
		case 0xCD: // XCHG A, [HL]
			I8A = MinxCPU_OnRead(1, minx.HL.D);
			MinxCPU_OnWrite(1, minx.HL.D, minx.BA.B.L);
			minx.BA.B.L = I8A;
			return 12;
		case 0xCE: // Expand 0
			return CPUCE();
		case 0xCF: // Expand 1
			return CPUCF();	
		case 0xD0: // SUB BA, #nnnn
			I16 = Fetch16();
			minx.BA.W.L = SUB16(minx.BA.W.L, I16);
			return 12;
		case 0xD1: // SUB HL, #nnnn
			I16 = Fetch16();
			minx.HL.W.L = SUB16(minx.HL.W.L, I16);
			return 12;
		case 0xD2: // SUB X, #nnnn
			I16 = Fetch16();
			minx.X.W.L = SUB16(minx.X.W.L, I16);
			return 12;
		case 0xD3: // SUB Y, #nnnn
			I16 = Fetch16();
			minx.Y.W.L = SUB16(minx.Y.W.L, I16);
			return 12;

		case 0xD4: // CMP BA, #nnnn
			I16 = Fetch16();
			SUB16(minx.BA.W.L, I16);
			return 12;
		case 0xD5: // CMP HL, #nnnn
			I16 = Fetch16();
			SUB16(minx.HL.W.L, I16);
			return 12;
		case 0xD6: // CMP X, #nnnn
			I16 = Fetch16();
			SUB16(minx.X.W.L, I16);
			return 12;
		case 0xD7: // CMP Y, #nnnn
			I16 = Fetch16();
			SUB16(minx.Y.W.L, I16);
			return 12;

		case 0xD8: // AND [N+#nn], #nn
			I8A = Fetch8();
			I8B = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, AND8(MinxCPU_OnRead(1, minx.N.D + I8A), I8B));
			return 20;
		case 0xD9: // OR [N+#nn], #nn
			I8A = Fetch8();
			I8B = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, OR8(MinxCPU_OnRead(1, minx.N.D + I8A), I8B));
			return 20;
		case 0xDA: // XOR [N+#nn], #nn
			I8A = Fetch8();
			I8B = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, XOR8(MinxCPU_OnRead(1, minx.N.D + I8A), I8B));
			return 20;
		case 0xDB: // CMP [N+#nn], #nn
			I8A = Fetch8();
			I8B = Fetch8();
			SUB8(MinxCPU_OnRead(1, minx.N.D + I8A), I8B);
			return 16;
		case 0xDC: // TST [N+#nn], #nn
			I8A = Fetch8();
			I8B = Fetch8();
			AND8(MinxCPU_OnRead(1, minx.N.D + I8A), I8B);
			return 16;
		case 0xDD: // MOV [N+#nn], #nn
			I8A = Fetch8();
			I8B = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D + I8A, I8B);
			return 16;
		case 0xDE: // PACK
			minx.BA.B.L = (minx.BA.B.L & 0x0F) | (minx.BA.B.H << 4);
			return 8;
		case 0xDF: // UNPACK
			minx.BA.B.H = (minx.BA.B.L >> 4);
			minx.BA.B.L = minx.BA.B.L & 0x0F;
			return 8;
		case 0xF1: // JMP #ss
			I8A = Fetch8();
			JMPS(S8_TO_16(I8A));
			return 8;
		case 0xF2: // CALL #ssss
			I16 = Fetch16();
			CALLS(I16);
			return 24;
		case 0xF3: // JMP #ssss
			I16 = Fetch16();
			JMPS(I16);
			return 12;
		case 0xF6: // SWAP A
			minx.BA.B.L = SWAP(minx.BA.B.L);	
			
		case 0xFF: //nop
			return 8;
			
		default:
			return 0;
	}
	return 0;
}

int CPUCE()
{
	uint8_t I8A;
	uint16_t I16;

	// Read IR
	minx.IR = Fetch8();

	// Process instruction
	switch(minx.IR) {

		case 0x00: // ADD A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x01: // ADD A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x02: // ADD A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x03: // ADD A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = ADD8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x04: // ADD [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, ADD8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L));
			return 16;
		case 0x05: // ADD [HL], #nn
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, ADD8(MinxCPU_OnRead(1, minx.HL.D), I8A));
			return 20;
		case 0x06: // ADD [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, ADD8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D)));
			return 20;
		case 0x07: // ADD [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, ADD8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D)));
			return 20;

		case 0x08: // ADC A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x09: // ADC A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x0A: // ADC A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x0B: // ADC A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = ADC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x0C: // ADC [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, ADC8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L));
			return 16;
		case 0x0D: // ADC [HL], #nn
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, ADC8(MinxCPU_OnRead(1, minx.HL.D), I8A));
			return 20;
		case 0x0E: // ADC [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, ADC8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D)));
			return 20;
		case 0x0F: // ADC [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, ADC8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D)));
			return 20;

		case 0x10: // SUB A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x11: // SUB A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x12: // SUB A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x13: // SUB A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x14: // SUB [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, SUB8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L));
			return 16;
		case 0x15: // SUB [HL], #nn
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, SUB8(MinxCPU_OnRead(1, minx.HL.D), I8A));
			return 20;
		case 0x16: // SUB [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, SUB8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D)));
			return 20;
		case 0x17: // SUB [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, SUB8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D)));
			return 20;

		case 0x18: // SBC A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x19: // SBC A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x1A: // SBC A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x1B: // SBC A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = SBC8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x1C: // SBC [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, SBC8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L));
			return 16;
		case 0x1D: // SBC [HL], #nn
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, SBC8(MinxCPU_OnRead(1, minx.HL.D), I8A));
			return 20;
		case 0x1E: // SBC [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, SBC8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D)));
			return 20;
		case 0x1F: // SBC [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, SBC8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D)));
			return 20;

		case 0x20: // AND A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x21: // AND A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x22: // AND A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x23: // AND A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = AND8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x24: // AND [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, AND8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L));
			return 16;
		case 0x25: // AND [HL], #nn
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, AND8(MinxCPU_OnRead(1, minx.HL.D), I8A));
			return 20;
		case 0x26: // AND [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, AND8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D)));
			return 20;
		case 0x27: // AND [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, AND8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D)));
			return 20;

		case 0x28: // OR A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x29: // OR A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x2A: // OR A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x2B: // OR A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = OR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x2C: // OR [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, OR8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L));
			return 16;
		case 0x2D: // OR [HL], #nn
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, OR8(MinxCPU_OnRead(1, minx.HL.D), I8A));
			return 20;
		case 0x2E: // OR [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, OR8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D)));
			return 20;
		case 0x2F: // OR [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, OR8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D)));
			return 20;

		case 0x30: // CMP A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x31: // CMP A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x32: // CMP A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x33: // CMP A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			SUB8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x34: // CMP [HL], A
			SUB8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L);
			return 16;
		case 0x35: // CMP [HL], #nn
			I8A = Fetch8();
			SUB8(MinxCPU_OnRead(1, minx.HL.D), I8A);
			return 20;
		case 0x36: // CMP [HL], [X]
			SUB8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D));
			return 20;
		case 0x37: // CMP [HL], [Y]
			SUB8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D));
			return 20;

		case 0x38: // XOR A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x39: // XOR A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;
		case 0x3A: // XOR A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 16;
		case 0x3B: // XOR A, [Y+L]
			I16 = minx.Y.W.L+ S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = XOR8(minx.BA.B.L, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 16;

		case 0x3C: // XOR [HL], A
			MinxCPU_OnWrite(1, minx.HL.D, XOR8(MinxCPU_OnRead(1, minx.HL.D), minx.BA.B.L));
			return 16;
		case 0x3D: // XOR [HL], #nn
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.HL.D, XOR8(MinxCPU_OnRead(1, minx.HL.D), I8A));
			return 20;
		case 0x3E: // XOR [HL], [X]
			MinxCPU_OnWrite(1, minx.HL.D, XOR8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.X.D)));
			return 20;
		case 0x3F: // XOR [HL], [Y]
			MinxCPU_OnWrite(1, minx.HL.D, XOR8(MinxCPU_OnRead(1, minx.HL.D), MinxCPU_OnRead(1, minx.Y.D)));
			return 20;

		case 0x40: // MOV A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x41: // MOV A, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;
		case 0x42: // MOV A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x43: // MOV A, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;

		case 0x44: // MOV [X+#ss], A
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.BA.B.L);
			return 16;
		case 0x45: // MOV [Y+#ss], A
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.BA.B.L);
			return 16;
		case 0x46: // MOV [X+L], A
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.BA.B.L);
			return 16;
		case 0x47: // MOV [Y+L], A
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.BA.B.L);
			return 16;

		case 0x48: // MOV B, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x49: // MOV B, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.BA.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;
		case 0x4A: // MOV B, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x4B: // MOV B, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;

		case 0x4C: // MOV [X+#ss], B
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.BA.B.H);
			return 16;
		case 0x4D: // MOV [Y+#ss], B
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.BA.B.H);
			return 16;
		case 0x4E: // MOV [X+L], B
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.BA.B.H);
			return 16;
		case 0x4F: // MOV [Y+L], B
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.BA.B.H);
			return 16;

		case 0x50: // MOV L, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x51: // MOV L, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;
		case 0x52: // MOV L, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x53: // MOV L, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;

		case 0x54: // MOV [X+#ss], L
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.HL.B.L);
			return 16;
		case 0x55: // MOV [Y+#ss], L
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.HL.B.L);
			return 16;
		case 0x56: // MOV [X+L], L
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.HL.B.L);
			return 16;
		case 0x57: // MOV [Y+L], L
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.HL.B.L);
			return 16;

		case 0x58: // MOV H, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.HL.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x59: // MOV H, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.HL.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;
		case 0x5A: // MOV H, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.HL.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 16;
		case 0x5B: // MOV H, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.HL.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 16;

		case 0x5C: // MOV [X+#ss], H
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.HL.B.H);
			return 16;
		case 0x5D: // MOV [Y+#ss], H
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.HL.B.H);
			return 16;
		case 0x5E: // MOV [X+L], H
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.HL.B.H);
			return 16;
		case 0x5F: // MOV [Y+L], H
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.HL.B.H);
			return 16;

		case 0x60: // MOV [HL], [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 20;
		case 0x61: // MOV [HL], [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 20;
		case 0x62: // MOV [HL], [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 20;
		case 0x63: // MOV [HL], [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, minx.HL.D, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 20;

		case 0x64: // *ADC BA, #nnnn
			I16 = Fetch16();
			minx.BA.W.L = ADC16(minx.BA.W.L, I16);
			return 16;
		case 0x65: // *ADC HL, #nnnn
			I16 = Fetch16();
			minx.HL.W.L = ADC16(minx.HL.W.L, I16);
			return 16;

		case 0x66: // ??? BA, #nn00+L
			I8A = Fetch8();
			minx.BA.W.L = ADC16(minx.BA.W.L, (I8A << 8) | minx.HL.B.L);
			return 24;
		case 0x67: // ??? HL, #nn00+L
			I8A = Fetch8();
			minx.HL.W.L = ADC16(minx.HL.W.L, (I8A << 8) | minx.HL.B.L);
			return 24;

		case 0x68: // MOV [X], [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 20;
		case 0x69: // MOV [X], [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 20;
		case 0x6A: // MOV [X], [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 20;
		case 0x6B: // MOV [X], [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, minx.X.D, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 20;

		case 0x6C: // *ADD SP, #nnnn
			I16 = Fetch8();
			minx.SP.W.L = ADD16(minx.SP.W.L, I16);

		case 0x6D: // ??? HL, #nn
			I8A = Fetch8();
			minx.HL.W.L = ADD16(minx.X.W.L, ((I8A << 4) * 3) + ((I8A & 0x08) >> 3));
			minx.F &= ~MINX_FLAG_CARRY; // It seems that carry gets clear?
			return 40;
		case 0x6E: // ??? SP, #nn00+L
			I8A = Fetch8();
			minx.SP.W.L = ADD16(minx.SP.W.L, (I8A << 8) | minx.HL.B.L);
			return 16;
		case 0x6F: // ??? HL, L
			minx.HL.W.L = ADD16(minx.X.W.L, ((minx.HL.B.L << 4) * 3) + ((minx.HL.B.L & 0x08) >> 3));
			minx.F &= ~MINX_FLAG_CARRY; // It seems that carry gets clear?
			return 40;

		case 0x70: // NOTHING
			minx.PC.W.L++;
			return 64;
		case 0x71: // NOTHING
			minx.PC.W.L++;
			return 64;
		case 0x72: // NOTHING
			return 64;
		case 0x73: // NOTHING
			return 64;

		case 0x74: // *MOV A, [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 64;
		case 0x75: // *MOV L, [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 64;
		case 0x76: // *MOV A, [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 64;
		case 0x77: // *MOV L, [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 64;

		case 0x78: // MOV [Y], [X+#ss]
			I8A = Fetch8();
			I16 = minx.X.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 20;
		case 0x79: // MOV [Y], [Y+#ss]
			I8A = Fetch8();
			I16 = minx.Y.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 20;
		case 0x7A: // MOV [Y], [X+L]
			I16 = minx.X.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16));
			return 20;
		case 0x7B: // MOV [Y], [Y+L]
			I16 = minx.Y.W.L + S8_TO_16(minx.HL.B.L);
			MinxCPU_OnWrite(1, minx.Y.D, MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16));
			return 20;

		case 0x7C: // NOTHING #nn
			minx.PC.W.L++;
			return 20;
		case 0x7D: // NOTHING #nn
			minx.PC.W.L++;
			return 16;
		case 0x7E: // NOTHING
			return 20;
		case 0x7F: // NOTHING
			return 16;

		case 0x80: // SAL A
			minx.BA.B.L = SAL(minx.BA.B.L);
			return 12;
		case 0x81: // SAL B
			minx.BA.B.H = SAL(minx.BA.B.H);
			return 12;
		case 0x82: // SAL [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, SAL(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x83: // SAL [HL]
			MinxCPU_OnWrite(1, minx.HL.D, SAL(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0x84: // SHL A
			minx.BA.B.L = SHL(minx.BA.B.L);
			return 12;
		case 0x85: // SHL B
			minx.BA.B.H = SHL(minx.BA.B.H);
			return 12;
		case 0x86: // SHL [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, SHL(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x87: // SHL [HL]
			MinxCPU_OnWrite(1, minx.HL.D, SHL(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0x88: // SAR A
			minx.BA.B.L = SAR(minx.BA.B.L);
			return 12;
		case 0x89: // SAR B
			minx.BA.B.H = SAR(minx.BA.B.H);
			return 12;
		case 0x8A: // SAR [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, SAR(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x8B: // SAR [HL]
			MinxCPU_OnWrite(1, minx.HL.D, SAR(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0x8C: // SHR A
			minx.BA.B.L = SHR(minx.BA.B.L);
			return 12;
		case 0x8D: // SHR B
			minx.BA.B.H = SHR(minx.BA.B.H);
			return 12;
		case 0x8E: // SHR [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, SHR(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x8F: // SHR [HL]
			MinxCPU_OnWrite(1, minx.HL.D, SHR(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0x90: // ROLC A
			minx.BA.B.L = ROLC(minx.BA.B.L);
			return 12;
		case 0x91: // ROLC B
			minx.BA.B.H = ROLC(minx.BA.B.H);
			return 12;
		case 0x92: // ROLC [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, ROLC(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x93: // ROLC [HL]
			MinxCPU_OnWrite(1, minx.HL.D, ROLC(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0x94: // ROL A
			minx.BA.B.L = ROL(minx.BA.B.L);
			return 12;
		case 0x95: // ROL B
			minx.BA.B.H = ROL(minx.BA.B.H);
			return 12;
		case 0x96: // ROL [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, ROL(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x97: // ROL [HL]
			MinxCPU_OnWrite(1, minx.HL.D, ROL(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0x98: // RORC A
			minx.BA.B.L = RORC(minx.BA.B.L);
			return 12;
		case 0x99: // RORC B
			minx.BA.B.H = RORC(minx.BA.B.H);
			return 12;
		case 0x9A: // RORC [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, RORC(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x9B: // RORC [HL]
			MinxCPU_OnWrite(1, minx.HL.D, RORC(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0x9C: // ROR A
			minx.BA.B.L = ROR(minx.BA.B.L);
			return 12;
		case 0x9D: // ROR B
			minx.BA.B.H = ROR(minx.BA.B.H);
			return 12;
		case 0x9E: // ROR [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, ROR(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0x9F: // ROR [HL]
			MinxCPU_OnWrite(1, minx.HL.D, ROR(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0xA0: // NOT A
			minx.BA.B.L = MNOT(minx.BA.B.L);
			return 12;
		case 0xA1: // NOT B
			minx.BA.B.H = MNOT(minx.BA.B.H);
			return 12;
		case 0xA2: // NOT [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, MNOT(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0xA3: // NOT [HL]
			MinxCPU_OnWrite(1, minx.HL.D, MNOT(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0xA4: // NEG A
			minx.BA.B.L = NEG(minx.BA.B.L);
			return 12;
		case 0xA5: // NEG B
			minx.BA.B.H = NEG(minx.BA.B.H);
			return 12;
		case 0xA6: // NEG [N+#nn]
			I8A = Fetch8();
			MinxCPU_OnWrite(1, minx.N.D | I8A, NEG(MinxCPU_OnRead(1, minx.N.D | I8A)));
			return 20;
		case 0xA7: // NEG [HL]
			MinxCPU_OnWrite(1, minx.HL.D, NEG(MinxCPU_OnRead(1, minx.HL.D)));
			return 16;

		case 0xA8: // EX BA, A
			minx.BA.W.L = S8_TO_16(minx.BA.B.L);
			return 12;

		case 0xA9: // NOTHING
			return 8;
		case 0xAA: // NOTHING
			return 12;

		case 0xAB: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0xABCE);
			return 64;
		case 0xAC: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0xACCE);
			return 64;
		case 0xAD: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0xACCE);
			return 64;

		case 0xAE: // HALT
			HALT();
			return 8;
		case 0xAF: // STOP
			STOP();
			return 8;

		case 0xB0: // AND B, #nn
			I8A = Fetch8();
			minx.BA.B.H = AND8(minx.BA.B.H, I8A);
			return 12;
		case 0xB1: // AND L, #nn
			I8A = Fetch8();
			minx.HL.B.L = AND8(minx.HL.B.L, I8A);
			return 12;
		case 0xB2: // AND H, #nn
			I8A = Fetch8();
			minx.HL.B.H = AND8(minx.HL.B.H, I8A);
			return 12;
		case 0xB3: // MOV H, V
			minx.HL.B.H = minx.PC.B._I;
			return 12;

		case 0xB4: // OR B, #nn
			I8A = Fetch8();
			minx.BA.B.H = OR8(minx.BA.B.H, I8A);
			return 12;
		case 0xB5: // OR L, #nn
			I8A = Fetch8();
			minx.HL.B.L = OR8(minx.HL.B.L, I8A);
			return 12;
		case 0xB6: // OR H, #nn
			I8A = Fetch8();
			minx.HL.B.H = OR8(minx.HL.B.H, I8A);
			return 12;
		case 0xB7: // ??? X
			minx.X.B.H = minx.PC.B._I;
			return 12;

		case 0xB8: // XOR B, #nn
			I8A = Fetch8();
			minx.BA.B.H = XOR8(minx.BA.B.H, I8A);
			return 12;
		case 0xB9: // XOR L, #nn
			I8A = Fetch8();
			minx.HL.B.L = XOR8(minx.HL.B.L, I8A);
			return 12;
		case 0xBA: // XOR H, #nn
			I8A = Fetch8();
			minx.HL.B.H = XOR8(minx.HL.B.H, I8A);
			return 12;
		case 0xBB: // ??? Y
			minx.Y.B.H = minx.PC.B._I;
			return 12;

		case 0xBC: // CMP B, #nn
			I8A = Fetch8();
			SUB8(minx.BA.B.H, I8A);
			return 12;
		case 0xBD: // CMP L, #nn
			I8A = Fetch8();
			SUB8(minx.HL.B.L, I8A);
			return 12;
		case 0xBE: // CMP H, #nn
			I8A = Fetch8();
			SUB8(minx.HL.B.H, I8A);
			return 12;
		case 0xBF: // CMP N, #nn
			I8A = Fetch8();
			SUB8(minx.N.B.H, I8A);
			return 12;

		case 0xC0: // MOV A, N
			minx.BA.B.L = minx.N.B.H;
			return 8;
		case 0xC1: // MOV A, F
			minx.BA.B.L = minx.F;
			return 8;
		case 0xC2: // MOV N, A
			minx.N.B.H = minx.BA.B.L;
			return 8;
		case 0xC3: // MOV F, A
			minx.F = minx.BA.B.L;
			MinxCPU_OnIRQHandle(minx.F, minx.Shift_U);
			return 8;

		case 0xC4: // MOV U, #nn
			I8A = Fetch8();
			Set_U(I8A);
			return 16;
		case 0xC5: // MOV I, #nn
			I8A = Fetch8();
			minx.HL.B._I = I8A;
			minx.N.B._I = minx.HL.B._I;
			return 12;
		case 0xC6: // MOV XI, #nn
			I8A = Fetch8();
			minx.X.B._I = I8A;
			return 12;
		case 0xC7: // MOV YI, #nn
			I8A = Fetch8();
			minx.Y.B._I = I8A;
			return 12;

		case 0xC8: // MOV A, V
			minx.BA.B.L = minx.PC.B._I;
			return 8;
		case 0xC9: // MOV A, I
			minx.BA.B.L = minx.HL.B._I;
			return 8;
		case 0xCA: // MOV A, XI
			minx.BA.B.L = minx.X.B._I;
			return 8;
		case 0xCB: // MOV A, YI
			minx.BA.B.L = minx.Y.B._I;
			return 8;

		case 0xCC: // MOV U, A
			Set_U(minx.BA.B.L);
			return 8;
		case 0xCD: // MOV I, A
			minx.HL.B._I = minx.BA.B.L;
			minx.N.B._I = minx.HL.B._I;
			return 8;
		case 0xCE: // MOV XI, A
			minx.X.B._I = minx.BA.B.L;
			return 8;
		case 0xCF: // MOV YI, A
			minx.Y.B._I = minx.BA.B.L;
			return 8;

		case 0xD0: // MOV A, [#nnnn]
			I16 = Fetch16();
			minx.BA.B.L = MinxCPU_OnRead(1, I16);
			return 20;
		case 0xD1: // MOV B, [#nnnn]
			I16 = Fetch16();
			minx.BA.B.H = MinxCPU_OnRead(1, I16);
			return 20;
		case 0xD2: // MOV L, [#nnnn]
			I16 = Fetch16();
			minx.HL.B.L = MinxCPU_OnRead(1, I16);
			return 20;
		case 0xD3: // MOV H, [#nnnn]
			I16 = Fetch16();
			minx.HL.B.H = MinxCPU_OnRead(1, I16);
			return 20;

		case 0xD4: // MOV [#nnnn], A
			I16 = Fetch16();
			MinxCPU_OnWrite(1, I16, minx.BA.B.L);
			return 20;
		case 0xD5: // MOV [#nnnn], B
			I16 = Fetch16();
			MinxCPU_OnWrite(1, I16, minx.BA.B.H);
			return 20;
		case 0xD6: // MOV [#nnnn], L
			I16 = Fetch16();
			MinxCPU_OnWrite(1, I16, minx.HL.B.L);
			return 20;
		case 0xD7: // MOV [#nnnn], H
			I16 = Fetch16();
			MinxCPU_OnWrite(1, I16, minx.HL.B.H);
			return 20;

		case 0xD8: // MUL L, A
			MUL();
			return 48;

		case 0xD9: // DIV HL, A
			DIV();
			return 52;

		case 0xDA: // ??? #nn
		case 0xDB: // ??? #nn
			return CPUSPCE();
		case 0xDC: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0xDCCE);
			return 64;
		case 0xDD: // NOTHING
			return 16;
		case 0xDE: // ??? #nn
		case 0xDF: // ??? #nn
			return CPUSPCE();

		case 0xE0: // JL #ss
			I8A = Fetch8();
			if ( ((minx.F & MINX_FLAG_OVERFLOW)!=0) != ((minx.F & MINX_FLAG_SIGN)!=0) ) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xE1: // JLE #ss
			I8A = Fetch8();
			if ( (((minx.F & MINX_FLAG_OVERFLOW)==0) != ((minx.F & MINX_FLAG_SIGN)==0)) || ((minx.F & MINX_FLAG_ZERO)!=0) ) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xE2: // JG #ss
			I8A = Fetch8();
			if ( (((minx.F & MINX_FLAG_OVERFLOW)!=0) == ((minx.F & MINX_FLAG_SIGN)!=0)) && ((minx.F & MINX_FLAG_ZERO)==0) ) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xE3: // JGE #ss
			I8A = Fetch8();
			if ( ((minx.F & MINX_FLAG_OVERFLOW)==0) == ((minx.F & MINX_FLAG_SIGN)==0) ) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;

		case 0xE4: // JO #ss
			I8A = Fetch8();
			if (minx.F & MINX_FLAG_OVERFLOW) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xE5: // JNO #ss
			I8A = Fetch8();
			if (!(minx.F & MINX_FLAG_OVERFLOW)) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xE6: // JP #ss
			I8A = Fetch8();
			if (!(minx.F & MINX_FLAG_SIGN)) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xE7: // JNP #ss
			I8A = Fetch8();
			if (minx.F & MINX_FLAG_SIGN) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;

		case 0xE8: // JNX0 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x01)) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xE9: // JNX1 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x02)) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xEA: // JNX2 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x04)) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xEB: // JNX3 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x08)) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;

		case 0xEC: // JX0 #ss
			I8A = Fetch8();
			if (minx.E & 0x01) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xED: // JX1 #ss
			I8A = Fetch8();
			if (minx.E & 0x02) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xEE: // JX2 #ss
			I8A = Fetch8();
			if (minx.E & 0x04) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;
		case 0xEF: // JX3 #ss
			I8A = Fetch8();
			if (minx.E & 0x08) {
				JMPS(S8_TO_16(I8A));
			}
			return 12;

		case 0xF0: // CALLL #ss
			I8A = Fetch8();
			if ( ((minx.F & MINX_FLAG_OVERFLOW)!=0) != ((minx.F & MINX_FLAG_SIGN)!=0) ) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xF1: // CALLLE #ss
			I8A = Fetch8();
			if ( (((minx.F & MINX_FLAG_OVERFLOW)==0) != ((minx.F & MINX_FLAG_SIGN)==0)) || ((minx.F & MINX_FLAG_ZERO)!=0) ) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xF2: // CALLG #ss
			I8A = Fetch8();
			if ( (((minx.F & MINX_FLAG_OVERFLOW)!=0) == ((minx.F & MINX_FLAG_SIGN)!=0)) && ((minx.F & MINX_FLAG_ZERO)==0) ) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xF3: // CALLGE #ss
			I8A = Fetch8();
			if ( ((minx.F & MINX_FLAG_OVERFLOW)==0) == ((minx.F & MINX_FLAG_SIGN)==0) ) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;

		case 0xF4: // CALLO #ss
			I8A = Fetch8();
			if (minx.F & MINX_FLAG_OVERFLOW) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xF5: // CALLNO #ss
			I8A = Fetch8();
			if (!(minx.F & MINX_FLAG_OVERFLOW)) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xF6: // CALLNS #ss
			I8A = Fetch8();
			if (!(minx.F & MINX_FLAG_SIGN)) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xF7: // CALLS #ss
			I8A = Fetch8();
			if (minx.F & MINX_FLAG_SIGN) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;

		case 0xF8: // CALLNX0 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x01)) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xF9: // CALLNX1 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x02)) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xFA: // CALLNX2 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x04)) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xFB: // CALLNX3 #ss
			I8A = Fetch8();
			if (!(minx.E & 0x08)) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;

		case 0xFC: // CALLX0 #ss
			I8A = Fetch8();
			if (minx.E & 0x01) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xFD: // CALLX1 #ss
			I8A = Fetch8();
			if (minx.E & 0x02) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xFE: // CALLX2 #ss
			I8A = Fetch8();
			if (minx.E & 0x04) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;
		case 0xFF: // CALLX3 #ss
			I8A = Fetch8();
			if (minx.E & 0x08) {
				CALLS(S8_TO_16(I8A));
			}
			return 12;

		default:
			MinxCPU_OnException(EXCEPTION_UNKNOWN_INSTRUCTION, (minx.IR << 8) + 0xCE);
			return 4;
	}
}

int CPUCF(void)
{
	uint8_t I8A;
	uint16_t I16;

	// Read IR
	minx.IR = Fetch8();

	// Process instruction
	switch(minx.IR) {
		case 0x00: // ADD BA, BA
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x01: // ADD BA, HL
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x02: // ADD BA, X
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x03: // ADD BA, Y
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x04: // ADC BA, BA
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x05: // ADC BA, HL
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x06: // ADC BA, X
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x07: // ADC BA, Y
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x08: // SUB BA, BA
			minx.BA.W.L = SUB16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x09: // SUB BA, HL
			minx.BA.W.L = SUB16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x0A: // SUB BA, X
			minx.BA.W.L = SUB16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x0B: // SUB BA, Y
			minx.BA.W.L = SUB16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x0C: // SBC BA, BA
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x0D: // SBC BA, HL
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x0E: // SBC BA, X
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x0F: // SBC BA, Y
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x10: // *ADD BA, BA
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x11: // *ADD BA, HL
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x12: // *ADD BA, X
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x13: // *ADD BA, Y
			minx.BA.W.L = ADD16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x14: // *ADC BA, BA
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x15: // *ADC BA, HL
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x16: // *ADC BA, X
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x17: // *ADC BA, Y
			minx.BA.W.L = ADC16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x18: // CMP BA, BA
			SUB16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x19: // CMP BA, HL
			SUB16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x1A: // CMP BA, X
			SUB16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x1B: // CMP BA, Y
			SUB16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x1C: // *SBC BA, BA
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x1D: // *SBC BA, HL
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x1E: // *SBC BA, X
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x1F: // *SBC BA, Y
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x20: // ADD HL, BA
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.BA.W.L);
			return 16;
		case 0x21: // ADD HL, HL
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.HL.W.L);
			return 16;
		case 0x22: // ADD HL, X
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.X.W.L);
			return 16;
		case 0x23: // ADD HL, Y
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.Y.W.L);
			return 16;

		case 0x24: // ADC HL, BA
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.BA.W.L);
			return 16;
		case 0x25: // ADC HL, HL
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.HL.W.L);
			return 16;
		case 0x26: // ADC HL, X
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.X.W.L);
			return 16;
		case 0x27: // ADC HL, Y
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.Y.W.L);
			return 16;

		case 0x28: // SUB HL, BA
			minx.HL.W.L = SUB16(minx.HL.W.L, minx.BA.W.L);
			return 16;
		case 0x29: // SUB HL, HL
			minx.HL.W.L = SUB16(minx.HL.W.L, minx.HL.W.L);
			return 16;
		case 0x2A: // SUB HL, X
			minx.HL.W.L = SUB16(minx.HL.W.L, minx.X.W.L);
			return 16;
		case 0x2B: // SUB HL, Y
			minx.HL.W.L = SUB16(minx.HL.W.L, minx.Y.W.L);
			return 16;

		case 0x2C: // SBC HL, BA
			minx.HL.W.L = SBC16(minx.HL.W.L, minx.BA.W.L);
			return 16;
		case 0x2D: // SBC HL, HL
			minx.HL.W.L = SBC16(minx.HL.W.L, minx.HL.W.L);
			return 16;
		case 0x2E: // SBC HL, X
			minx.HL.W.L = SBC16(minx.HL.W.L, minx.X.W.L);
			return 16;
		case 0x2F: // SBC HL, Y
			minx.HL.W.L = SBC16(minx.HL.W.L, minx.Y.W.L);
			return 16;

		case 0x30: // *ADD HL, BA
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.BA.W.L);
			return 16;
		case 0x31: // *ADD BA, HL
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.HL.W.L);
			return 16;
		case 0x32: // *ADD BA, X
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.X.W.L);
			return 16;
		case 0x33: // *ADD BA, Y
			minx.HL.W.L = ADD16(minx.HL.W.L, minx.Y.W.L);
			return 16;

		case 0x34: // *ADC HL, BA
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.BA.W.L);
			return 16;
		case 0x35: // *ADC HL, HL
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.HL.W.L);
			return 16;
		case 0x36: // *ADC HL, X
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.X.W.L);
			return 16;
		case 0x37: // *ADC HL, Y
			minx.HL.W.L = ADC16(minx.HL.W.L, minx.Y.W.L);
			return 16;

		case 0x38: // CMP HL, BA
			SUB16(minx.HL.W.L, minx.BA.W.L);
			return 16;
		case 0x39: // CMP HL, HL
			SUB16(minx.HL.W.L, minx.HL.W.L);
			return 16;
		case 0x3A: // CMP HL, X
			SUB16(minx.HL.W.L, minx.X.W.L);
			return 16;
		case 0x3B: // CMP HL, Y
			SUB16(minx.HL.W.L, minx.Y.W.L);
			return 16;

		case 0x3C: // *SBC BA, BA
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.BA.W.L);
			return 16;
		case 0x3D: // *SBC BA, HL
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.HL.W.L);
			return 16;
		case 0x3E: // *SBC BA, X
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.X.W.L);
			return 16;
		case 0x3F: // *SBC BA, Y
			minx.BA.W.L = SBC16(minx.BA.W.L, minx.Y.W.L);
			return 16;

		case 0x40: // ADD X, BA
			minx.X.W.L = ADD16(minx.X.W.L, minx.BA.W.L);
			return 16;
		case 0x41: // ADD X, HL
			minx.X.W.L = ADD16(minx.X.W.L, minx.HL.W.L);
			return 16;
		case 0x42: // ADD Y, BA
			minx.Y.W.L = ADD16(minx.Y.W.L, minx.BA.W.L);
			return 16;
		case 0x43: // ADD Y, HL
			minx.Y.W.L = ADD16(minx.Y.W.L, minx.HL.W.L);
			return 16;
		case 0x44: // ADD SP, BA
			minx.SP.W.L = ADD16(minx.SP.W.L, minx.BA.W.L);
			return 16;
		case 0x45: // ADD SP, HL
			minx.SP.W.L = ADD16(minx.SP.W.L, minx.HL.W.L);
			return 16;
		case 0x46: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x46CF);
			return 16;
		case 0x47: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x47CF);
			return 16;

		case 0x48: // SUB X, BA
			minx.X.W.L = SUB16(minx.X.W.L, minx.BA.W.L);
			return 16;
		case 0x49: // SUB X, HL
			minx.X.W.L = SUB16(minx.X.W.L, minx.HL.W.L);
			return 16;
		case 0x4A: // SUB Y, BA
			minx.Y.W.L = SUB16(minx.Y.W.L, minx.BA.W.L);
			return 16;
		case 0x4B: // SUB Y, HL
			minx.Y.W.L = SUB16(minx.Y.W.L, minx.HL.W.L);
			return 16;
		case 0x4C: // SUB SP, BA
			minx.SP.W.L = SUB16(minx.SP.W.L, minx.BA.W.L);
			return 16;
		case 0x4D: // SUB SP, HL
			minx.SP.W.L = SUB16(minx.SP.W.L, minx.HL.W.L);
			return 16;
		case 0x4E: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x4ECF);
			return 16;
		case 0x4F: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x4FCF);
			return 16;

		case 0x50: // *ADD X, BA
			minx.X.W.L = ADD16(minx.X.W.L, minx.BA.W.L);
			return 16;
		case 0x51: // *ADD X, HL
			minx.X.W.L = ADD16(minx.X.W.L, minx.HL.W.L);
			return 16;
		case 0x52: // *ADD Y, BA
			minx.Y.W.L = ADD16(minx.Y.W.L, minx.BA.W.L);
			return 16;
		case 0x53: // *ADD Y, HL
			minx.Y.W.L = ADD16(minx.Y.W.L, minx.HL.W.L);
			return 16;
		case 0x54: // *ADD SP, BA
			minx.SP.W.L = ADD16(minx.SP.W.L, minx.BA.W.L);
			return 16;
		case 0x55: // *ADD SP, HL
			minx.SP.W.L = ADD16(minx.SP.W.L, minx.HL.W.L);
			return 16;
		case 0x56: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x56CF);
			return 16;
		case 0x57: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x57CF);
			return 16;

		case 0x58: // *SUB X, BA
			minx.X.W.L = SUB16(minx.X.W.L, minx.BA.W.L);
			return 16;
		case 0x59: // *SUB X, HL
			minx.X.W.L = SUB16(minx.X.W.L, minx.HL.W.L);
			return 16;
		case 0x5A: // *SUB Y, BA
			minx.Y.W.L = SUB16(minx.Y.W.L, minx.BA.W.L);
			return 16;
		case 0x5B: // *SUB Y, HL
			minx.Y.W.L = SUB16(minx.Y.W.L, minx.HL.W.L);
			return 16;
		case 0x5C: // CMP SP, BA
			SUB16(minx.SP.W.L, minx.BA.W.L);
			return 16;
		case 0x5D: // CMP SP, HL
			SUB16(minx.SP.W.L, minx.HL.W.L);
			return 16;
		case 0x5E: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x5ECF);
			return 16;
		case 0x5F: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, 0x5FCF);
			return 16;

		case 0x60: // ADC BA, #nnnn
			I16 = Fetch16();
			minx.BA.W.L = ADC16(minx.BA.W.L, I16);
			return 16;
		case 0x61: // ADC HL, #nnnn
			I16 = Fetch16();
			minx.HL.W.L = ADC16(minx.HL.W.L, I16);
			return 16;
		case 0x62: // SBC BA, #nnnn
			I16 = Fetch16();
			minx.BA.W.L = SBC16(minx.BA.W.L, I16);
			return 16;
		case 0x63: // SBC HL, #nnnn
			I16 = Fetch16();
			minx.HL.W.L = SBC16(minx.HL.W.L, I16);
			return 16;

		case 0x64: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x64CF);
			return 16;
		case 0x65: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x65CF);
			return 16;
		case 0x66: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x66CF);
			return 16;
		case 0x67: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x67CF);
			return 16;

		case 0x68: // ADD SP, #nnnn
			I16 = Fetch16();
			minx.SP.W.L = ADD16(minx.SP.W.L, I16);
			return 16;
		case 0x69: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x69CF);
			return 16;

		case 0x6A: // SUB SP, #nnnn
			I16 = Fetch16();
			minx.SP.W.L = SUB16(minx.SP.W.L, I16);
			return 16;
		case 0x6B: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x6BCF);
			return 16;

		case 0x6C: // CMP SP, #nnnn
			I16 = Fetch16();
			SUB16(minx.SP.W.L, I16);
			return 16;
		case 0x6D: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x6DCF);
			return 16;

		case 0x6E: // MOV SP, #nnnn
			I16 = Fetch16();
			minx.SP.W.L = I16;
			return 16;
		case 0x6F: // UNSTABLE
			MinxCPU_OnException(EXCEPTION_UNSTABLE_INSTRUCTION, 0x6FCF);
			return 16;

		case 0x70: // MOV BA, [SP+#ss]
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			minx.BA.B.L = MinxCPU_OnRead(1, I16++);
			minx.BA.B.H = MinxCPU_OnRead(1, I16);
			return 24;
		case 0x71: // MOV HL, [SP+#ss]
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			minx.HL.B.L = MinxCPU_OnRead(1, I16++);
			minx.HL.B.H = MinxCPU_OnRead(1, I16);
			return 24;
		case 0x72: // MOV X, [SP+#ss]
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			minx.X.B.L = MinxCPU_OnRead(1, I16++);
			minx.X.B.H = MinxCPU_OnRead(1, I16);
			return 24;
		case 0x73: // MOV Y, [SP+#ss]
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			minx.Y.B.L = MinxCPU_OnRead(1, I16++);
			minx.Y.B.H = MinxCPU_OnRead(1, I16);
			return 24;

		case 0x74: // MOV [SP+#ss], BA
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, I16++, minx.BA.B.L);
			MinxCPU_OnWrite(1, I16, minx.BA.B.H);
			return 24;
		case 0x75: // MOV [SP+#ss], HL
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, I16++, minx.HL.B.L);
			MinxCPU_OnWrite(1, I16, minx.HL.B.H);
			return 24;
		case 0x76: // MOV [SP+#ss], X
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, I16++, minx.X.B.L);
			MinxCPU_OnWrite(1, I16, minx.X.B.H);
			return 24;
		case 0x77: // MOV [SP+#ss], Y
			I8A = Fetch8();
			I16 = minx.SP.W.L + S8_TO_16(I8A);
			MinxCPU_OnWrite(1, I16++, minx.Y.B.L);
			MinxCPU_OnWrite(1, I16, minx.Y.B.H);
			return 24;

		case 0x78: // MOV SP, [#nnnn]
			I16 = Fetch16();
			minx.SP.B.L = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16++);
			minx.SP.B.H = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16);
			return 24;

		case 0x79: // ??? #nn
		case 0x7A: // ??? #nn
		case 0x7B: // ??? #nn
			return CPUSPCF();

		case 0x7C: // MOV [#nnnn], SP
			I16 = Fetch16();
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16++, minx.SP.B.L);
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16, minx.SP.B.H);
			return 24;

		case 0x7D: case 0x7E: case 0x7F: // ??? #nn
		case 0x80: case 0x81: case 0x82: case 0x83:
		case 0x84: case 0x85: case 0x86: case 0x87:
		case 0x88: case 0x89: case 0x8A: case 0x8B:
		case 0x8C: case 0x8D: case 0x8E: case 0x8F:
		case 0x90: case 0x91: case 0x92: case 0x93:
		case 0x94: case 0x95: case 0x96: case 0x97:
		case 0x98: case 0x99: case 0x9A: case 0x9B:
		case 0x9C: case 0x9D: case 0x9E: case 0x9F:
		case 0xA0: case 0xA1: case 0xA2: case 0xA3:
		case 0xA4: case 0xA5: case 0xA6: case 0xA7:
		case 0xA8: case 0xA9: case 0xAA: case 0xAB:
		case 0xAC: case 0xAD: case 0xAE: case 0xAF:
			return CPUSPCF();

		case 0xB0: // PUSH A
			PUSH(minx.BA.B.L);
			return 12;
		case 0xB1: // PUSH B
			PUSH(minx.BA.B.H);
			return 12;
		case 0xB2: // PUSH L
			PUSH(minx.HL.B.L);
			return 12;
		case 0xB3: // PUSH H
			PUSH(minx.HL.B.H);
			return 12;

		case 0xB4: // POP A
			minx.BA.B.L = POP();
			return 12;
		case 0xB5: // POP B
			minx.BA.B.H = POP();
			return 12;
		case 0xB6: // POP L
			minx.HL.B.L = POP();
			return 12;
		case 0xB7: // POP H
			minx.HL.B.H = POP();
			return 12;
		case 0xB8: // PUSHA
			PUSH(minx.BA.B.H);
			PUSH(minx.BA.B.L);
			PUSH(minx.HL.B.H);
			PUSH(minx.HL.B.L);
			PUSH(minx.X.B.H);
			PUSH(minx.X.B.L);
			PUSH(minx.Y.B.H);
			PUSH(minx.Y.B.L);
			PUSH(minx.N.B.H);
			return 48;
		case 0xB9: // PUSHAX
			PUSH(minx.BA.B.H);
			PUSH(minx.BA.B.L);
			PUSH(minx.HL.B.H);
			PUSH(minx.HL.B.L);
			PUSH(minx.X.B.H);
			PUSH(minx.X.B.L);
			PUSH(minx.Y.B.H);
			PUSH(minx.Y.B.L);
			PUSH(minx.N.B.H);
			PUSH(minx.HL.B._I);
			PUSH(minx.X.B._I);
			PUSH(minx.Y.B._I);
			return 60;

		case 0xBA: case 0xBB: // ??? #n
			return CPUSPCF();

		case 0xBC: // POPA
			minx.N.B.H = POP();
			minx.Y.B.L = POP();
			minx.Y.B.H = POP();
			minx.X.B.L = POP();
			minx.X.B.H = POP();
			minx.HL.B.L = POP();
			minx.HL.B.H = POP();
			minx.BA.B.L = POP();
			minx.BA.B.H = POP();
			return 44;

		case 0xBD: // POPAX
			minx.Y.B._I = POP();
			minx.X.B._I = POP();
			minx.HL.B._I = POP();
			minx.N.B._I = minx.HL.B._I;
			minx.N.B.H = POP();
			minx.Y.B.L = POP();
			minx.Y.B.H = POP();
			minx.X.B.L = POP();
			minx.X.B.H = POP();
			minx.HL.B.L = POP();
			minx.HL.B.H = POP();
			minx.BA.B.L = POP();
			minx.BA.B.H = POP();
			return 56;

		case 0xBE: case 0xBF: // ??? #n
			return CPUSPCF();

		case 0xC0: // MOV BA, [HL]
			I16 = minx.HL.W.L;
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16++);
			minx.BA.B.H = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16);
			return 20;
		case 0xC1: // MOV HL, [HL]
			I16 = minx.HL.W.L;
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16++);
			minx.HL.B.H = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16);
			return 20;
		case 0xC2: // MOV X, [HL]
			I16 = minx.HL.W.L;
			minx.X.B.L = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16++);
			minx.X.B.H = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16);
			return 20;
		case 0xC3: // MOV Y, [HL]
			I16 = minx.HL.W.L;
			minx.Y.B.L = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16++);
			minx.Y.B.H = MinxCPU_OnRead(1, (minx.HL.B._I << 16) | I16);
			return 20;

		case 0xC4: // MOV [HL], BA
			I16 = minx.HL.W.L;
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16++, minx.BA.B.L);
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16, minx.BA.B.H);
			return 20;
		case 0xC5: // MOV [HL], HL
			I16 = minx.HL.W.L;
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16++, minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16, minx.HL.B.H);
			return 20;
		case 0xC6: // MOV [HL], X
			I16 = minx.HL.W.L;
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16++, minx.X.B.L);
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16, minx.X.B.H);
			return 20;
		case 0xC7: // MOV [HL], Y
			I16 = minx.HL.W.L;
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16++, minx.Y.B.L);
			MinxCPU_OnWrite(1, (minx.HL.B._I << 16) | I16, minx.Y.B.H);
			return 20;

		case 0xC8: case 0xC9: case 0xCA: case 0xCB: // MOV B, V
		case 0xCC: case 0xCD: case 0xCE: case 0xCF:
			minx.BA.B.H = minx.PC.B._I;
			return 12;

		case 0xD0: // MOV BA, [X]
			I16 = minx.X.W.L;
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16++);
			minx.BA.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 20;
		case 0xD1: // MOV HL, [X]
			I16 = minx.X.W.L;
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16++);
			minx.HL.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 20;
		case 0xD2: // MOV X, [X]
			I16 = minx.X.W.L;
			minx.X.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16++);
			minx.X.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 20;
		case 0xD3: // MOV Y, [X]
			I16 = minx.X.W.L;
			minx.Y.B.L = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16++);
			minx.Y.B.H = MinxCPU_OnRead(1, (minx.X.B._I << 16) | I16);
			return 20;

		case 0xD4: // MOV [X], BA
			I16 = minx.X.W.L;
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16++, minx.BA.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.BA.B.H);
			return 20;
		case 0xD5: // MOV [X], HL
			I16 = minx.X.W.L;
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16++, minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.HL.B.H);
			return 20;
		case 0xD6: // MOV [X], X
			I16 = minx.X.W.L;
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16++, minx.X.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.X.B.H);
			return 20;
		case 0xD7: // MOV [X], Y
			I16 = minx.X.W.L;
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16++, minx.Y.B.L);
			MinxCPU_OnWrite(1, (minx.X.B._I << 16) | I16, minx.Y.B.H);
			return 20;

		case 0xD8: // MOV BA, [Y]
			I16 = minx.Y.W.L;
			minx.BA.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16++);
			minx.BA.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 20;
		case 0xD9: // MOV HL, [Y]
			I16 = minx.Y.W.L;
			minx.HL.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16++);
			minx.HL.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 20;
		case 0xDA: // MOV X, [Y]
			I16 = minx.Y.W.L;
			minx.X.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16++);
			minx.X.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 20;
		case 0xDB: // MOV Y, [Y]
			I16 = minx.Y.W.L;
			minx.Y.B.L = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16++);
			minx.Y.B.H = MinxCPU_OnRead(1, (minx.Y.B._I << 16) | I16);
			return 20;

		case 0xDC: // MOV [Y], BA
			I16 = minx.Y.W.L;
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16++, minx.BA.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.BA.B.H);
			return 20;
		case 0xDD: // MOV [Y], HL
			I16 = minx.Y.W.L;
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16++, minx.HL.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.HL.B.H);
			return 20;
		case 0xDE: // MOV [Y], X
			I16 = minx.Y.W.L;
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16++, minx.X.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.X.B.H);
			return 20;
		case 0xDF: // MOV [Y], Y
			I16 = minx.Y.W.L;
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16++, minx.Y.B.L);
			MinxCPU_OnWrite(1, (minx.Y.B._I << 16) | I16, minx.Y.B.H);
			return 20;

		case 0xE0: // MOV BA, BA
			return 8;
		case 0xE1: // MOV BA, HL
			minx.BA.W.L = minx.HL.W.L;
			return 8;
		case 0xE2: // MOV BA, X
			minx.BA.W.L = minx.X.W.L;
			return 8;
		case 0xE3: // MOV BA, Y
			minx.BA.W.L = minx.Y.W.L;
			return 8;

		case 0xE4: // MOV HL, BA
			minx.HL.W.L = minx.BA.W.L;
			return 8;
		case 0xE5: // MOV HL, HL
			return 8;
		case 0xE6: // MOV HL, X
			minx.HL.W.L = minx.X.W.L;
			return 8;
		case 0xE7: // MOV HL, Y
			minx.HL.W.L = minx.Y.W.L;
			return 8;

		case 0xE8: // MOV X, BA
			minx.X.W.L = minx.BA.W.L;
			return 8;
		case 0xE9: // MOV X, HL
			minx.X.W.L = minx.HL.W.L;
			return 8;
		case 0xEA: // MOV X, X
			return 8;
		case 0xEB: // MOV X, Y
			minx.X.W.L = minx.Y.W.L;
			return 8;

		case 0xEC: // MOV Y, BA
			minx.Y.W.L = minx.BA.W.L;
			return 8;
		case 0xED: // MOV Y, HL
			minx.Y.W.L = minx.HL.W.L;
			return 8;
		case 0xEE: // MOV Y, X
			minx.Y.W.L = minx.X.W.L;
			return 8;
		case 0xEF: // MOV Y, Y
			return 8;

		case 0xF0: // MOV SP, BA
			minx.SP.W.L = minx.BA.W.L;
			return 8;
		case 0xF1: // MOV SP, HL
			minx.SP.W.L = minx.HL.W.L;
			return 8;
		case 0xF2: // MOV SP, X
			minx.SP.W.L = minx.X.W.L;
			return 8;
		case 0xF3: // MOV SP, Y
			minx.SP.W.L = minx.Y.W.L;
			return 8;

		case 0xF4: // MOV HL, SP
			minx.HL.W.L = minx.SP.W.L;
			return 8;
		case 0xF5: // MOV HL, PC
			minx.HL.W.L = minx.PC.W.L;
			return 8;
		case 0xF6: // ??? X
			minx.X.B.H = minx.PC.B._I;
			return 12;
		case 0xF7: // ??? Y
			minx.Y.B.H = minx.PC.B._I;
			return 12;

		case 0xF8: // MOV BA, SP
			minx.BA.W.L = minx.SP.W.L;
			return 8;
		case 0xF9: // MOV BA, PC
			minx.BA.W.L = minx.PC.W.L;
			return 8;

		case 0xFA: // MOV X, SP
			minx.X.W.L = minx.SP.W.L;
			return 8;

		case 0xFB: // NOTHING
		case 0xFC: // NOTHING
			return 12;
		case 0xFD: // MOV A, E
			minx.BA.B.L = minx.E;
			return 12;

		case 0xFE: // MOV Y, SP
			minx.Y.W.L = minx.SP.W.L;
			return 8;

		case 0xFF: // NOTHING
			return 64;

		default:
			MinxCPU_OnException(EXCEPTION_UNKNOWN_INSTRUCTION, (minx.IR << 8) + 0xCF);
			return 4;
	}
}

int CPUSPCE(void)
{
	// Read IR
	minx.IR = Fetch8();

	// Process instruction
	switch(minx.IR) {
		// TODO!
		default:
			MinxCPU_OnException(EXCEPTION_UNKNOWN_INSTRUCTION, (minx.IR << 16) + 0xCEFF);
			return 64;
	}
}

int CPUSPCF(void)
{
	// Read IR
	minx.IR = Fetch8();

	// Process instruction
	switch(minx.IR) {
		case 0x00: case 0x01: case 0x02: case 0x03: // Decrement BA
			minx.BA.W.L = DEC16(minx.BA.W.L);
			return 16;
		case 0x04: case 0x05: case 0x06: case 0x07: // Decrement BA if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.BA.W.L = DEC16(minx.BA.W.L);
			return 16;
		case 0x08: case 0x09: case 0x0A: case 0x0B: // Increment BA
			minx.BA.W.L = INC16(minx.BA.W.L);
			return 16;
		case 0x0C: case 0x0D: case 0x0E: case 0x0F: // Increment BA if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.BA.W.L = INC16(minx.BA.W.L);
			return 16;
		case 0x10: case 0x11: case 0x12: case 0x13: // Decrement BA
			minx.BA.W.L = DEC16(minx.BA.W.L);
			return 16;
		case 0x14: case 0x15: case 0x16: case 0x17: // Decrement BA if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.BA.W.L = DEC16(minx.BA.W.L);
			return 16;
		case 0x18: case 0x19: case 0x1A: case 0x1B: // Increment BA (Doesn't save result!!)
			INC16(minx.BA.W.L);
			return 16;
		case 0x1C: case 0x1D: case 0x1E: case 0x1F: // Increment BA if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.BA.W.L = INC16(minx.BA.W.L);
			return 16;

		case 0x20: case 0x21: case 0x22: case 0x23: // Decrement HL
			minx.HL.W.L = DEC16(minx.HL.W.L);
			return 16;
		case 0x24: case 0x25: case 0x26: case 0x27: // Decrement HL if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.HL.W.L = DEC16(minx.HL.W.L);
			return 16;
		case 0x28: case 0x29: case 0x2A: case 0x2B: // Increment HL
			minx.HL.W.L = INC16(minx.HL.W.L);
			return 16;
		case 0x2C: case 0x2D: case 0x2E: case 0x2F: // Increment HL if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.HL.W.L = INC16(minx.HL.W.L);
			return 16;
		case 0x30: case 0x31: case 0x32: case 0x33: // Decrement HL
			minx.HL.W.L = DEC16(minx.HL.W.L);
			return 16;
		case 0x34: case 0x35: case 0x36: case 0x37: // Decrement HL if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.HL.W.L = DEC16(minx.HL.W.L);
			return 16;
		case 0x38: case 0x39: case 0x3A: case 0x3B: // Increment HL (Doesn't save result!!)
			INC16(minx.HL.W.L);
			return 16;
		case 0x3C: case 0x3D: case 0x3E: case 0x3F: // Increment HL if Carry = 0
			if (!(minx.F & MINX_FLAG_CARRY)) minx.HL.W.L = INC16(minx.HL.W.L);
			return 16;

		case 0x40: case 0x41: // Decrement X
			minx.X.W.L = DEC16(minx.X.W.L);
			return 16;
		case 0x42: case 0x43: // Decrement Y
			minx.X.W.L = DEC16(minx.X.W.L);
			return 16;
		case 0x44: case 0x45: // Decrement SP
			minx.SP.W.L = DEC16(minx.SP.W.L);
			return 16;
		case 0x46: case 0x47: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 16;

		case 0x48: case 0x49: // Increment X
			minx.X.W.L = INC16(minx.X.W.L);
			return 16;
		case 0x4A: case 0x4B: // Increment Y
			minx.X.W.L = INC16(minx.X.W.L);
			return 16;
		case 0x4C: case 0x4D: // Increment SP
			minx.SP.W.L = INC16(minx.SP.W.L);
			return 16;
		case 0x4E: case 0x4F: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 16;

		case 0x50: case 0x51: // Decrement X
			minx.X.W.L = DEC16(minx.X.W.L);
			return 16;
		case 0x52: case 0x53: // Decrement Y
			minx.X.W.L = DEC16(minx.X.W.L);
			return 16;
		case 0x54: case 0x55: // Decrement SP
			minx.SP.W.L = DEC16(minx.SP.W.L);
			return 16;
		case 0x56: case 0x57: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 16;

		case 0x58: case 0x59: // Increment X
			minx.X.W.L = INC16(minx.X.W.L);
			return 16;
		case 0x5A: case 0x5B: // Increment Y
			minx.X.W.L = INC16(minx.X.W.L);
			return 16;
		case 0x5C: case 0x5D: // Increment SP
			minx.SP.W.L = INC16(minx.SP.W.L);
			return 16;
		case 0x5E: case 0x5F: // CRASH
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 16;

		case 0x60: case 0x61: case 0x62: case 0x63: // CRASH
		case 0x64: case 0x65: case 0x66: case 0x67:
		case 0x68: case 0x69: case 0x6A: case 0x6B:
		case 0x6C: case 0x6D: case 0x6E: case 0x6F:
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 16;

		case 0x70: // BA = (0x4D << 8) | V
			minx.BA.W.L = 0x4D00 | minx.PC.B._I;
			return 24;
		case 0x71: // HL = (0x4D << 8) | V
			minx.HL.W.L = 0x4D00 | minx.PC.B._I;
			return 24;
		case 0x72: // X = (0x4D << 8) | V
			minx.X.W.L = 0x4D00 | minx.PC.B._I;
			return 24;
		case 0x73: // Y = (0x4D << 8) | V
			minx.Y.W.L = 0x4D00 | minx.PC.B._I;
			return 24;

		case 0x74: case 0x75: case 0x76: case 0x77: // NOTHING
			return 24;

		case 0x78: case 0x79: case 0x7A: case 0x7B: // CRASH
		case 0x7C: case 0x7D: case 0x7E: case 0x7F:
		case 0x80: case 0x81: case 0x82: case 0x83:
		case 0x84: case 0x85: case 0x86: case 0x87:
		case 0x88: case 0x89: case 0x8A: case 0x8B:
		case 0x8C: case 0x8D: case 0x8E: case 0x8F:
		case 0x90: case 0x91: case 0x92: case 0x93:
		case 0x94: case 0x95: case 0x96: case 0x97:
		case 0x98: case 0x99: case 0x9A: case 0x9B:
		case 0x9C: case 0x9D: case 0x9E: case 0x9F:
		case 0xA0: case 0xA1: case 0xA2: case 0xA3:
		case 0xA4: case 0xA5: case 0xA6: case 0xA7:
		case 0xA8: case 0xA9: case 0xAA: case 0xAB:
		case 0xAC: case 0xAD: case 0xAE: case 0xAF:
			//MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 24;

		case 0xB0: case 0xB1: case 0xB2: case 0xB3: // NOTHING
			return 12;

		case 0xB4: case 0xB5: case 0xB6: case 0xB7: // CRASH
		case 0xB8: case 0xB9: case 0xBA: case 0xBB:
		case 0xBC: case 0xBD: case 0xBE: case 0xBF:
			//MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 12;

		case 0xC0: // BA = (0x20 << 8) | V
			minx.BA.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xC1: // HL = (0x20 << 8) | V
			minx.HL.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xC2: // X = (0x20 << 8) | V
			minx.X.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xC3: // Y = (0x20 << 8) | V
			minx.Y.W.L = 0x2000 | minx.PC.B._I;
			return 20;

		case 0xC4: case 0xC5: case 0xC6: case 0xC7: // NOTHING
			return 20;

		case 0xC8: case 0xC9: case 0xCA: case 0xCB: // CRASH
		case 0xCC: case 0xCD: case 0xCE: case 0xCF:
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 20;

		case 0xD0: // BA = (0x20 << 8) | V
			minx.BA.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xD1: // HL = (0x20 << 8) | V
			minx.HL.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xD2: // X = (0x20 << 8) | V
			minx.X.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xD3: // Y = (0x00 << 8) | V ? (EH!?)
			minx.Y.W.L = 0x0000 | minx.PC.B._I;
			return 20;

		case 0xD4: case 0xD5: case 0xD6: case 0xD7: // NOTHING
			return 20;

		case 0xD8: // BA = (0x20 << 8) | V
			minx.BA.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xD9: // HL = (0x20 << 8) | V
			minx.HL.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xDA: // X = (0x20 << 8) | V
			minx.X.W.L = 0x2000 | minx.PC.B._I;
			return 20;
		case 0xDB: // Y = (0x20 << 8) | V
			minx.Y.W.L = 0x2000 | minx.PC.B._I;
			return 20;

		case 0xDC: case 0xDD: case 0xDE: case 0xDF: // NOTHING
			return 20;
		
		case 0xE0: case 0xE1: case 0xE2: case 0xE3: // CRASH
		case 0xE4: case 0xE5: case 0xE6: case 0xE7:
		case 0xE8: case 0xE9: case 0xEA: case 0xEB:
		case 0xEC: case 0xED: case 0xEE: case 0xEF:
		case 0xF0: case 0xF1: case 0xF2: case 0xF3:
		case 0xF4: case 0xF5: case 0xF6: case 0xF7:
		case 0xF8: case 0xF9: case 0xFA: case 0xFB:
		case 0xFC: case 0xFD: case 0xFE: case 0xFF:
			MinxCPU_OnException(EXCEPTION_CRASH_INSTRUCTION, (minx.IR << 16) | 0xBFCF);
			return 24;

		default:
			MinxCPU_OnException(EXCEPTION_UNKNOWN_INSTRUCTION, (minx.IR << 16) + 0xBFCF);
			return 64;
	}
}