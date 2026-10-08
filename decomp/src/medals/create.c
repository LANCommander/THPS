/* Medal_Create__F10EMedalTypeiiiii (0x80073dc8) */
typedef struct {
	short vx, vy, vz, pad;
} SVECTOR;

typedef struct {
	int vx, vy, vz, pad;
} VECTOR;

#define CTC2(n, v) __asm__ volatile("ctc2 %0, $" #n : : "r"(v))
#define MTC2(n, v) __asm__ volatile("mtc2 %0, $" #n : : "r"(v))
#define STLVNL(p)                                                                                  \
	__asm__ volatile("swc2 $25, 0(%0); swc2 $26, 4(%0); swc2 $27, 8(%0)" : : "r"(p) : "memory")

typedef struct {
	unsigned short flags;
	short s2, s4;
	char _6[0x1e];
	short s36, s38, s40;
	char _2a[300];
	short s342, s344, s346;
} Medal;

extern char *DAT_800d217c;
extern char DAT_800a824c[];

Medal *FUN_800434d4(int);
Medal *__8CPowerUpUsRC7CVectorT2Uii(Medal *, int, int *, char *, int, int);

Medal *Medal_Create__F10EMedalTypeiiiii(int type, int x, int y, int z, int a, int b) {
	SVECTOR v;
	VECTOR o;
	int pos[3];
	Medal *p;
	short sa;
	short *q;

	v.vx = x;
	v.vy = y;
	v.vz = z;
	CTC2(0, *(int *)(DAT_800d217c + 0x34));
	CTC2(1, *(int *)(DAT_800d217c + 0x38));
	CTC2(2, *(int *)(DAT_800d217c + 0x3c));
	CTC2(3, *(int *)(DAT_800d217c + 0x40));
	CTC2(4, *(int *)(DAT_800d217c + 0x44));
	MTC2(0, *(int *)&v.vx);
	MTC2(1, *(int *)&v.vz);
	__asm__ volatile("nop; nop; cop2 0x406012");

	STLVNL(&o);

	pos[0] = o.vx + (*(int *)(DAT_800d217c + 4) << 12);
	pos[1] = o.vy + (*(int *)(DAT_800d217c + 8) << 12);
	pos[2] = o.vz + (*(int *)(DAT_800d217c + 12) << 12);

	switch (type) {
		case 5:
			p = FUN_800434d4(356);

			if (p)
				p = __8CPowerUpUsRC7CVectorT2Uii(p, 1636, pos, DAT_800a824c, 0, 0xffff);

			break;
		case 6:
			p = FUN_800434d4(356);

			if (p)
				p = __8CPowerUpUsRC7CVectorT2Uii(p, 1637, pos, DAT_800a824c, 0, 0xffff);

			break;
		case 7:
			p = FUN_800434d4(356);

			if (p)
				p = __8CPowerUpUsRC7CVectorT2Uii(p, 1638, pos, DAT_800a824c, 0, 0xffff);

			break;
	}

	q = &p->s36;
	p->s346 = 80;
	sa = a;
	p->flags |= 0x200;
	p->s36 = sa;
	q[1] = sa;
	q[2] = sa;
	p->s344 = b;
	p->s342 = b;
	return p;
}
