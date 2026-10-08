/* Bit_DeleteAll__Fv (0x80027b28) */
#include "names.h"
void *DAT_800d18cc;
void *DAT_800d18d0;
void *DAT_800d18d4;
void *DAT_800d18d8;
void *DAT_800d18f4;
void *DAT_800d18f8;
void *DAT_800d18dc;
void *DAT_800d18e0;
void *DAT_800d18e4;
void *DAT_800d18e8;
void *DAT_800d18ec;
void *DAT_800d18fc;
void *DAT_800d18f0;

void DeleteBitList(void *);

void Bit_DeleteAll(void) {
	DeleteBitList(DAT_800d18cc);
	DeleteBitList(DAT_800d18d0);
	DeleteBitList(DAT_800d18d4);
	DeleteBitList(DAT_800d18d8);
	DeleteBitList(DAT_800d18f4);
	DeleteBitList(DAT_800d18f8);
	DeleteBitList(DAT_800d18dc);
	DeleteBitList(DAT_800d18e0);
	DeleteBitList(DAT_800d18e4);
	DeleteBitList(DAT_800d18e8);
	DeleteBitList(DAT_800d18ec);
	DeleteBitList(DAT_800d18fc);
	DeleteBitList(DAT_800d18f0);
}
