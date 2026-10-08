/* FUN_8005c97c (0x8005c97c) */
int DAT_800d1cac;
int DAT_800d1ca8;

extern int DAT_800d1dc0;
extern char DAT_800bec34[];

void FUN_8005c8dc(int a);
void FUN_8006af64(void);
void FUN_8008c5ec(short *r, int a, int b, int c);
void FUN_80065d14(char *p);

void FUN_8005c97c(int a) {
	short r[4];

	if (DAT_800d1cac != a)
		FUN_8005c8dc(a);

	if (DAT_800d1ca8 != 2) {
		if (DAT_800d1dc0) {
			FUN_8006af64();
		} else {
			r[0] = 0;
			r[1] = 0;
			r[2] = 512;
			r[3] = 240;
			FUN_8008c5ec(r, 0, 0, 0);
		}
	}

	FUN_80065d14(DAT_800bec34);

	DAT_800d1ca8 = 2;
}
