/* _._11CMotionBlur (0x80029ad8) */
extern char DAT_8009f758[];

int BASEF(char *p, int a);
void __dl__4CBitPv(void *p);

void FUN_80029ad8(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f758;
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
