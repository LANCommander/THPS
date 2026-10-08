/* FUN_800601fc (0x800601fc) */
extern int DAT_800a5e28[];
extern int DAT_800a5e30[];

int FUN_80060ba0(void);
void FUN_8005e4ec(int *p, int a, int b);

int FUN_800601fc(void) {
	int r = FUN_80060ba0();
	int v;

	if (r != -1) {
		if (r == 19) {
			v = DAT_800a5e28[0];
			FUN_8005e4ec(&v, 1, 60);

			r = 0;
		} else if (r == 0) {
			v = DAT_800a5e30[0];
			FUN_8005e4ec(&v, 1, -1);

			r = -1;
		}
	}

	return r;
}
