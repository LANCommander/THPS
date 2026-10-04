/* DisplayTapesSkate__Fv (0x8006c7e8) */
typedef unsigned char uchar;
typedef unsigned int uint;
struct CBruce {
	char pad0[0x1c];
	int mDead;
	char pad1[0xdec - 0x20];
	int mTape[5];
};
extern CBruce *DAT_800d19a4;
extern uint DAT_800d1a24;
extern char DAT_800d1e6c[];
extern char DAT_800d1e70[];
extern char DAT_800d1e74[];
extern char DAT_800d1e78[];
extern char DAT_800d1e7c[];
int DAT_800d1e5c;
int DAT_800d1e60;
int DAT_800d1e64;
int DAT_800d1e68;
void Mess_SetRGB(uchar, uchar, uchar, int);
void Mess_SetTextJustify(uchar);
void Mess_SetScale(int);
void Mess_DrawPanelText(int, int, const char *, int, uint, int);
void DisplayTapesSkate(void)
{
	CBruce *pSkater = DAT_800d19a4;
	if (!pSkater->mDead) {
		if (DAT_800d1e64) {
			if (DAT_800d1e68 >= 483 && DAT_800d1e64 > 10)
				DAT_800d1e68 -= 4;
			if (DAT_800d1e64 < 10)
				DAT_800d1e68 = 522 - DAT_800d1e64 * 4;
			DAT_800d1e64--;
			Mess_SetRGB(((DAT_800d1a24 % 20) * 12) & 252, 100, 100, 0);
			Mess_SetTextJustify(1);
			Mess_SetScale(255);
			if (pSkater->mTape[0])
				Mess_DrawPanelText(DAT_800d1e68, 80, DAT_800d1e6c, 0, 0, 256);
			if (pSkater->mTape[1])
				Mess_DrawPanelText(DAT_800d1e68, 105, DAT_800d1e70, 0, 0, 256);
			if (pSkater->mTape[2])
				Mess_DrawPanelText(DAT_800d1e68, 130, DAT_800d1e74, 0, 0, 256);
			if (pSkater->mTape[3])
				Mess_DrawPanelText(DAT_800d1e68, 155, DAT_800d1e78, 0, 0, 256);
			if (pSkater->mTape[4])
				Mess_DrawPanelText(DAT_800d1e68, 180, DAT_800d1e7c, 0, 0, 256);
		}
		if (DAT_800d1e5c) {
			if (DAT_800d1e60 >= 482 && DAT_800d1e5c > 10)
				DAT_800d1e60 -= 4;
			if (DAT_800d1e5c < 11)
				DAT_800d1e60 = 511 - DAT_800d1e5c * 4;
			DAT_800d1e5c--;
		}
	}
}
