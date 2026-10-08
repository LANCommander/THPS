/* FUN_800543d4 (0x800543d4) */
struct VT {
	char pad[8];
	short off;
	short pad2;
	void (*fn)(char *, int);
};

typedef struct {
	struct VT *vt;
} O;

extern int DAT_800d1afc;
extern int DAT_800d33c4[];
extern O *DAT_800d36a4[][15];

O *DAT_800d22dc;
int DAT_800d22e4;

void FUN_8004cdd0(void);
void FUN_8004d5d0(int);

void FUN_800543d4(void) {
	int i, j;
	O *o;

	if (DAT_800d1afc)
		FUN_8004cdd0();

	for (i = 0; i < 3; i++) {
		for (j = 0; j < DAT_800d33c4[i]; j++) {
			o = DAT_800d36a4[i][j];

			if (o) {
				o->vt->fn((char *)o + o->vt->off, 3);

				DAT_800d36a4[i][j] = 0;
			}
		}
	}

	if (DAT_800d22e4)
		FUN_8004d5d0(DAT_800d22e4);

	o = DAT_800d22dc;

	if (o)
		o->vt->fn((char *)o + o->vt->off, 3);
}
