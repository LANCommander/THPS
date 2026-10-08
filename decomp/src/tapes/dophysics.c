/* DoPhysics__5CTape (0x8007333c) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

extern short rcossin_tbl[] __attribute__((section(".data")));
void __apl__8CSVectorRC8CSVector(char *, char *);
void CSVector_Mask(char *);

void CTape_DoPhysics(char *t) {
	__apl__8CSVectorRC8CSVector(t + 0x10, t + 0x88);
	CSVector_Mask(t + 0x10);

	*(V *)(t + 4) = *(V *)(t + 0x180);
	*(int *)(t + 8) += (*(unsigned short *)(t + 0x190) *
	                    rcossin_tbl[(*(unsigned short *)(t + 0x18c) & 0xfff) * 2] / 4096)
	                   << 12;
	*(unsigned short *)(t + 0x18c) += *(unsigned short *)(t + 0x192);
}
