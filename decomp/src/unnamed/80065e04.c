/* FUN_80065e04 (0x80065e04) */
extern int DAT_800d1b10;

void Mem_Delete__FPv(int);
void ProcessNewPSX__Fi(int);
void Spool_ClearPSX__FPc(char *);
void Spool_Sync__Fv(void);
void unloadPRE__10PREManagerPc(int, char *);

void FUN_80065e04(char *a, int b) {
	int o = b * 36;
	int *p30 = (int *)(a + 0x30);
	int *s, *q;
	char *t, *t1, *t2, *t3;

	if (*(int *)((char *)p30 + o)) {
		t1 = a + 0x28;
		s = (int *)(t1 + o);

		if (*s == 0) {
			q = (int *)(a + 0x10);
			q = (int *)((char *)q + o);
			Mem_Delete__FPv(*q);

			*q = 0;
		}

		if (*s == 2) {
			unloadPRE__10PREManagerPc(DAT_800d1b10, (char *)(o + (int)a + 20));
		} else if (*s == 1) {
			q = (int *)(a + 0x24);
			q = (int *)((char *)q + o);
			ProcessNewPSX__Fi(*q);
			Spool_ClearPSX__FPc((char *)(o + (int)a) + 20);
			Spool_Sync__Fv();

			*q = -1;
		}

		t = (char *)(b * 36);
		*(int *)((int)p30 + (int)t) = 0;
	}
}
