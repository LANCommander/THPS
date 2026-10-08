/* FUN_8006edb8 (0x8006edb8) */
#include "names.h"
typedef struct {
	char pad[20];
	int *p14;
	char q[64 - 24];
} S;

extern S PSXRegion[];
extern int *DAT_800c09a8[];

void Mem_Delete(int *);

void FUN_8006edb8(int i) {
	int *d = PSXRegion[i].p14;
	int *s = DAT_800c09a8[i];

	do {
		int j = 0;

		goto test;
	body:
		*d++ = *s++;
	test:
		if (j < 7500) {
			j++;
			goto body;
		}
	} while (0);

	Mem_Delete(DAT_800c09a8[i]);

	DAT_800c09a8[i] = 0;
}
