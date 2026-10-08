/* FUN_8004e1e0 (0x8004e1e0) */
extern int DAT_800d1ff4;
extern int DAT_800d1ff8;
extern int DAT_800d1ffc;
extern char *DAT_800d2178;

int DAT_800d1b6c;

void FUN_8004e1e0(void) {
	char *p = DAT_800d2178;

	DAT_800d1ff4 = 290;
	DAT_800d1ff8 = 150;
	DAT_800d1b6c = 0;
	DAT_800d1ffc = -108;
	*(short *)(p + 12) = 3413;
}
