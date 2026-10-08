/* FUN_800277b8 (0x800277b8) */
extern char DAT_8009f610[];

int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_800277b8(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f610;
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
