/* DisplayTime__FP6CBruceUsUs (0x8006d39c) */
/* C++ (PANEL.CPP). Fuzzy demo twin (0.31 by opcode, the same shape with the Mess_ text calls);
   locals from its MAIN.SYM. Draws a skater's run clock as m:ss, flashing in the last seconds, and
   ticks the urgent beep (faster as time runs out) for the first player. The two SVideoInfo blocks
   are one extern array: an unsized extern gives the split lui/addiu that keeps the if/else (a
   single `la` lets jump.c turn it into `VInfo = B; if (...) VInfo = A`). */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct CBruce {
	char pad0[0x330];
	int mTime;                 /* 0x330 */
};
struct SVideoInfo {
	int Mode;
	char pad4[0xc0 - 4];
};
extern int DAT_800d16a4;
extern CBruce *DAT_800d19a4;
extern CBruce *DAT_800d17c8;
extern SVideoInfo DAT_800bf318[];
extern int DAT_800d1770;
extern uint DAT_800d1a24;
extern int DAT_800d1790;
extern int DAT_800d1794;
extern char DAT_800a2394[];
int DAT_800d23c0;
int SFX_PlayX(unsigned int, short, int);
void Mess_SetRGB(uchar, uchar, uchar, int);
void Mess_SetTextJustify(uchar);
void Mess_SetScale(int);
int Mess_DrawPanelText(int, int, const char *, int, uint, int);
extern "C" {
void FUN_8001f138(int);
int FUN_8008b900(char *, const char *, ...);
}

void DisplayTime(CBruce *pBruce, ushort xpos, ushort ypos)
{
	char time[8];
	int ticks;
	int mins;
	int secs;

	if (DAT_800d16a4 == 2)
		return;
	if (DAT_800d16a4 == 7 && !pBruce->mTime)
		return;
	FUN_8001f138(DAT_800d1794);
	{
		SVideoInfo *VInfo;
		if (pBruce == DAT_800d19a4)
			VInfo = &DAT_800bf318[0];
		else
			VInfo = &DAT_800bf318[1];
		if (VInfo->Mode != 2) {
			ticks = pBruce->mTime - DAT_800d1770;
			mins = ticks / 3600;
			secs = (ticks - mins * 3600) / 60;
			if (ticks < 0) {
				secs = 0;
				mins = 0;
			}
			FUN_8008b900(time, DAT_800a2394, mins, secs);
			Mess_SetRGB(128, 0, 0, 0);
			Mess_SetTextJustify(0);
			Mess_SetScale(256);
			if (DAT_800d16a4 == 7) {
				if (mins || secs >= 4 || DAT_800d1a24 % 30 >= 15)
					Mess_DrawPanelText(xpos, ypos, time, 0, 0, 256);
			} else {
				if (mins || secs >= 11 || DAT_800d1a24 % 60 >= 30)
					Mess_DrawPanelText(xpos, ypos, time, 0, 0, 256);
				if (pBruce == DAT_800d17c8) {
					if (ticks >= 1 && ticks < 600) {
						if (ticks < DAT_800d23c0) {
							int sub;
							SFX_PlayX(22, 8192, 0);
							sub = DAT_800d23c0 / 10;
							if (sub < 10)
								sub = 10;
							DAT_800d23c0 -= sub;
						}
					} else {
						DAT_800d23c0 = 600;
					}
				}
			}
		}
	}
	FUN_8001f138(DAT_800d1790);
}
