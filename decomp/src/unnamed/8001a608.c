/* Front_SwitchOnVideoScreen__Fv (0x8001a608) */
struct T {
	char pad[12];
	int f;
	char q[104];
};

extern int DAT_800a42f4[];
extern struct T DAT_800a5398[];
extern int DAT_800d1e28;
extern int DAT_800d16a4;

int DAT_800d13e8;

int Competition_IsOver__Fv(void);
void FUN_8001a128(void);

void Front_SwitchOnVideoScreen__Fv(void) {
	int v;

	if (DAT_800a42f4[0] == 0 && DAT_800a5398[DAT_800d1e28].f != 0 && DAT_800d16a4 == 1 &&
	    Competition_IsOver__Fv() == 0)
		v = 25;
	else {
		v = 16;

		if (DAT_800a42f4[0] == 0)
			v = 15;
	}

	DAT_800d13e8 = v;
	FUN_8001a128();
}
