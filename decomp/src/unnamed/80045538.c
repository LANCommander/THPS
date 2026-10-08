/* Trig_SendPulseToNode__Fi (0x80045538) */
#include "names.h"
typedef struct {
	int x, y, z, pad;
} V;

typedef struct {
	unsigned short w0, w2, w4, w6;
	unsigned char b8, p9, b10, p11, b12, p13, b14, p15, b16, p17, b18;
} P;

typedef struct {
	int a;
	char p[3];
	unsigned char f7;
} CP;

short **DAT_800d19e8;

extern int DAT_800d186c;

void Trig_CreateObject(int, short **);
CP *GetCommandPoint(int, short **);
void ExecuteCommandList(int, int, int);
P *Trig_GetPosition(V *, int);
int __nw__4CBitUi(int);
void CLight_ctor(int, V *, int, int, int, int, int, int, int, int, int, int, int);
void TrickOb_DarkenNode(int, short **);
int __nw__6CClassUi(int, short **);
void FUN_8004f684(int, int);

void Trig_SendPulseToNode(int idx) {
	V v;
	P *p;
	CP *cp;
	int o, o2;

	switch (*DAT_800d19e8[idx]) {
		case 5:
		case 7:
		case 1:
			Trig_CreateObject(idx, DAT_800d19e8);
			break;
		case 6:
			cp = GetCommandPoint(idx, DAT_800d19e8);
			cp->f7 = cp->f7 + 1;
			ExecuteCommandList(cp->a, idx, 0);
			break;
		case 501:
			p = Trig_GetPosition(&v, idx);
			DAT_800d186c = 0;
			o = __nw__4CBitUi(100);

			if (o)
				CLight_ctor(o, &v, idx, p->w0, p->w2, p->w4, p->w6, p->b8, p->b10, p->b12, p->b14,
				             p->b16, p->b18);

			DAT_800d186c = 1;
			break;
		case 10:
		case 11:
			o2 = __nw__6CClassUi(44, DAT_800d19e8);

			if (o2)
				FUN_8004f684(o2, idx);

			break;
		case 14:
		case 12:
			TrickOb_DarkenNode(idx, DAT_800d19e8);
			break;
	}
}
