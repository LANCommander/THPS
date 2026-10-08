/* FUN_80022b4c (0x80022b4c) */
struct E {
	int f0;
	int p[5];
	int f24;
	int q[1];
};

extern struct E movieDetails[];
extern unsigned char DAT_800a6728[];

int FUN_8009085c(char *a, int b);
int FUN_800913c0(char *a);

void FUN_80022b4c(void) {
	char buf[24];
	int i;

	for (i = 0; i < 26; i++) {
		if (movieDetails[DAT_800a6728[i]].f24) {
			if (FUN_8009085c(buf, movieDetails[DAT_800a6728[i]].f0))
				movieDetails[DAT_800a6728[i]].f24 = FUN_800913c0(buf);
			else
				movieDetails[DAT_800a6728[i]].f24 = 0;
		}
	}
}
