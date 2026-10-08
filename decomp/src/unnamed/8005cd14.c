/* FUN_8005cd14 (0x8005cd14) */
typedef struct {
	char p[0xc];
	int fc;
	char q[0x30 - 0x10];
	int f30, f34;
	char r[0x78 - 0x38];
} E;

extern E DAT_800a5398[];
extern char DAT_800a1b0c[], DAT_800a1b1c[], DAT_800a1b2c[], DAT_800a1b3c[], DAT_800a1b4c[],
    DAT_800c0a48[];

int DAT_800d1cf4, DAT_800d1cf8, DAT_800d1d04, DAT_800d1d0c, DAT_800d1cec, DAT_800d1d14;

void FUN_8005c8dc(int);
void FUN_8005c97c(int);
void FUN_8005ca64(void);
int FUN_8005ca3c(char *);
void FUN_80061a10(int);
void FUN_8005dc58(int);
int FileIO_Open__FPCc(int);
int Mem_NewX__FUiii(int, int, int);
void FUN_8004cb10(int);
void FUN_8004cdd0(void);
int __nw__5CItemUi(int);
int FUN_80063a5c(int, int, int, int, int, int, int);
void Pack_DefragmentFully__Fv(void);
void FUN_8006b240(void);
void FUN_80061ea0(void);

void FUN_8005cd14(void) {
	int o, s0, s1, o2;

	if (DAT_800d1cf8 == 3) {
		FUN_8005c8dc(7);
		FUN_8005c97c(7);
		FUN_8005ca64();
		FUN_80061a10(FUN_8005ca3c(DAT_800a1b0c));
		FUN_8005dc58(8);
	} else if (DAT_800d1cf8 == 1) {
		FUN_8005c8dc(5);
		FUN_8005c97c(5);
		FUN_8005ca64();
		FUN_80061a10(FUN_8005ca3c(DAT_800a1b1c));
		FUN_8005dc58(8);
	} else if (DAT_800d1cf8 == 5) {
		FUN_8005c8dc(14);
		FUN_8005c97c(14);
		FUN_8005ca64();
		FUN_80061a10(FUN_8005ca3c(DAT_800a1b2c));
		FUN_8005dc58(8);
	}

	if (DAT_800d1cf8 == 3 || DAT_800d1cf8 == 1 || DAT_800d1cf8 == 5) {
		o = __nw__5CItemUi(24);

		if (o)
			o = FUN_80063a5c(o, 8, FUN_8005ca3c(DAT_800a1b3c), 0, 458, 64, 128);

		DAT_800d1d0c = o;
	} else if (DAT_800a5398[DAT_800d1cf4].fc != 0) {
		FUN_8005c8dc(6);
		FUN_8005c97c(6);
		FUN_8005ca64();

		s0 = Mem_NewX__FUiii(FileIO_Open__FPCc(DAT_800a5398[DAT_800d1cf4].f34), 1, 1);

		if (s0) {
			FUN_8004cb10(s0);
			FUN_8004cdd0();
		}

		o2 = __nw__5CItemUi(24);

		if (o2)
			o2 = FUN_80063a5c(o2, 8, s0, 0, 458, 64, 128);

		DAT_800d1d0c = o2;
		s0 = Mem_NewX__FUiii(FileIO_Open__FPCc(DAT_800a5398[DAT_800d1cf4].f30), 1, 1);

		if (s0) {
			FUN_8004cb10(s0);
			FUN_8004cdd0();
		}

		FUN_80061a10(s0);
		FUN_8005dc58(5);

		DAT_800d1cf8 = 4;
	}

	s0 = __nw__5CItemUi(24);

	if (s0)
		s0 = FUN_80063a5c(s0, 8, FUN_8005ca3c(DAT_800a1b4c), 0, 440, 64, 128);

	DAT_800d1d04 = s0;
	DAT_800c0a48[0xe1] = 0;
	DAT_800c0a48[0x24d] = 0;
	DAT_800d1cec = 0;
	DAT_800d1d14 = 0;
	Pack_DefragmentFully__Fv();
	FUN_8006b240();
	FUN_80061ea0();
}
