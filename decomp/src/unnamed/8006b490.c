/* __4CCarPsii (0x8006b490) */
extern char DAT_800d1e2c[], DAT_800d1e34[], DAT_800d1e3c[], DAT_800a232c[], DAT_800a233c[];
extern int DAT_800d1998;

int DAT_800d1e44;

int __6CBaddy(char *);
void InitItem__5CItemPc(char *, char *);
int SFX_PlayX__FUisi(int, int, int);
void AttachTo__5CBodyPP5CBody(char *, void *);
void CycleAnim__6CSuperiSc(char *, int, int);
short *SquirtPos__5CBodyPs(char *, short *);
void SquirtAngles__5CBodyPs(char *, short *);
char *Trig_GetLinksPointer__Fi(int);
void Trig_GetPosition__FR7CVectori(char *, int);

char *__4CCarPsii(char *t, short *p, int id, int ty) {
	int x;
	unsigned short v;

	__6CBaddy(t);

	*(char **)(t + 0x48) = DAT_800a233c;
	*(short *)(t + 0x3a) = ty;
	*(int *)(t + 0x214) = 1;

	switch (ty) {
		case 0xd5:
			InitItem__5CItemPc(t, DAT_800d1e2c);

			x = 0x71;
			goto L;
		case 0xd6:
			*(int *)(t + 0x214) = 0;
			InitItem__5CItemPc(t, DAT_800a232c);
			break;
		case 0xd7:
			InitItem__5CItemPc(t, DAT_800d1e34);

			x = 0x81;
			goto L;
		case 0xd8:
			InitItem__5CItemPc(t, DAT_800d1e3c);

			x = 0x86;
		L:
			*(int *)(t + 0x210) = SFX_PlayX__FUisi(x, 0, 0);
			break;
	}

	DAT_800d1e44 = 300;
	AttachTo__5CBodyPP5CBody(t, &DAT_800d1998);

	*(int *)(t + 0x150) = 0x10000;
	CycleAnim__6CSuperiSc(t, 0, 1);

	*(short *)(t + 0x1e8) = 52;
	*(short *)(t + 0x1ea) = 32;
	*(short *)(t + 0xe6) = 60;
	SquirtAngles__5CBodyPs(t, SquirtPos__5CBodyPs(t, p));

	*(short *)(t + 0xe2) = id;
	v = *(unsigned short *)(Trig_GetLinksPointer__Fi(id) + 2);
	*(int *)(t + 0x21c) = v;
	Trig_GetPosition__FR7CVectori(t + 4, v);

	*(int *)(t + 8) = *(int *)(t + 8) + 0xfff92000;
	return t;
}
