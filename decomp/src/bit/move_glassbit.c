/* Move__9CGlassBit (0x8002a7dc) */
typedef struct {
	int x, y, z;
} V;

typedef struct {
	char _0[8];
	short s8;
	unsigned short s10;
	char _c[0x18];
	V vel;
	char _30[0x18];
	V p[3];
	int floor;
	unsigned char b70, b71, b72, b73, b74, b75, b76;
} G;

int Redbook_Rnd__Fi(int);
void Die__4CBit(G *);

void Move__9CGlassBit(G *t) {
	int vx = t->vel.x;
	int vy = t->vel.y;
	int vz = t->vel.z;
	int r;

	t->p[0].x += vx;
	t->p[0].z += vz;
	t->p[0].y += vy;
	t->p[1].x += vx;
	t->p[1].y += vy;
	t->p[1].z += vz;
	t->p[2].x += vx;
	t->p[2].y += vy;
	vy += 10000;
	t->p[2].z += vz;

	if (t->floor < t->p[0].y) {
		unsigned _t8947 = t->s8 < 2;

		if (_t8947) {
			r = Redbook_Rnd__Fi(50);
			t->p[0].y = t->floor - (r << 12);
			t->p[1].y = t->floor - (Redbook_Rnd__Fi(50) << 12);
			vy = -vy;
			vy >>= 2;
			t->p[2].y = t->floor - (Redbook_Rnd__Fi(50) << 12);
			t->s8++;
		} else {
			vy = 0;
		}

		vx >>= 1;
		vz >>= 1;
	}

	t->vel.x = vx;
	t->vel.y = vy;
	t->vel.z = vz;

	if (t->s8 < 2 && Redbook_Rnd__Fi(5) == 0) {
		t->b73 = 48;
		t->b74 = 48;
		t->b75 = 64;
	} else {
		t->b73 = t->b70;
		t->b74 = t->b71;
		t->b75 = t->b72;
	}

	if (t->s10 == 0 || --t->s10 == 0) {
		t->b70 = t->b70 > t->b76 ? t->b70 - t->b76 : 0;
		t->b71 = t->b71 > t->b76 ? t->b71 - t->b76 : 0;
		t->b72 = t->b72 > t->b76 ? t->b72 - t->b76 : 0;
	}

	if ((t->b70 | t->b71 | t->b72) == 0)
		Die__4CBit(t);
}
