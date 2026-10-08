/* Panel_PlayerInit__FUsP6CBruce (0x8006e144) */
extern char *DAT_800d19a4;

void Panel_PlayerInit(unsigned short n, char *b) {
	if (b == DAT_800d19a4)
		*(short *)(b + 0x92c) = 0;
	else
		*(short *)(b + 0x92c) = 1;
}
