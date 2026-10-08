/* FUN_800294a8 (0x800294a8) */
extern char DAT_8009f7a0[];

char DAT_800d18d8[8];

int BASEF(char *p, int a);
void DeleteFrom__4CBitPv(char *p, char *q);
void FUN_80027d70(void *p);

void FUN_800294a8(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f7a0;
	DeleteFrom__4CBitPv(p, DAT_800d18d8);
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
