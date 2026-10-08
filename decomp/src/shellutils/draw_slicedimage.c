/* draw__11SlicedImageiiiiiiii (0x80062e20) */
/* SlicedImage::draw (SHELLUTILS.CPP), as C. Emits one POLY_FT4 per slice of the image at (x, y),
   flat or tinted, optionally semi-transparent, into the panel OT or a per-call layer. The tpage is
   libgpu's getTPage on the slice RECT. */
typedef struct {
	char pad[0x18];
	char *tab;
	int w;
	int h;
	int depth;
	unsigned short f28;
} SP;

typedef struct {
	unsigned addr : 24;
	unsigned len : 8;
} TG;

extern char DAT_800a20d8[];

int DAT_800d1d94;

extern char *DAT_800d1a48;
extern char *DAT_800d1a54;

int FUN_8008c190(char *, int);
int FUN_8008c880(char *);

typedef struct {
	short x, y, w, h;
} RECT;

#define getTPage(tp, abr, x, y)                                                                    \
	((((tp) & 0x3) << 7) | (((abr) & 0x3) << 5) | (((y) & 0x100) >> 4) | (((x) & 0x3ff) >> 6) |    \
	 (((y) & 0x200) << 2))
#define EN(o) ((char *)((int)(o) + (int)p->tab))

void draw__11SlicedImageiiiiiiii(SP *p, int x0, int y, int fb, int c4, int c5, int c6, int c7, int c8) {
	int i, j, k, off, s2, x;
	char *pk;
	unsigned *ot;
	int t0;

	t0 = 0;

	if ((unsigned)DAT_800d1d94 >= 0x2000)
		FUN_8008c190(DAT_800a20d8, DAT_800d1d94);

	if (fb)
		ot = (unsigned *)(DAT_800d1a48 + 0x84);
	else
		ot = (unsigned *)(DAT_800d1a48 + (DAT_800d1d94 * 4 + 0x8c));

	i = 0;
	s2 = p->depth == 8;

	if (p->h > 0) {
		do {
			x = x0;
			j = 0;

			if (p->w > 0) {
				do {
					pk = DAT_800d1a54;
					DAT_800d1a54 = pk + 40;
					pk[3] = 9;
					pk[7] = 44;

					if (c4 == -1) {
						pk[4] = 0;
						pk[5] = 0;
						pk[6] = 0;
					} else {
						pk[4] = c4;
						pk[5] = c5;
						pk[6] = c6;
					}

					*(short *)(pk + 8) = x;
					*(short *)(pk + 10) = y;
					off = t0 * 8;
					*(short *)(pk + 16) = x + (*(short *)(EN(off) + 4) << s2);
					*(short *)(pk + 18) = y;
					*(short *)(pk + 24) = x;
					*(short *)(pk + 26) = *(unsigned short *)(EN(off) + 6) + y;
					*(short *)(pk + 32) = x + (*(short *)(EN(off) + 4) << s2);
					*(short *)(pk + 34) = *(unsigned short *)(EN(off) + 6) + y;
					pk[12] = (*(unsigned short *)EN(off) & 63) << s2;
					pk[13] = *(unsigned char *)(EN(off) + 2);

					{
						pk[20] = ((*(unsigned short *)EN(off) & 63) << s2) +
						         (*(short *)(EN(off) + 4) << s2);
						pk[21] = *(unsigned char *)(EN(off) + 2);
					}

					pk[28] = (*(unsigned short *)EN(off) & 63) << s2;

					{
						{
							int t2 = EN(off)[2];

							pk[29] = *(unsigned char *)(EN(off) + 6) + t2;
						}
					}

					{
						pk[36] = ((*(unsigned short *)EN(off) & 63) << s2) +
						         (*(short *)(EN(off) + 4) << s2);
					}

					{
						{
							int t2 = EN(off)[2];

							pk[37] = *(unsigned char *)(EN(off) + 6) + t2;
						}
					}

					if (c7)
						pk[7] |= 2;
					else
						pk[7] &= 253;

					if (c4 == -1)
						pk[7] |= 1;
					else
						pk[7] &= 254;

					{
						char *e = EN(off);

						*(short *)(pk + 22) =
						    getTPage(p->depth == 8 ? 1 : 2, 0, ((RECT *)e)->x, ((RECT *)e)->y);
					}

					*(short *)(pk + 14) = p->f28;

					if (c8 == 0) {
						((TG *)pk)->addr = ((TG *)ot)->addr;
						((TG *)ot)->addr = (unsigned)pk;
					} else
						FUN_8008c880(pk);

					if (ot != (unsigned *)(DAT_800d1a48 + 0x84))
						DAT_800d1d94--;

					t0++;
					j++;
					x += *(short *)(EN(off) + 4) << s2;
				} while (j < p->w);
			}

			k = i * p->w;
			i++;
			y += *(short *)(EN(k * 8) + 6);
		} while (i < p->h);
	}
}
