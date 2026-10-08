/* FUN_80056428 (0x80056428) */
typedef struct N {
	int a;
	int b;
	struct N *next;
	int d;
	int e;
} N;

int DAT_800d2304[2];
int DAT_800d231c[2];

extern int DAT_800d3758[];
extern N *DAT_800d1a60;
extern N *DAT_800d1c80;

void FUN_80059618(int);
void FUN_800495f4(N *);
N *Mem_NewX__FUiii(int, int, int);
void FUN_8006edb8(int);
void ClearRegion__Fiii(int, int, int);

void FUN_80056428(void) {
	int i, n;
	N *t;

	FUN_80059618(0);

	n = 2;

	if (DAT_800d2304[0] == DAT_800d2304[1] && DAT_800d231c[0] && DAT_800d231c[1])
		n = 1;

	for (i = 0; i < n; i++) {
		if (DAT_800d231c[i]) {
			ClearRegion__Fiii(DAT_800d3758[DAT_800d2304[i]], 1, 1);
			FUN_8006edb8(DAT_800d3758[DAT_800d2304[i]]);
		}
	}

	if (DAT_800d1a60) {
		do {
			t = DAT_800d1a60->next;
			FUN_800495f4(DAT_800d1a60);

			DAT_800d1a60 = t;
		} while (t);
	}

	DAT_800d1a60 = Mem_NewX__FUiii(20, 1, 1);
	*DAT_800d1a60 = *DAT_800d1c80;
	DAT_800d1a60->next = 0;
}
