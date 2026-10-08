/* Competition_MarqueeDisplay__Fv (0x800764d8) */
typedef struct {
	char pad[0xd4];
	char *text;
	char pad2[0x124 - 0xd8];
	unsigned x;
} SComp;

extern SComp DAT_800c0fdc;

void Mess_SetRGB__FUcUcUci(unsigned char, unsigned char, unsigned char, int);
void Mess_SetScale__Fi(int);
void FUN_8001d250(int);
int FUN_8001e114(int, int, const char *, int, int, int, int);

void Competition_MarqueeDisplay(void) {
	if (DAT_800c0fdc.text) {
		Mess_SetRGB__FUcUcUci(122, 122, 122, 0);
		Mess_SetScale__Fi(256);
		FUN_8001d250(1);

		if (DAT_800c0fdc.x > 768)
			DAT_800c0fdc.x = 0;

		FUN_8001e114(512 - DAT_800c0fdc.x, 200, DAT_800c0fdc.text, 0, 0, 256, 0);

		DAT_800c0fdc.x += 5;
	}
}
