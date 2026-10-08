/* FUN_8003b2f0 (0x8003b2f0) */
typedef struct {
	int x, y, z;
} V;

typedef struct B {
	char p0[4];
	V pos;
	char p1[0x6c - 0x10];
	V vel;
	char p2[0xf0 - 0x78];
	V old;
	char p3[0x1d4 - 0xfc];
	struct B *other;
	char p4[0x358 - 0x1d8];
	int f358;
} B;

int FUN_800720ec(V *, V *);
int Length__C7CVector(V *);
void Normalize__7CVector(V *);
V __mi__FRC7CVectorT0(const V *, const V *);
void FUN_8002fe9c(B *, int);

void FUN_8003b2f0(B *p) {
	V d;
	int pd;
	V c;
	int pc;
	int s0, s1, v;
	V *s3;
	B *a;

	if (p->f358 == 0) {
		if (p->other->f358 == 0) {
			d = __mi__FRC7CVectorT0(&p->other->pos, &p->pos);

			if (Length__C7CVector(&d) < 60) {
				c = __mi__FRC7CVectorT0(&p->other->pos, &p->old);
				d = c;
				Normalize__7CVector(&d);

				s3 = &p->vel;
				s1 = FUN_800720ec(s3, &d);
				v = FUN_800720ec(&p->other->vel, &d);

				if (s1 > 0) {
					if (v > 0) {
						FUN_8002fe9c(p->other, 0);
					} else {
						s0 = Length__C7CVector(&p->other->vel);

						if (Length__C7CVector(s3) >= s0)
							FUN_8002fe9c(p->other, 0);
						else
							FUN_8002fe9c(p, 0);
					}
				} else if (v <= 0)
					FUN_8002fe9c(p, 0);
			}
		}
	}
}
