/* FUN_8002ee00 (0x8002ee00) */
extern char DAT_8009f7e8[];

int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_8002ee00(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f7e8;
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
