/* FUN_8001f274 (0x8001f274) */
extern char DAT_8009ef94[];
extern char DAT_8009efa4[];

void Mem_Delete__FPv(int a);
void FUN_80024238(void *p);

void FUN_8001f274(char **p, int f) {
	*p = DAT_8009ef94;

	if (((int *)p)[2])
		Mem_Delete__FPv(((int *)p)[1]);

	*p = DAT_8009efa4;

	if (f & 1)
		FUN_80024238(p);
}
