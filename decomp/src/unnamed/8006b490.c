/* __4CCarPsii (0x8006b490) */
#include "names.h"
extern char DAT_800d1e2c[], DAT_800d1e34[], DAT_800d1e3c[], DAT_800a232c[], DAT_800a233c[];
extern int DAT_800d1998;

int DAT_800d1e44;

int CBaddy_ctor(char *);
void CItem_InitItem(char *, char *);
int SFX_PlayX(int, int, int);
void CBody_AttachTo(char *, void *);
void CSuper_CycleAnim(char *, int, int);
short *CBody_SquirtPos(char *, short *);
void CBody_SquirtAngles(char *, short *);
char *Trig_GetLinksPointer(int);
void Trig_GetPosition(char *, int);

char *CCar_ctor(char *t, short *p, int id, int ty) {
	int x;
	unsigned short v;

	CBaddy_ctor(t);

	*(char **)(t + 0x48) = DAT_800a233c;
	*(short *)(t + 0x3a) = ty;
	*(int *)(t + 0x214) = 1;

	switch (ty) {
		case 0xd5:
			CItem_InitItem(t, DAT_800d1e2c);

			x = 0x71;
			goto L;
		case 0xd6:
			*(int *)(t + 0x214) = 0;
			CItem_InitItem(t, DAT_800a232c);
			break;
		case 0xd7:
			CItem_InitItem(t, DAT_800d1e34);

			x = 0x81;
			goto L;
		case 0xd8:
			CItem_InitItem(t, DAT_800d1e3c);

			x = 0x86;
		L:
			*(int *)(t + 0x210) = SFX_PlayX(x, 0, 0);
			break;
	}

	DAT_800d1e44 = 300;
	CBody_AttachTo(t, &DAT_800d1998);

	*(int *)(t + 0x150) = 0x10000;
	CSuper_CycleAnim(t, 0, 1);

	*(short *)(t + 0x1e8) = 52;
	*(short *)(t + 0x1ea) = 32;
	*(short *)(t + 0xe6) = 60;
	CBody_SquirtAngles(t, CBody_SquirtPos(t, p));

	*(short *)(t + 0xe2) = id;
	v = *(unsigned short *)(Trig_GetLinksPointer(id) + 2);
	*(int *)(t + 0x21c) = v;
	Trig_GetPosition(t + 4, v);

	*(int *)(t + 8) = *(int *)(t + 8) + 0xfff92000;
	return t;
}
