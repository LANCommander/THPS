/* Mess_SetFontScale__FUi (0x8001f1d8) */
typedef struct {
	char pad[0x1a];
	unsigned short scale;
	char pad2[8];
} Font;

unsigned char DAT_800d1602;
int DAT_800d15e4;

extern Font DAT_800a6110[];

extern void Mess_SetScale__Fi(int);

void Mess_SetFontScale(unsigned s) {
	if (!DAT_800d1602)
		Mess_SetScale__Fi(s);
	else
		(DAT_800d15e4 + DAT_800a6110)->scale = s;
}
