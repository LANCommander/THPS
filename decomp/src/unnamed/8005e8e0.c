/* FUN_8005e8e0 (0x8005e8e0) */
typedef struct {
	int a, b, c;
} V;

extern V DAT_800a1c84;

typedef struct {
	char p[0xd4];
	int f;
} Q;

extern Q DAT_800a5d5c;
extern int DAT_800d10f4;

int DAT_800d1d80;

int FUN_8005e0e0(V *, int *, int, int, int *, int, int, int, int);
void FUN_8005e4ec(int *, int, int);
int FUN_80060ba0(int);

int FUN_8005e8e0(int a) {
	V l;
	int k[3];
	int s;
	int v, r;

	for (;;) {
		l = DAT_800a1c84;
		k[1] = 0;
		k[2] = 0;
		k[0] = DAT_800d1d80 ^ 1;
		v = FUN_8005e0e0(&l, k, 3, 16, &a, 0, 0, 0, 0);

		if (v == -1)
			goto ret;

		switch (v) {
			case 18:
				break;
			case 19:
				v = FUN_80060ba0(0);

				if (v == 0) {
					v = DAT_800a5d5c.f;
					s = v;
					FUN_8005e4ec(&s, 1, -1);

					v = -1;
				}

				break;
			case 17:
				DAT_800d10f4 = 1;
				break;
		}

		if (v == -1) {
			a = 0;
			continue;
		}
	ret:
		r = v;
		break;
	}

	return r;
}
