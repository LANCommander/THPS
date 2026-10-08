/* DisplayTrick__10CPanelDataP6CBruceUsUs (0x8006d938) */
/* C++ (PANEL.CPP). Demo twin CPanelData::DisplayTrick by signature and prologue (the demo body
   uses the Font/TextEffect classes THPS1 lacks). Draws the three trick-name lines bottom-up and
   animates the text scale: grow from 60 (state 1), settle to normal (2), hold for 30 frames (3),
   shrink away (4), or hand over to the message effect at +0x164 (5). Called on pBruce->mPanel.
   The per-mode scale pair is set in both arms (NormalScale first): that keeps jump.c from
   rewriting the if/else into "x = b; if (c) x = a;", giving retail's bne; j shape. */
typedef unsigned short ushort;
typedef unsigned int uint;

struct SVideoInfo {
	int VideoMode;
	char pad4[0xc0 - 4];
};

class CBruce;

class CPanelData {
  public:
	char pad0[0x14c];
	int mTrickState; /* 0x14c */
	int mTrickTimer; /* 0x150 */
	char pad154[0x158 - 0x154];
	int mTrickAbort; /* 0x158 */
	char pad15c[0x164 - 0x15c];
	char mTrickMess[0x38c - 0x164]; /* 0x164 */
	char mTrickLine1[100];          /* 0x38c */
	char mTrickLine2[100];          /* 0x3f0 */
	char mTrickLine3[100];          /* 0x454 */
	void DisplayTrick(CBruce *pBruce, ushort xpos, ushort ypos);
};

class CBruce {
  public:
	char pad0[0x924];
	CPanelData mPanel; /* 0x924 */
};

extern SVideoInfo DAT_800bf318;
extern int DAT_800a71fc[];
extern int DAT_800d1780;
extern int DAT_800d16fc;

void Mess_SetRGB(unsigned char, unsigned char, unsigned char, int);
void Mess_SetScale(int);
int Mess_GetScale(void);
int Mess_DrawPanelText(int, int, const char *, int, uint, int);

extern "C" {
	void FUN_8006ca1c(CBruce *);
	void FUN_8001d250(int);
	void FUN_8001e0a4(char *, int);
	void FUN_8001e0f8(char *, ushort);
	ushort FUN_8001e108(char *);
}

void CPanelData::DisplayTrick(CBruce *pBruce, ushort xpos, ushort ypos) {
	int ok = DAT_800bf318.VideoMode != 2;

	if (!ok)
		return;

	if (!DAT_800a71fc[0])
		return;

	Mess_SetRGB(128, 128, 128, 0);
	FUN_8006ca1c(pBruce);
	FUN_8001d250(0);
	int NormalScale;
	int BigScale;

	if (DAT_800d1780 == 1) {
		NormalScale = 188;
		BigScale = 256;
	} else {
		NormalScale = 188;
		BigScale = 188;
	}

	switch (mTrickState) {
		case 0:
			return;
		case 1: {
			int Frames = 5;

			Mess_SetScale((BigScale - 60) * mTrickTimer / Frames + 60);

			if (mTrickTimer == Frames) {
				mTrickTimer = 0;
				mTrickState = 2;
			}

			break;
		}
		case 2: {
			int Frames = 5;

			Mess_SetScale(BigScale + (NormalScale - BigScale) * mTrickTimer / Frames);

			if (mTrickTimer == Frames) {
				mTrickTimer = 0;
				mTrickState = 3;
			}

			break;
		}
		case 3:
			Mess_SetScale(188);

			if (mTrickTimer == 30) {
				mTrickTimer = 0;
				mTrickState = 4;
			}

			if (mTrickAbort) {
				mTrickState = 5;
				mTrickAbort = 0;
			}

			break;
		case 4: {
			int Frames = 10;

			Mess_SetScale(NormalScale + (0 - NormalScale) * mTrickTimer / Frames);

			if (mTrickTimer == Frames) {
				mTrickTimer = 0;
				mTrickState = 0;
			}

			if (mTrickAbort)
				mTrickAbort = 0;

			break;
		}
		case 5:
			break;
	}

	if (mTrickState == 5)
		FUN_8001e0a4(pBruce->mPanel.mTrickMess, 1);
	else
		FUN_8001e0f8(pBruce->mPanel.mTrickMess, Mess_GetScale());

	if (!DAT_800d16fc)
		mTrickTimer++;

	int LineHeight = Mess_GetScale() * 13 / 188;

	if (pBruce->mPanel.mTrickLine3[0]) {
		Mess_DrawPanelText(xpos, ypos, pBruce->mPanel.mTrickLine3, 0, 0, 256);

		ypos -= LineHeight;
	}

	if (pBruce->mPanel.mTrickLine2[0]) {
		Mess_DrawPanelText(xpos, ypos, pBruce->mPanel.mTrickLine2, 0, 0, 256);

		ypos -= LineHeight;
	}

	Mess_DrawPanelText(xpos, ypos, pBruce->mPanel.mTrickLine1, 0, 0, 256);
	int Busy = FUN_8001e108(pBruce->mPanel.mTrickMess);

	if (mTrickState == 5) {
		FUN_8001e0a4(pBruce->mPanel.mTrickMess, 0);

		if (!Busy)
			pBruce->mPanel.mTrickState = 0;
	}
}
