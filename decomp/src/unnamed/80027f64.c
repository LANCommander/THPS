/* __15CNonRenderedBit (0x80027f64) */
extern char DAT_8009f878[];

char DAT_800d18cc[8];

char *__4CBit(char *p);
void AttachTo__4CBitPv(char *p, char *q);

char *__15CNonRenderedBit(char *p) {
	__4CBit(p);

	*(char **)(p + 68) = DAT_8009f878;
	AttachTo__4CBitPv(p, DAT_800d18cc);
	return p;
}
