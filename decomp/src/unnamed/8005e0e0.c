/* FUN_8005e0e0 (0x8005e0e0) */
struct VT {
	char pad[8];
	short off;
	short p;
	void (*fn)(char *, int);
	short off2;
	short p2;
	void (*fn2)(char *);
};

typedef struct O {
	struct VT *vt;
} O;

extern char DAT_800c0a48[];
extern int DAT_800d1cb0;
extern int DAT_800d1cb8;

int DAT_800d2358, DAT_800d235c, DAT_800d1d28;

extern char DAT_800a1c04[];

extern int FUN_8005eb78();
void FUN_800242cc(void);
void FUN_8004b250(int, int, int);
void FUN_8005c68c(void);
void FUN_8005c780(void);
void FUN_8005c934(void);
int FUN_8005e09c(int);
void FUN_80061ea0(void);
O *FUN_80063e34(O *, int);
void FUN_80063f58(O *);
int FUN_80064274(O *);
O *FUN_800642e8(O *, int, int, int, int *, int, int, int, int);
void FUN_80064890(O *, int, int);
void FUN_800648c0(O *, int, int);
int FUN_8006516c(O *);
void FUN_8006b240(void);
void FUN_8006b26c(void);
void FUN_80070ff4(void);
int FUN_8008f6fc(int, char *);
void Pad_ClearTriggers__FP8SControl(char *);
O *__nw__5CItemUi(int);
void down__12VerticalMenu(O *);
void erase__12VerticalMenu(O *);
void up__12VerticalMenu(O *);

int FUN_8005e0e0(int *a0, int *a1, int a2, int a3, int a4, void (*a5)(O *), int a6, int a7,
                 int a8) {
	O *s2;
	O *s1;
	int s3, s0, i, r, t;
	char *P;

	Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
	Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);

	s3 = FUN_8005e09c(a4);

	if (s3)
		return s3 + a3;

	s2 = __nw__5CItemUi(820);

	if (s2)
		s2 = FUN_800642e8(s2, 100, 398, 15, a0, a2, a6, a7, a8);

	FUN_80064890(s2, DAT_800d2358, DAT_800d235c);

	for (i = 0; i < a2; i++) {
		if (a1[i])
			FUN_800648c0(s2, i, 1);
	}

	s0 = -1;

	if (a5 && (int)a5 == (int)FUN_8005eb78)
		s0 = DAT_800d1d28;

	s1 = __nw__5CItemUi(284);

	if (s1)
		s1 = FUN_80063e34(s1, s0);

	DAT_800d1cb0 = 1600;

	while (s3 == 0) {
		FUN_8005c780();

		if (FUN_8008f6fc(*a0, DAT_800a1c04) == 0) {
			if (DAT_800d1cb0)
				DAT_800d1cb0--;
			else
				s3 = 128;
		}

		FUN_8005c934();
		FUN_80070ff4();
		FUN_8005c68c();

		if (DAT_800d1cb8) {
			s3 = 0x666;
			break;
		}

		FUN_800242cc();
		FUN_8006b240();
		FUN_80061ea0();

		r = FUN_80064274(s1);

		if (r == 3) {
			FUN_8004b250(144, 8192, 0);
			up__12VerticalMenu(s2);
		}

		if (r == 4) {
			FUN_8004b250(144, 8192, 0);
			down__12VerticalMenu(s2);
		}

		if (r)
			DAT_800d1cb0 = 1600;

		FUN_80063f58(s1);

		if (a5)
			a5(s2);

		s2->vt->fn2((char *)s2 + s2->vt->off2);
		FUN_8006b26c();

		if (DAT_800c0a48[225] || DAT_800c0a48[589] || DAT_800c0a48[49] || DAT_800c0a48[413]) {
			Pad_ClearTriggers__FP8SControl(DAT_800c0a48);
			Pad_ClearTriggers__FP8SControl(DAT_800c0a48 + 364);
			FUN_8004b250(145, 8192, 0);

			t = FUN_8006516c(s2) + 1;
			s3 = a3 + t;
		}

		P = DAT_800c0a48;

		if (P[1] || P[365]) {
			Pad_ClearTriggers__FP8SControl(P);
			Pad_ClearTriggers__FP8SControl(P + 364);
			FUN_8004b250(147, 8192, 0);

			s3 = -1;
		}
	}

	i = 0;

	do {
		i++;
		FUN_8006b240();
		FUN_80061ea0();
		erase__12VerticalMenu(s2);
		FUN_8006b26c();
	} while (i < 2);

	if (s2)
		s2->vt->fn((char *)s2 + s2->vt->off, 3);

	if (s1)
		s1->vt->fn((char *)s1 + s1->vt->off, 3);

	return s3;
}
