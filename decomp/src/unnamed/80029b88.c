/* _._19CMotionBlurImmortal (0x80029b88) */
extern char __vt_19CMotionBlurImmortal[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80029b88(char *p, int f) {
	*(char **)(p + 68) = __vt_19CMotionBlurImmortal;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
