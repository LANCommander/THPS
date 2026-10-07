/* TrickTips_Update__Fv (0x80072404) */
/* C++ (TRICKTIPS.CPP). Fuzzy demo twin (0.967); the SYM shows the body is all inlined helpers
   (tip, tip_mask, tip_used, tip_bank locals). The FindTip() path uses its own copy of the
   show-tip inline (ShowFoundTip): the SYM gives that copy tip_mask/tip_used/tip_bank declared at
   the top, and its sched1 order (TipsShown address and load first, tip_mask set twice) needs the
   `tip_mask &= bit` split plus two nested one-pass loops (macro-like); the constant-tip copies
   keep the single-expression form.
   Residue (1 word): retail loads TipsShown after the sllv; ours loads it before. */
typedef unsigned char uchar;
typedef unsigned int uint;

struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton b[16];
	char pad100[0x16c - 0x100];
};
class CBruce {
public:
	char pad0[0x20c];
	int mGrinds;               /* 0x20c */
	char pad210[0x218 - 0x210];
	int mBails;                /* 0x218 */
	int mPerpendicularBails;   /* 0x21c */
	int mTrickBails;           /* 0x220 */
	int mRailBails;            /* 0x224 */
	int mJumps;                /* 0x228 */
	int mWeakJumps;            /* 0x22c */
	int mAirs;                 /* 0x230 */
	int mTricks;               /* 0x234 */
	int mRails;                /* 0x238 */
	int mAirPolys;             /* 0x23c */
	int mAirPolyBreaks;        /* 0x240 */
	int mBigAirs;              /* 0x244 */
};
struct STip {
	int Flag;
	int pad4;
	char *Line1;
	char *Line2;
	char *Line3;
};
struct SLevel {
	char pad0[12];
	int NoTips;                /* 0x0c */
	char pad10[0x58 - 0x10];
	int DisabledTips[2];       /* 0x58 */
	char pad60[120 - 0x60];
};
struct SCareer {
	char pad0[0x974];
	int TipsSeen[2];           /* 0x974 */
	int TipsShown[2];          /* 0x97c */
	char pad984[0x9b4 - 0x984];
	int TipsOn;                /* 0x9b4 */
};
struct SVideoInfo {
	int VideoMode;
};
struct CTrickTipMonitor {
	char pad0[0x58];
	uint mTimer;               /* 0x58 */
	uint mLastTipTime;         /* 0x5c */
	uint mJumpTimer;           /* 0x60 */
	CBruce *pSkater;           /* 0x64 */
	char mTipLine1Buf[40];
	char *mTipLine1;           /* 0x90 */
	char *mTipLine2;
	char *mTipLine3;
	char *mTipLine4;
	uint mTipTimer;            /* 0xa0 */
	int mOldBails;
	int mOldPerpendicularBails;
	int mOldTrickBails;
	int mOldRailBails;
	int mOldJumps;
	int mOldWeakJumps;
	int mOldAirs;
	int mOldTricks;
	int mOldRails;
	int mOldAirPolys;
	int mOldAirPolyBreaks;
	int mOldBigAirs;
	int mOldGrinds;
	int mBailCounter;
	int mPerpendicularBailCounter;
	int mTrickBailCounter;
	int mRailBailCounter;
	int mJumpCounter;
	int mWeakJumpCounter;
	int mAirCounter;
	int mTrickCounter;
	int mRailCounter;
	int mAirPolyCounter;
	int mAirPolyBreakCounter;
	int mBigAirCounter;
	int mGrindCounter;
	int mHoldingForwardCounter;
	void ShowTip(int tip);
	void ShowFoundTip(int tip);
	int FindTip();
	void Update();
};
extern CTrickTipMonitor DAT_800d38c8;
extern SCareer DAT_800a6844;
extern SLevel DAT_800a5398[];
extern STip DAT_800a28c4[];
extern SVideoInfo DAT_800bf318[];
extern SVideoInfo DAT_800bf3d8[];
extern SControl DAT_800c0a48[2];
extern int DAT_800d1cb0;
extern int DAT_800d16a4;
extern CBruce *DAT_800d19a4;
extern int DAT_800d1e28;
char *DAT_800d1fa0;
char *DAT_800d1fa4;

static inline int TipBank(int tip)
{
	int tip_bank;
	if (tip < 32)
		tip_bank = 0;
	else if (tip < 64)
		tip_bank = 1;
	return tip_bank;
}

inline int CTrickTipMonitor::FindTip()
{
	int i;
	for (i = 0; i < 26; i++) {
		if (DAT_800a28c4[i].Flag)
			continue;
		if ((DAT_800a6844.TipsSeen[TipBank(i)] >> (i - TipBank(i) * 32)) & 1)
			continue;
		return i;
	}
	return -1;
}

inline void CTrickTipMonitor::ShowTip(int tip)
{
	if (!mTimer || mTimer >= mLastTipTime + 600) {
		mLastTipTime = mTimer;
		int tip_bank = TipBank(tip);
		if (DAT_800a6844.TipsOn) {
			if (((DAT_800a5398[DAT_800d1e28].DisabledTips[tip_bank] >> (tip - tip_bank * 32)) & 1) == 0) {
				int &seen = DAT_800a6844.TipsSeen[tip_bank];
				int tip_mask = DAT_800a6844.TipsShown[tip_bank] & (1 << (tip - tip_bank * 32));
				int tip_used = seen & (1 << (tip - tip_bank * 32));
				seen |= (1 << (tip - tip_bank * 32));
				if (!tip_mask) {
					if (tip_used) {
						mTipLine1 = DAT_800d1fa4;
						DAT_800a6844.TipsShown[tip_bank] |= 1 << (tip - tip_bank * 32);
					} else {
						mTipLine1 = DAT_800d1fa0;
					}
					mTipTimer = 200;
					mTipLine2 = DAT_800a28c4[tip].Line1;
					mTipLine3 = DAT_800a28c4[tip].Line2;
					mTipLine4 = DAT_800a28c4[tip].Line3;
				}
			}
		}
	}
}

inline void CTrickTipMonitor::ShowFoundTip(int tip)
{
	int tip_mask;
	int tip_used;
	int tip_bank;
	if (!mTimer || mTimer >= mLastTipTime + 600) {
		mLastTipTime = mTimer;
		tip_bank = TipBank(tip);
		if (DAT_800a6844.TipsOn) {
			if (((DAT_800a5398[DAT_800d1e28].DisabledTips[tip_bank] >> (tip - tip_bank * 32)) & 1) == 0) {
				do {
					tip_mask = DAT_800a6844.TipsShown[tip_bank];
					do {
						tip_used = DAT_800a6844.TipsSeen[tip_bank];
						tip_mask &= (1 << (tip - tip_bank * 32));
					} while (0);
					DAT_800a6844.TipsSeen[tip_bank] |= (1 << (tip - tip_bank * 32));
					tip_used &= (1 << (tip - tip_bank * 32));
				} while (0);
				if (!tip_mask) {
					if (tip_used) {
						mTipLine1 = DAT_800d1fa4;
						DAT_800a6844.TipsShown[tip_bank] |= 1 << (tip - tip_bank * 32);
					} else {
						mTipLine1 = DAT_800d1fa0;
					}
					mTipTimer = 200;
					mTipLine2 = DAT_800a28c4[tip].Line1;
					mTipLine3 = DAT_800a28c4[tip].Line2;
					mTipLine4 = DAT_800a28c4[tip].Line3;
				}
			}
		}
	}
}

inline void CTrickTipMonitor::Update()
{
	if (DAT_800a5398[DAT_800d1e28].NoTips)
		return;
	if (DAT_800bf318[0].VideoMode == 2 || DAT_800bf3d8[0].VideoMode == 2)
		return;
	if (!DAT_800d1cb0 || DAT_800d16a4 != 1)
		return;
	pSkater = DAT_800d19a4;
	if (!mTimer) {
		int tip = FindTip();
		if (tip >= 0)
			ShowFoundTip(tip);
	}
	mTimer++;
	mJumpTimer++;
	if (mOldTricks < pSkater->mTricks)
		mOldTricks = pSkater->mTricks;
	if (mOldGrinds < pSkater->mGrinds) {
		mOldGrinds = pSkater->mGrinds;
		mGrindCounter++;
		DAT_800a6844.TipsSeen[0] |= 0x100;
		DAT_800a6844.TipsShown[0] |= 0x100;
	}
	if (mOldJumps < pSkater->mJumps) {
		mOldJumps = pSkater->mJumps;
		mJumpTimer = 0;
		mJumpCounter++;
	}
	if (mJumpTimer > 600)
		mJumpTimer = 0;
	if (DAT_800c0a48[0].b[10].Pressed || DAT_800c0a48[1].b[10].Pressed)
		mHoldingForwardCounter++;
	else
		mHoldingForwardCounter = 0;
	if (mHoldingForwardCounter > 150) {
		ShowTip(1);
		mHoldingForwardCounter = 0;
	}
	if (mOldAirPolyBreaks < pSkater->mAirPolyBreaks) {
		mOldAirPolyBreaks = pSkater->mAirPolyBreaks;
		if (++mAirPolyBreakCounter >= 3) {
			mAirPolyBreakCounter = 0;
			if (mBigAirCounter < 3)
				ShowTip(6);
		}
	}
	if (mOldAirPolys < pSkater->mAirPolys) {
		mOldAirPolys = pSkater->mAirPolys;
		mAirPolyCounter++;
	}
	if (mOldBigAirs < pSkater->mBigAirs) {
		mOldBigAirs = pSkater->mBigAirs;
		mBigAirCounter++;
	}
	if (mOldWeakJumps < pSkater->mWeakJumps) {
		mOldWeakJumps = pSkater->mWeakJumps;
		if (++mWeakJumpCounter >= 5) {
			ShowTip(5);
			mWeakJumpCounter = 0;
		}
	}
	if (mOldBails < pSkater->mBails) {
		mOldBails = pSkater->mBails;
		if (++mBailCounter >= 3) {
			ShowTip(3);
			mBailCounter = 0;
		}
	}
	if (mOldPerpendicularBails < pSkater->mPerpendicularBails) {
		mOldPerpendicularBails = pSkater->mPerpendicularBails;
		if (++mPerpendicularBailCounter >= 3) {
			ShowTip(2);
			mPerpendicularBailCounter = 0;
		}
	}
	if (mOldRailBails < pSkater->mRailBails) {
		mOldRailBails = pSkater->mRailBails;
		if (++mRailBailCounter >= 3) {
			ShowTip(9);
			mRailBailCounter = 0;
		}
	}
}

void TrickTips_Update()
{
	DAT_800d38c8.Update();
}
