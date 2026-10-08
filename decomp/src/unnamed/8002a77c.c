/* FUN_8002a77c (0x8002a77c) */
extern char DAT_8009f688[];

char DAT_800d18ec[8];

int BASEF(char *p, int a);
void DeleteFrom__4CBitPv(char *p, char *q);
void FUN_80027d70(void *p);

void FUN_8002a77c(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f688;
	DeleteFrom__4CBitPv(p, DAT_800d18ec);
	BASEF(p, 0);

	if (f & 1)
		FUN_80027d70(p);
}
