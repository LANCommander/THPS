/* FUN_80070830 (0x80070830) */
struct T {
	char pad[13];
	char f;
	char q[3];
};

extern int DAT_800d1afc;

int DAT_800d1ef4;

extern struct T DAT_800bf654[];

int FUN_80070830(void) {
	int r = 0;

	if (DAT_800d1afc || DAT_800bf654[DAT_800d1ef4].f)
		r = 1;

	return r;
}
