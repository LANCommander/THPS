/* FUN_80029c38 (0x80029c38) */
extern char DAT_8009f728[];

int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_80029c38(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f728;
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
