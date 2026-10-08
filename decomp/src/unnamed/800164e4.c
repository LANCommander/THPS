/* FUN_800164e4 (0x800164e4) */
struct T {
	char pad[12];
	int f;
	char q[104];
};

extern struct T DAT_800a5398[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;

int FUN_800164e4(void) {
	if (DAT_800a5398[DAT_800d1e28].f != 0 && DAT_800d16a4 == 1)
		return 1;

	return 0;
}
