extern u8 MinxWRAM[4096];
extern u8 MinxMMIO[256];
extern u8 MinxBIOS[4096];
extern u8 MinxROM[2097152];
extern u8 MinxOAM[95];

#define PMR_REG_KEYPAD MinxMMIO[0x52]
extern void GetKeypad();
extern void MergeKeyData();

#define PMR_PRC_SCROLL_Y MinxMMIO[0x85]
#define PMR_PRC_SCROLL_X MinxMMIO[0x86]

#define PMR_IRQ_PRI1		(MinxWRAM[0x20])
#define PMR_IRQ_PRI2		(MinxWRAM[0x21])
#define PMR_IRQ_PRI3		(MinxWRAM[0x22])
#define PMR_IRQ_ENA1		(MinxWRAM[0x23])
#define PMR_IRQ_ENA2		(MinxWRAM[0x24])
#define PMR_IRQ_ENA3		(MinxWRAM[0x25])
#define PMR_IRQ_ENA4		(MinxWRAM[0x26])
#define PMR_IRQ_ACT1		(MinxWRAM[0x27])
#define PMR_IRQ_ACT2		(MinxWRAM[0x28])
#define PMR_IRQ_ACT3		(MinxWRAM[0x29])
#define PMR_IRQ_ACT4		(MinxWRAM[0x2A])

#define PMR_SYS_CTRL1		(MinxWRAM[0x00])
#define PMR_SYS_CTRL2		(MinxWRAM[0x01])
#define PMR_SYS_CTRL3		(MinxWRAM[0x02])