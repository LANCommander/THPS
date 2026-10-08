/* _._8CFlatBit (0x80029368) */
extern char DAT_8009f7d0[];

char DAT_800d18d0[8];

int BASEF(char *p, int a);
void DeleteFrom__4CBitPv(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80029368(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f7d0;
	DeleteFrom__4CBitPv(p, DAT_800d18d0);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
