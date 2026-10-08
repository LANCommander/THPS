/* FUN_8002e290 (0x8002e290) */
extern char DAT_8009f6e8[];

void Mem_Delete__FPv(int a);
int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_8002e290(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f6e8;
	Mem_Delete__FPv(*(int *)(p + 104));
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
