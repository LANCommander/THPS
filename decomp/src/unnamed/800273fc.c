/* FUN_800273fc (0x800273fc) */
extern char DAT_8009f640[];

int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_800273fc(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f640;
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
