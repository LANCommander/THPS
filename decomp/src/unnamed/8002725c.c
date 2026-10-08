/* __10CGPolyLinei (0x8002725c) */
#include "names.h"
typedef struct {
	int x, y, z;
} V;

typedef struct {
	V v;
	int w;
} E;

extern char __vt_10CGPolyLine[];
extern V ZeroVector;
extern char GPolyLineList[8];

void CBit_ctor(char *p);
char *Mem_NewX(int a, int b, int c);
void CBit_AttachTo(char *p, char *q);

char *CGPolyLine_ctor(char *p, int n) {
	int i;

	CBit_ctor(p);

	*(char **)(p + 68) = __vt_10CGPolyLine;
	*(char **)(p + 76) = Mem_NewX(n << 4, 0, 1);

	for (i = 0; i < n; i++) {
		(*(E **)(p + 76))[i].w = 0x50ffffff;
		(*(E **)(p + 76))[i].v = ZeroVector;
	}

	*(int *)(p + 72) = n;
	CBit_AttachTo(p, GPolyLineList);

	p[92] = 255;
	p[93] = 255;
	p[94] = 255;
	p[95] = 80;
	return p;
}
