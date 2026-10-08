/* FUN_8007d6b8 (0x8007d6b8) */
extern int DAT_800c1188[];
extern int DAT_800c1174[];
extern int DAT_800c1160[];
extern char DAT_800a35c4[];

void FUN_8007d6b8(void) {
	volatile int pad[4];

	DAT_800c1188[0] = (int)DAT_800a35c4;
	DAT_800c1174[0] = (int)DAT_800a35c4;
	DAT_800c1160[0] = (int)DAT_800a35c4;
}
