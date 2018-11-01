extern void menu();

typedef union {
	struct {
		u8 X;
		u8 _I;
		u8 H;
		u8 L;
	} B;
	struct {
		u16 H;
		u16 L;
	} W;
	u32 D;
} MinxRegx;

int CPU();

typedef struct {
	// Registers
	MinxRegx BA;			// Registers A, B
	MinxRegx HL;			// Registers L, H, I
	MinxRegx X;			// Registers X, XI
	MinxRegx Y;			// Registers Y, YI
	MinxRegx SP;			// Register SP
	MinxRegx PC;			// Registers PC, V
	MinxRegx N;			// for [N+#nn], I is written here too
	u8 U1;			// V Shadow 1
	u8 U2;			// V Shadow 2
	u8 F;			// Flags
	u8 E;			// Exception
	u8 IR;			// Last Instruction Register (for open-bus)
	u8 Shift_U;		// Shift U, set to 2 when: U modify, branch, return
	u8 Status;			// CPU Status (0 = Normal, 1 = Halt, 2 = Stoped, 3 = IRQ)
	u8 IRQ_Vector;		// IRQ Vector when Status is IRQ
	u8 Reserved[28];		// Reserved bytes
} TMinxCPU;

#define MINX_FLAG_ZERO    	0x01
#define MINX_FLAG_CARRY   	0x02
#define MINX_FLAG_OVERFLOW	0x04
#define MINX_FLAG_SIGN    	0x08
#define MINX_FLAG_BCD     	0x10
#define MINX_FLAG_NIBBLE  	0x20
#define MINX_FLAG_INTFLG  	0x40
#define MINX_FLAG_INTOFF  	0x80

#define MINX_FLAG_SAVE_NUL	0xF0
#define MINX_FLAG_SAVE_O  	0xF4
#define MINX_FLAG_SAVE_CO 	0xF6
#define MINX_FLAG_SAVE_COS	0xFE

enum {
	MINX_SLEEP_HALT,
	MINX_SLEEP_STOP
};

enum {
	EXCEPTION_UNKNOWN_INSTRUCTION,
	EXCEPTION_CRASH_INSTRUCTION,
	EXCEPTION_UNSTABLE_INSTRUCTION,
	EXCEPTION_DIVISION_BY_ZERO
};

// Status reasons
enum {
	MINX_STATUS_NORMAL = 0, // Normal operation
	MINX_STATUS_HALT = 1,   // CPU during HALT
	MINX_STATUS_STOP = 2,   // CPU during STOP
	MINX_STATUS_IRQ = 3,    // Delay caused by hardware IRQ
};

extern TMinxCPU minx;

extern int PM_ROM_Mask;

extern uint8_t MinxCPU_OnRead(int cpu, int addr);
extern void MinxCPU_OnWrite(int cpu, uint32_t addr, uint8_t data);

extern u8 ADD8(uint8_t A, uint8_t B);
extern u8 ADC8(uint8_t A, uint8_t B);
extern u8 SUB8(uint8_t A, uint8_t B);
extern u8 SBC8(uint8_t A, uint8_t B);
extern u8 OR8(uint8_t A, uint8_t B);
extern u8 AND8(uint8_t A, uint8_t B);
extern u8 XOR8(uint8_t A, uint8_t B);
extern void JMPS(uint16_t OFFSET);
extern void JMPU(uint16_t ADDR);
extern u8 SWAP(uint8_t A);
extern u8 POP(void);
extern void PUSH(uint8_t A);
extern u8 Fetch8(void);
extern u16 Fetch16(void);
extern void CALLS(uint16_t OFFSET);
extern u16 S8_TO_16(int8_t a);
u8 DEC8(uint8_t A);
u16 DEC16(uint16_t A);
u8 INC8(uint8_t A);
u16 INC16(uint16_t A);
extern u16 SUB16(uint16_t A, uint16_t B);
void DIV(void);
void MUL(void);
void Set_U(uint8_t val);
void STOP(void);
void HALT(void);
u16 ADD16(uint16_t A, uint16_t B);
u16 ADC16(uint16_t A, uint16_t B);
u8 SAL(uint8_t A);
u8 SHL(uint8_t A);
u8 SAR(uint8_t A);
u8 SHR(uint8_t A);
u8 ROLC(uint8_t A);
u8 ROL(uint8_t A);
u8 RORC(uint8_t A);
u8 ROR(uint8_t A);
u8 MNOT(uint8_t A);
u8 NEG(uint8_t A);
u16 SBC16(uint16_t A, uint16_t B);

void MinxCPU_OnIRQAct(uint8_t intr);
void MinxIRQ_OnIRQ(uint8_t intr);
void MinxCPU_OnIRQHandle(uint8_t cpuflag, uint8_t shift_u);
int MinxIRQ_Create(void);
void MinxIRQ_Destroy(void);
void MinxIRQ_Reset(int hardreset);
void MinxIRQ_SetIRQ(uint8_t intr);
uint8_t MinxIRQ_ReadReg(int cpu, uint8_t reg);
void MinxIRQ_WriteReg(int cpu, uint8_t reg, uint8_t val);
void MinxIRQ_Process(void);
int MinxCPU_CallIRQ(uint8_t addr);
void MinxCPU_OnException(int type, uint32_t ir);