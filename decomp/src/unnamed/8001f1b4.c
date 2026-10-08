/* FUN_8001f1b4 (0x8001f1b4) */
extern char Font_table[];

int Current_font;

void FUN_8001f1b4(char v) {
	Font_table[Current_font * 36 + 24] = v;
}
