/* FUN_80028054 (0x80028054) */
extern char DAT_8009f860[];

int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_80028054(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f860;
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
