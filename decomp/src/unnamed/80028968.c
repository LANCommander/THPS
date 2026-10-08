/* FUN_80028968 (0x80028968) */
extern char DAT_8009f818[];

char DAT_800d18e4[8];

int BASEF(char *p, int a);
void DeleteFrom__4CBitPv(char *p, char *q);
void FUN_80027d70(void *p);

void FUN_80028968(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f818;
	DeleteFrom__4CBitPv(p, DAT_800d18e4);
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
