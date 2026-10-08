/* FUN_8005c8bc (0x8005c8bc) */
struct S {
	char pad[524];
	int x;
	int Get() {
		return x;
	}
};

extern "C" {
	int DAT_800d1cac;

	extern S DAT_800be478;

	void FUN_8005c8bc(void);
}

void FUN_8005c8bc(void) {
	if (DAT_800d1cac == 3)
		((volatile S &)DAT_800be478).x;
}
