/* _._16CLinked2EndedBit (0x80029408) */
extern char DAT_8009f7b8[];

char DAT_800d18d4[8];

int BASEF(char *p, int a);
void DeleteFrom__4CBitPv(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80029408(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f7b8;
	DeleteFrom__4CBitPv(p, DAT_800d18d4);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
