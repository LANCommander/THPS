/* FUN_80029b88 (0x80029b88) */
extern char DAT_8009f740[];

int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_80029b88(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f740;
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
