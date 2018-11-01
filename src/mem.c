#include <libheart.h>

const u8 MinxBIOS[4096];
u8 MinxWRAM[4096] HRT_EWRAM_DATA;
u8 MinxMMIO[256] HRT_EWRAM_DATA;
u8 MinxOAM[95] HRT_EWRAM_DATA;
const u8 MinxROM[0x124] = {
0xB4,0x20,0xDD,0x80,0x0A,0xDD,0x81,0x09,0xC6,0xC8,0x22,0xBE,0x82,0x20,0xB0,0x01,0xCE,0xD4,0x00,0x13,0xCE,0xD4,0x01,0x13,0xF2,0x97,0x00,0xC6,0xA1,0x22,0xCE,0xD0,0x00,0x13,0xCE,0xD1,0x01,0x13,0xF2,0x98,0x00,0xF2,0xB1,0x00,0xF2,0xA6,0x00,0xDC,0x52,0x20,0xEE,0x16,0x00,0xDC,0x52,0x40,0xEE,0x24,0x00,0xDC,0x52,0x08,0xEE,0x32,0x00,0xDC,0x52,0x10,0xEE,0x40,0x00,0xF3,0xD2,0xFF,0xCE,0xD0,0x00,0x13,0x32,0x01,0xCE,0xE0,0xC9,0xF2,0x45,0x00,0x88,0xCE,0xD4,0x00,0x13,0xF3,0xBE,0xFF,0xCE,0xD0,0x00,0x13,0x32,0x0A,0xCE,0xE2,0xB5,0xF2,0x31,0x00,0x80,0xCE,0xD4,0x00,0x13,0xF3,0xAA,0xFF,0xCE,0xD0,0x01,0x13,0x32,0x01,0xCE,0xE0,0xA1,0xF2,0x1D,0x00,0x88,0xCE,0xD4,0x01,0x13,0xF3,0x96,0xFF,0xCE,0xD0,0x01,0x13,0x32,0x06,0xCE,0xE2,0x8D,0xF2,0x09,0x00,0x80,0xCE,0xD4,0x01,0x13,0xF3,0x82,0xFF,0xCF,0xB0,0xCF,0xB1,0xC6,0xA0,0x22,0xCE,0xD0,0x00,0x13,0xCE,0xD1,0x01,0x13,0xF2,0x15,0x00,0xCF,0xB5,0xCF,0xB4,0xF8,0xC6,0xA2,0x22,0xC7,0x60,0x13,0xB1,0x60,0x46,0xCE,0x47,0x82,0xF5,0xFB,0xF8,0xCF,0xB0,0xCF,0xB1,0x02,0x0C,0xF5,0xFD,0xC7,0x60,0x13,0x50,0x4E,0xCE,0x4F,0xCF,0xB5,0xCF,0xB4,0xF8,0x44,0x52,0x32,0xFF,0xEE,0xFA,0xFF,0xF8,0x44,0x52,0x32,0xFF,0xEF,0xFA,0xFF,0xF8,0x00,0x01,0x02,0x57,0x72,0x69,0x74,0x74,0x65,0x6E,0x20,0x62,0x79,0x20,0x53,0x65,0x62,0x61,0x73,0x74,0x69,0x61,0x6E,0x20,0x4D,0x69,0x68,0x61,0x69,0x2C,0x20,0x32,0x30,0x31,0x35,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7A,0x86,0x94,0xE4,0xE4,0x94,0x86,0x7A,0x00,0x00,0x18,0x24,0x2C,0x18,0x00,0x00
};

int PM_ROM_Mask = 0;