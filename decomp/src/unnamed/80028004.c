/* FUN_80028004 (0x80028004) */
extern char DAT_8009f860[];

char *FUN_80027e44(char *p);

char *FUN_80028004(char *p) {
	FUN_80027e44(p);

	*(char **)(p + 68) = DAT_8009f860;
	*(short *)(p + 92) = 128;
	*(short *)(p + 94) = 400;
	*(int *)(p + 76) = 0x2c808080;
	return p;
}
