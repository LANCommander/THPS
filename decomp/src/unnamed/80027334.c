/* FUN_80027334 (0x80027334) */
extern char DAT_8009f658[];
extern int DAT_800d18f8;

void Mem_Delete__FPv(int a);
void DeleteFrom__4CBitPv(char *p, int *q);
int BASEF(char *p, int a);
void FUN_80027d70(void *p);

void FUN_80027334(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f658;
	Mem_Delete__FPv(*(int *)(p + 76));
	DeleteFrom__4CBitPv(p, &DAT_800d18f8);
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
