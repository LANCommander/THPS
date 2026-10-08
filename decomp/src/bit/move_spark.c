/* Move__6CSpark (0x80029810) */
typedef struct {
	char _0[8];
	unsigned short life;
	unsigned short maxlife;
	char _c[0xc];
	int px, py, pz;
	int vx, vy, vz;
	int ax, ay, az;
	char _3c[0x4c - 0x3c];
	unsigned char c0, c1, c2;
	char _4f[5];
	unsigned char d0, d1, d2;
	char _57[1];
	int lim;
} Spark;

void FUN_80027e18(Spark *);

void Move__6CSpark(Spark *t) {
	int x = t->px + t->vx;
	int y = t->py + t->vy;
	int z = t->pz + t->vz;
	int lim = t->lim;

	if (lim && lim < y) {
		t->py = lim;
	} else {
		t->py = y;
		t->pz = z;
		t->px = x;
		x = t->vx + t->ax;
		y = t->vy + t->ay;
		z = t->vz + t->az;
		x -= x >> 3;
		t->vx = x;
		y -= y >> 3;
		z -= z >> 3;
		t->vy = y;
		t->vz = z;
	}

	t->life++;

	if ((short)t->life >= t->maxlife)
		FUN_80027e18(t);

	t->c0 -= t->d0;
	t->c1 -= t->d1;
	t->c2 -= t->d2;
}
