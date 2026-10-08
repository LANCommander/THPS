/* FUN_800343f0 (0x800343f0) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	short x, y, z, w;
} SV;

typedef struct {
	V s, e;
	char pad[0x68 - 24];
	int hit;
	char pad2[0x78 - 0x6c];
	SV n;
	char pad3[0xa8 - 0x80];
} L;

typedef struct {
	char p0[4];
	int x, y, z;
	char p1[0x6c - 0x10];
	V vel;
	char p2[0xf0 - 0x78];
	V old;
	char p3[0x146 - 0xfc];
	unsigned short st;
	char p4[0x150 - 0x148];
	int f150;
	char p5[0x358 - 0x154];
	int f358;
	char p6[0x368 - 0x35c];
	int f368;
	char p7[0x7d8 - 0x36c];
	V w1;
	int m0, m1, m2;
	V w2;

} B;

void FUN_8002fcdc(B *, int, int);
void FUN_80039f2c(B *, SV, int);
void FUN_80043408(B *);
int FUN_800720ec(V *, V *);
void FUN_800827d4(L *, int);
int GetFaceFlags__FP9SLineInfo(L *);
int Length__C7CVector(V *);
void M3dColij_InitLineInfo__FP9SLineInfo(L *);

#define MUL(t) (p->f358 ? (t) * 35 : (t) * 5)
#define ST(d, b, q, t)                                                                             \
	q = (t);                                                                                       \
	d = b + (p->f358 ? q * 35 : q * 5) * 2;

int FUN_800343f0(B *p, int a) {
	L li;
	V d;
	int pd;
	V c;
	int pc;
	int s1, q0, q1, q2, q3, q4, q5;

	li.s.x = p->x + p->w2.x * 30;
	li.s.y = p->y + p->w2.y * 30;
	li.s.z = p->z + p->w2.z * 30;
	ST(li.e.x, li.s.x, q0, a * p->m0)
	ST(li.e.y, li.s.y, q1, a * p->m1)
	ST(li.e.z, li.s.z, q2, a * p->m2)
	M3dColij_InitLineInfo__FP9SLineInfo(&li);
	FUN_800827d4(&li, 1);
	GetFaceFlags__FP9SLineInfo(&li);

	if (li.hit) {
		d.x = li.n.x;
		d.y = li.n.y;
		d.z = li.n.z;

		if ((unsigned)(FUN_800720ec(&d, &p->w2) + 1023) < 2047) {
			s1 = 0;
			*(V *)&p->x = p->old;
			c = p->vel;

			if (p->st != 12) {
				if (Length__C7CVector(&c) >= 7) {
					if (!p->f358 && !p->f368) {
						{
							V e;
							int pe;

							e.x = li.n.x;
							e.y = li.n.y;
							e.z = li.n.z;

							if (FUN_800720ec(&e, &p->w1) >= 2897) {
								p->f150 = 0x10000;
								FUN_8002fcdc(p, 12, 3787);

								s1 = 200;
								FUN_80043408(p);
							}
						}
					}
				}
			}

			{
				SV t;

				t = li.n;
				FUN_80039f2c(p, t, s1);
			}

			li.s.x = p->x;
			li.s.y = p->y;
			li.s.z = p->z;
			ST(li.e.x, li.s.x, q3, li.n.x)
			ST(li.e.y, li.s.y, q4, li.n.y)
			ST(li.e.z, li.s.z, q5, li.n.z)
			M3dColij_InitLineInfo__FP9SLineInfo(&li);
			FUN_800827d4(&li, 1);
			GetFaceFlags__FP9SLineInfo(&li);

			if (li.hit)
				return 0;

			p->x = li.e.x;
			p->y = li.e.y;
			p->z = li.e.z;
			return 1;
		}
	}

	return 0;
}
