/* Bit_Init__Fv (0x800279cc) */
#include "names.h"
int DAT_800d1868;
int DAT_800d18cc;
int DAT_800d18d0;
int DAT_800d18d4;
int DAT_800d18d8;
int DAT_800d18f4;
int DAT_800d18f8;
int DAT_800d18dc;
int DAT_800d18e0;
int DAT_800d18e4;
int DAT_800d18e8;
int DAT_800d18ec;
int DAT_800d18fc;
int DAT_800d18f0;
int DAT_800d1900;
int DAT_800d18a0;

extern int DAT_800d1420 __attribute__((section(".data")));

extern char DAT_800d1898[];
extern char *DAT_800a7220[];
extern int DAT_800a7238[];

int FUN_8008f72c(int, int, int, int);
void FUN_80092f30(int *, int, int, int);
int Spool_FindAnim(char *);
int Spool_FindTextureEntry(unsigned);

void Bit_Init(void) {
	int i;

	DAT_800d1868 = 0;
	DAT_800d18cc = 0;
	DAT_800d18d0 = 0;
	DAT_800d18d4 = 0;
	DAT_800d18d8 = 0;
	DAT_800d18f4 = 0;
	DAT_800d18f8 = 0;
	DAT_800d18dc = 0;
	DAT_800d18e0 = 0;
	DAT_800d18e4 = 0;
	DAT_800d18e8 = 0;
	DAT_800d18ec = 0;
	DAT_800d18fc = 0;
	DAT_800d18f0 = 0;
	FUN_80092f30(&DAT_800d1900, 1, 1, FUN_8008f72c(0, 1, 0, 0));

	for (i = 0; i < 6; i++)
		DAT_800a7238[i] = Spool_FindAnim(DAT_800a7220[i]);

	DAT_800d1420 = Spool_FindAnim(DAT_800d1898);
	DAT_800d18a0 = Spool_FindTextureEntry(0x2a3b2550);
}
