/* _._19CMotionBlurImmortal (0x80029b88) */
extern char DAT_8009f740[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80029b88(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f740;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
