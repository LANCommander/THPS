/* __16CLinked2EndedBit (0x800293c8) */
extern char DAT_8009f7b8[];

char DAT_800d18d4[8];

char *__7CFT4Bit(char *p);
void AttachTo__4CBitPv(char *p, char *q);

char *__16CLinked2EndedBit(char *p) {
	__7CFT4Bit(p);

	*(char **)(p + 68) = DAT_8009f7b8;
	AttachTo__4CBitPv(p, DAT_800d18d4);
	return p;
}
