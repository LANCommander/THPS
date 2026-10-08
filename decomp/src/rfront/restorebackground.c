/* Front_RestoreBackground__Fv (0x800114a8) */
typedef struct {
	void *spr;
	int pad;
	short x, y;
	int pad2;
	int type;
} SBg;

int DAT_800d1118;

extern SBg DAT_800a4434[];

void draw__6Spriteiiiiii(void *, int, int, int, int, int, int);

void Front_RestoreBackground(void) {
	int i;

	for (i = 0; i < DAT_800d1118; i++) {
		if (DAT_800a4434[i].type == 2)
			draw__6Spriteiiiiii(DAT_800a4434[i].spr, DAT_800a4434[i].x, DAT_800a4434[i].y, 0, -1,
			                    -1, -1);
	}
}
