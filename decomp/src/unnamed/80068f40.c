/* FUN_80068f40 (0x80068f40) */
extern int DAT_800bf318[];

int DAT_800d1e04;
int DAT_800d1e08;

void FUN_80068f40(int a, int b) {
	if (DAT_800bf318[0] == 1) {
		switch (a) {
			case 1:
				DAT_800d1e04 = b;
				break;
			case 2:
				DAT_800d1e08 = b;
				break;
		}
	}
}
