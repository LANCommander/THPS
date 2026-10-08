/* FUN_80028394 (0x80028394) */
extern char DAT_8009f848[];

char DAT_800d18dc[8];

char *FUN_80027e44(char *p);
void AttachTo__4CBitPv(char *p, char *q);

char *FUN_80028394(char *p) {
	FUN_80027e44(p);

	*(char **)(p + 68) = DAT_8009f848;
	*(int *)(p + 144) = 0x2c808080;
	AttachTo__4CBitPv(p, DAT_800d18dc);
	return p;
}
