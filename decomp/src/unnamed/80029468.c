/* FUN_80029468 (0x80029468) */
extern char DAT_8009f7a0[];

char DAT_800d18d8[8];

char *FUN_80027e44(char *p);
void AttachTo__4CBitPv(char *p, char *q);

char *FUN_80029468(char *p) {
	FUN_80027e44(p);

	*(char **)(p + 68) = DAT_8009f7a0;
	AttachTo__4CBitPv(p, DAT_800d18d8);
	return p;
}
