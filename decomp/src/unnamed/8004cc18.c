/* FileIO_Continue__Fv (0x8004cc18) */
typedef struct {
	short x, y, w, h;
} R;

int DAT_800d1b14, DAT_800d1afc, DAT_800d1b34, DAT_800d1af8, DAT_800d224c, DAT_800d1b04,
    DAT_800d1b0c, DAT_800d2264, DAT_800d2260;
char DAT_800d225c[8];

extern R DAT_800d1b20[];

int FUN_8008f264(int, char *, int);
int FUN_800958c0(int, int, int);
int FUN_80095a5c(int, char *);
void FUN_80070ff4(void);
int FUN_8008c5ec(R *, int, int, int);
void FUN_8005dcc4(void);

void FileIO_Continue__Fv(void) {
	char buf[104];
	R r;
	int s0, v;

	if (DAT_800d1b14 != 0) {
		DAT_800d1afc = 0;
		return;
	}

	DAT_800d1b34 = DAT_800d1afc;
	s0 = 0;

	switch (DAT_800d1afc) {
		case 0:
			break;
		case 1:
			DAT_800d1af8 = 0;

			if (FUN_8008f264(2, DAT_800d225c, 0) == 0) {
				s0 = 1;
				break;
			}

			DAT_800d1afc = 2;
		case 2:
			if (FUN_800958c0(DAT_800d2264, DAT_800d2260, 384) == 0) {
				s0 = 1;
				DAT_800d1afc = s0;
				break;
			}

			DAT_800d1afc = 3;
		case 3:
			if (DAT_800d1af8 == DAT_800d224c) {
				DAT_800d1afc = 0;
				DAT_800d1b04 = 0;
				break;
			}

			FUN_80070ff4();

			v = FUN_80095a5c(1, buf);

			if (v > 0) {
				DAT_800d1b0c = 0;
			} else if (v < 0) {
				DAT_800d1b0c = DAT_800d1b0c + 1;

				if (DAT_800d1b0c >= 5) {
					DAT_800d1b0c = 0;
					DAT_800d1afc = 1;
				}

				s0 = 1;
			} else {
				DAT_800d1af8 = DAT_800d224c;
			}

			break;
	}

	if (s0 != 0) {
		r = DAT_800d1b20[0];
		FUN_8008c5ec(&r, 255, 0, 0);

		r.y += 256;
		FUN_8008c5ec(&r, 255, 0, 0);
	}

	FUN_8005dcc4();
}
