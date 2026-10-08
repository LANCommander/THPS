/* __8CQuadBit (0x80028394) */
extern char DAT_8009f848[];

char DAT_800d18dc[8];

char *__4CBit(char *p);
void AttachTo__4CBitPv(char *p, char *q);

char *__8CQuadBit(char *p) {
	__4CBit(p);

	*(char **)(p + 68) = DAT_8009f848;
	*(int *)(p + 144) = 0x2c808080;
	AttachTo__4CBitPv(p, DAT_800d18dc);
	return p;
}
