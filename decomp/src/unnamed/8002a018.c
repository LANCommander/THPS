/* _._7CRibbon (0x8002a018) */
#include "names.h"
typedef struct {
	char pad[8];
	short adj;
	short pad2;
	void (*fn)(char *, int);
} VT;

extern char DAT_8009f6b8[];

void Mem_Delete(char *p);
void FUN_80027fa4(char *p, int a);
void __dl__4CBitPv(char *p);

void FUN_8002a018(char *p, int f) {
	int i;

	*(char **)(p + 68) = DAT_8009f6b8;

	for (i = 0; i < *(int *)(p + 72); i++) {
		char *o = ((char **)*(char **)(p + 92))[i];

		if (o) {
			VT *v = *(VT **)(o + 68);

			v->fn(o + v->adj, 3);
		}
	}

	Mem_Delete(*(char **)(p + 92));
	Mem_Delete(*(char **)(p + 88));
	FUN_80027fa4(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
