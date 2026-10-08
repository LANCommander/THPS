/* SFX_Grunt__FP6CBruce (0x80043408) */
struct E {
	char pad[12];
	int f;
	char q[324];
};

extern struct E DAT_800a44fc[];
extern int DAT_800d1984;
extern int DAT_800d1e28;

int Redbook_Rnd__Fi(int);
void SFX_PlayX__FUisi(int, int, int);

void SFX_Grunt__FP6CBruce(char *p) {
	int a;

	switch (DAT_800d1984) {
		case 7:
			a = 53;
			break;
		case 9:
			a = 40;

			if (DAT_800d1e28 == 8)
				a = 137;

			break;
		default:
			goto out;
	}

	SFX_PlayX__FUisi(a, 8192, 0);
out:
	a = DAT_800a44fc[*(int *)(p + 744)].f;

	if (a == 0x9000 || a == 0xb000)
		a = 31;
	else
		a = Redbook_Rnd__Fi(3) + 28;

	SFX_PlayX__FUisi(a, 8192, 0);
}
