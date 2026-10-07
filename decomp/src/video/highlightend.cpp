/* Video_HighlightEnd__FP6CBrucei (0x80068fd8) flags=-fstructure-noalias */
/* C++ (VIDEO.CPP). Demo twin. Inserts a finished trick into the player's top-5 replay highlights. */
#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))
struct SHighlight { short FromFrame; short ToFrame; int Score; };
struct SVideoInfo {
	char pad0[0x1c];
	unsigned int NumFrames;
	char pad1[0x30];
	SHighlight Highlights[5];
	char pad2[0x48];
};
struct CBruce { int vf; int x; int y; int z; };
extern SVideoInfo DAT_800bf318[2];
extern CBruce *DAT_800d19a4;
int DAT_800d1dec;
int DAT_800d1e0c;
int DAT_800d1e10;
int DAT_800d1e14;
int DAT_800d1e18;
void Video_HighlightEnd(CBruce *pSkater, int Score)
{
	SVideoInfo *VInfo;
	int WasABail;
	if (pSkater == DAT_800d19a4)
		VInfo = &DAT_800bf318[0];
	else
		VInfo = &DAT_800bf318[1];
	DAT_800d1dec = 0;
	DAT_800d1e10 = VInfo->NumFrames;
	DAT_800d1e18 = pSkater->y;
	WasABail = (Score < 0);
	if (Score < 0)
		Score = -Score;
	if (Score == 0)
		Score = (ABS(DAT_800d1e18 - DAT_800d1e14) * 2) >> 12;
	else
		Score += ABS(DAT_800d1e18 - DAT_800d1e14) >> 13;
	for (int i = 0; i < 5; i++) {
		if (VInfo->Highlights[i].Score < Score) {
			for (int j = 4; j > i; j--)
				VInfo->Highlights[j] = VInfo->Highlights[j - 1];
			DAT_800d1e0c -= 15;
			if (DAT_800d1e0c < 0) DAT_800d1e0c = 0;
			if (WasABail)
				DAT_800d1e10 += 30;
			else
				DAT_800d1e10 += 8;
			if (DAT_800d1e10 >= 3600) DAT_800d1e10 = 3599;
			VInfo->Highlights[i].FromFrame = DAT_800d1e0c;
			VInfo->Highlights[i].ToFrame = DAT_800d1e10;
			VInfo->Highlights[i].Score = Score;
			break;
		}
	}
}
