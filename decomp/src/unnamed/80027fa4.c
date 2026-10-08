/* _._15CNonRenderedBit (0x80027fa4) */
extern char DAT_8009f878[];

char DAT_800d18cc[8];

int BASEF(char *p, int a);
void DeleteFrom__4CBitPv(char *p, char *q);
void __dl__4CBitPv(void *p);

void FUN_80027fa4(char *p, int f) {
	*(char **)(p + 68) = DAT_8009f878;
	DeleteFrom__4CBitPv(p, DAT_800d18cc);
	BASEF(p, 0);

	if (f & 1)
		__dl__4CBitPv(p);
}
