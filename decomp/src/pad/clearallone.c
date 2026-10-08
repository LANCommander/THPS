/* Pad_ClearAllOne__Fi (0x80070960) */
#include "names.h"
extern char DAT_800c0a48[];

extern void Pad_Clear(char *);

void Pad_ClearAllOne__Fi(int i) {
	int o = i * 0x16c;
	char *p = DAT_800c0a48 + o;

	Pad_Clear(p);

	*(int *)(DAT_800c0a48 + o + 0x150) = 0;
	p[0x14b] = 0;
	p[0x14a] = 0;
	p[0x149] = 0;
	p[0x148] = 0;
}
