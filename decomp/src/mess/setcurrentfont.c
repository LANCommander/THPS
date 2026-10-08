/* Mess_SetCurrentFont__FPc (0x8001f144) */
typedef struct {
	char name[0x1a];
	unsigned short scale;
	char pad2[8];
} Font;

int Num_fonts;
int Current_font;

extern Font Font_table[];

extern int FUN_8008f6fc(char *, char *);

void Mess_SetCurrentFont(char *name) {
	int i;

	for (i = 0; i < Num_fonts; i++) {
		if (!FUN_8008f6fc(name, Font_table[i].name))
			break;
	}

	Current_font = i;
}
