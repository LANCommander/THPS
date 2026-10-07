/* HandleStickToRail__6CBruce (0x8003058c) flags=-fstructure-noalias */
/* C++ (PHYSICS.CPP). Called from DoPhysics where the demo calls HandleStickToRail. THPS1 keeps the
   demo's StartHandPlant and StartGrind as inline helpers (their Debug_RunAnim lines 1536..1548 and
   1667..1835 are this file's __LINE__s) and adds a button-combo rail-trick lookup in the 44-byte
   trick table (entries from 32 on, keyed by style + two button codes) whose result both helpers use.
   Levers: the balance product distributes into GetStat's three arms only because the multiplicand
   is an inline call (GetBalanceVel(); a plain member or local is not distributed by fold); the
   table walk reads the body through a local table pointer and the test into a variable, which
   keeps the two pointer givs apart as in retail; `char *pName` loaded before the Trick_Trick call
   gives retail's score-first argument loads; the Limit test is two ifs on a State local (not an
   || that folds to & 0x6000); `case 0: break;` gives the m210 slti tree; Bailing as two `= 1`
   stores. Residues: the 2*index giv and pre-test load schedule in the trick walk, the
   GetBalanceVel copy/arm register roles (a1/a2/a3: retail's DAT arm uses the load, the stat
   arms the copy; ours the reverse), and the Direction call's a0 move / name-table base register
   (Score read into a local between the m368 and mGrindTrick stores gives retail's lhu-first order). */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
}
typedef unsigned short ushort;
typedef unsigned char uchar;
#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))
struct CVector {
	int vx, vy, vz;
	CVector &operator+=(const CVector &);
	CVector &operator*=(const int &);
};
struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};
struct SControl {
	SButton Triangle;         /* 0x00 */
	SButton Square;           /* 0x10 */
	SButton Circle;           /* 0x20 */
	SButton X;                /* 0x30 */
	SButton LeftOne;          /* 0x40 */
	SButton LeftTwo;          /* 0x50 */
	SButton RightOne;         /* 0x60 */
	SButton RightTwo;         /* 0x70 */
	SButton Left;             /* 0x80 */
	SButton Right;            /* 0x90 */
	SButton Up;               /* 0xa0 */
	SButton Down;             /* 0xb0 */
};
struct SSkater {
	char pad0[0xc];
	int Style;                /* 0x0c */
	char pad10[0x18 - 0x10];
	int Stats[10];            /* 0x18 */
	char pad40[340 - 0x40];
};
struct STrick {
	int Flags;                /* 0x00 */
	int Anim;                 /* 0x04 */
	int w2;                   /* 0x08 */
	char *pName;              /* 0x0c */
	int Frames;               /* 0x10 */
	int w5;                   /* 0x14 */
	int MinFrame;             /* 0x18 */
	int Score;                /* 0x1c */
	int w8, w9, w10;
};
extern SSkater DAT_800a44fc[];
extern STrick DAT_800a7358[];
extern char DAT_8009fcbc[];
extern ushort DAT_800a7edc[];
extern char *DAT_800a7ef0[];
int DAT_800d1924;
extern int DAT_800d172c;
extern int DAT_800d1770;
class CBruce {
public:
	char pad0[0x4];
	CVector mPos;             /* 0x4 */
	char pad10[0x6c - 0x10];
	CVector mVel;             /* 0x6c */
	char pad78[0x134 - 0x78];
	int mFlags;               /* 0x134 */
	char pad138[0x144 - 0x138];
	short mFrame;             /* 0x144 */
	char pad146[0x14e - 0x146];
	uchar m14E;               /* 0x14e */
	char pad14f[0x150 - 0x14f];
	int m150;                 /* 0x150 */
	char pad154[0x198 - 0x154];
	uchar *mpStatBonus;       /* 0x198 */
	char pad19c[0x204 - 0x19c];
	int m204;                 /* 0x204 */
	char pad208[0x20c - 0x208];
	int m20C;                 /* 0x20c */
	int m210;                 /* 0x210 */
	char pad214[0x220 - 0x214];
	int m220;                 /* 0x220 */
	char pad224[0x238 - 0x224];
	int m238;                 /* 0x238 */
	char pad23c[0x248 - 0x23c];
	int m248;                 /* 0x248 */
	char pad24c[0x254 - 0x24c];
	int m254;                 /* 0x254 */
	char pad258[0x268 - 0x258];
	int m268;                 /* 0x268 */
	int m26C;                 /* 0x26c */
	char pad270[0x274 - 0x270];
	int m274;                 /* 0x274 */
	int m278;                 /* 0x278 */
	char pad27c[0x2e8 - 0x27c];
	int mSkaterIndex;         /* 0x2e8 */
	int m2EC;                 /* 0x2ec */
	char pad2f0[0x310 - 0x2f0];
	int m310;                 /* 0x310 */
	int m314;                 /* 0x314 */
	char pad318[0x320 - 0x318];
	int m320;                 /* 0x320 */
	char pad324[0x328 - 0x324];
	int m328;                 /* 0x328 */
	int m32C;                 /* 0x32c */
	char pad330[0x358 - 0x330];
	int m358;                 /* 0x358 */
	int m35C;                 /* 0x35c */
	int m360;                 /* 0x360 */
	int m364;                 /* 0x364 */
	int m368;                 /* 0x368 */
	char pad36c[0x424 - 0x36c];
	int m424;                 /* 0x424 */
	char pad428[0x6dc - 0x428];
	int m6DC;                 /* 0x6dc */
	int m6E0;                 /* 0x6e0 */
	int m6E4;                 /* 0x6e4 */
	int mRailStart;           /* 0x6e8 */
	char pad6ec[0x6f4 - 0x6ec];
	CVector m6F4;             /* 0x6f4 */
	CVector mRailDir;         /* 0x700 */
	int m70C;                 /* 0x70c */
	int m710;                 /* 0x710 */
	char pad714[0x720 - 0x714];
	int m720;                 /* 0x720 */
	int m724;                 /* 0x724 */
	int m728;                 /* 0x728 */
	char pad72c[0x734 - 0x72c];
	int mPhysicsState;        /* 0x734 */
	char pad738[0x760 - 0x738];
	int m760;                 /* 0x760 */
	char pad764[0x7d8 - 0x764];
	CVector mFront;           /* 0x7d8 */
	CVector mRight;           /* 0x7e4 */
	CVector mUp;              /* 0x7f0 */
	char pad7fc[0x86c - 0x7fc];
	SControl *mPad;           /* 0x86c */
	char pad870[0x894 - 0x870];
	signed char mAX;          /* 0x894 */
	signed char mAY;          /* 0x895 */
	char pad896[0x8cc - 0x896];
	CVector m8CC;             /* 0x8cc */
	CVector mLastScorePos;    /* 0x8d8 */
	int mBalance;             /* 0x8e4 */
	int mBalanceVel;          /* 0x8e8 */
	char pad8ec[0x8f0 - 0x8ec];
	int mRailTime;            /* 0x8f0 */
	int mGrindTrick;          /* 0x8f4 */
	int GetBalanceVel() { return mBalanceVel; }
	void Trick_Trick(int, char *, int, int);
	void StateTransition(int, int);
	void StartHandPlant(int, int);
	void StartGrind(int);
	void HandleStickToRail();
};
#define GetStat(n) (DAT_800d1924 ? DAT_800d1924 \
	: (DAT_800a44fc[mSkaterIndex].Stats[n] + ((m254 || DAT_800d172c) ? 3 : 0)) + mpStatBonus[n])
int SFX_PlayX(unsigned int, short, int);
int Redbook_Rnd(int);
extern "C" {
void FUN_8002f1a0(CBruce *);
void FUN_8002fcdc(CBruce *, int, int);
void FUN_8002fd28(CBruce *, int, int, int);
void FUN_8002fd80(CBruce *, int, int, int, int);
void FUN_8002fe9c(CBruce *, int);
void FUN_8003159c(CBruce *);
void FUN_80030434(CBruce *);
void FUN_800429d0(CBruce *);
int FUN_800720ec(CVector *, CVector *);
}

inline void CBruce::StartHandPlant(int RailTrick, int Flags)
{
	m150 = 0x10000;
	m248 = 0;
	if (!m760) {
		FUN_8002f1a0(this);
		if (!m760) {
			m6E0 = 0;
			return;
		}
	}
	if (RailTrick && (Flags & 0x2000000)) {
		char *pName = DAT_800a7358[RailTrick].pName;
		Trick_Trick(RailTrick, pName, DAT_800a7358[RailTrick].Score, 0);
		FUN_8002fcdc(this, DAT_800a7358[RailTrick].Anim, 1536);
		m368 |= 0x4800;
		SFX_PlayX(162, 0x2000, 0);
	} else {
		Trick_Trick(79, DAT_8009fcbc, 1000, 0);
		FUN_8002fd28(this, 34, 8, 1544);
		m368 |= 0x4800;
	}
	StateTransition(8, 1548);
	SFX_PlayX(38, 0x2000, 0);
	mPos = m6F4;
	mPos.vy -= 30;
	FUN_80030434(this);
	mVel.vx = 0;
	mVel.vz = 0;
	m710 = mRailStart;
	mVel.vy = -mVel.vy;
}

inline void CBruce::StartGrind(int RailTrick)
{
	int RightDot;
	int Direction;
	int Score;

	if (!RailTrick || (DAT_800a7358[RailTrick].Flags & 0x2000000))
		RailTrick = 0;
	FUN_800429d0(this);
	m204 = 0;
	mPos = m6F4;
	m6E0 = 0;
	m6DC = 1;
	mPos.vy += -0x19000;
	m710 = mRailStart;
	mLastScorePos = mPos;
	m8CC = mPos;
	if (mRailStart != m6E4) {
		mRailTime -= 30;
		if (mRailTime < 0)
			mRailTime = 0;
		mBalanceVel = 0;
		m6E4 = mRailStart;
	} else
		mRailTime += 40;
	mBalanceVel = GetBalanceVel() * (100 - GetStat(3) * 15) / 100 * (mRailTime + 60) / 80;
	m20C++;
	{
		CVector Vel = mRailDir;
		Vel *= GetStat(1) + 5;
		mVel += Vel;
	}
	switch (m210) {
	case 0:
		break;
	case 1:
		SFX_PlayX(Redbook_Rnd(2) + 36, 0x2000, 0);
		break;
	case 2:
		SFX_PlayX(Redbook_Rnd(2) + 38, 0x2000, 0);
		break;
	}
	StateTransition(4, 1667);
	m35C = 1;
	m424++;
	m238++;
	FUN_80030434(this);
	FUN_800720ec(&mRailDir, &mFront);
	RightDot = FUN_800720ec(&mRailDir, &mRight);
	m320 = 0;
	if (RailTrick) {
		SFX_PlayX(162, 0x2000, 0);
		m368 = 0x80001000;
		Score = DAT_800a7358[RailTrick].Score;
		Trick_Trick(RailTrick, DAT_800a7358[RailTrick].pName, Score, 0);
		m364 = 1;
		m2EC = 0;
		mGrindTrick = 0;
		if (!DAT_800a7358[RailTrick].Frames)
			FUN_8002fcdc(this, DAT_800a7358[RailTrick].Anim, 1701);
		else
			FUN_8002fd80(this, DAT_800a7358[RailTrick].Anim, 0, DAT_800a7358[RailTrick].Frames, 1705);
		return;
	}
	if (ABS(RightDot) < 2867) {
		SControl *pPad = mPad;
		Direction = 6;
		if (pPad->Down.Pressed || mAY > 40) {
			if (pPad->Left.Pressed || mAX < -40) {
				Direction = 7;
				m320 = -180;
			} else if (pPad->Right.Pressed || mAX > 40) {
				Direction = 7;
				m320 = 180;
			} else
				Direction = 4;
		}
		if (pPad->Up.Pressed || mAY < -40) {
			if (pPad->Left.Pressed || mAX < -40)
				Direction = 8;
			else if (pPad->Right.Pressed || mAX > 40)
				Direction = 8;
			else
				Direction = 5;
		}
	} else {
		if (mFlags & 2)
			RightDot = -RightDot;
		mFlags &= ~2;
		if (RightDot < 0)
			Direction = 2;
		else
			Direction = 3;
	}
	m368 = 0x80001000;
	mGrindTrick = Direction;
	Score = DAT_800a7edc[Direction];
	Trick_Trick(Direction + 66, DAT_800a7ef0[Direction], Score, 0);
	m364 = 1;
	switch (Direction) {
	case 2:
		FUN_8002fd80(this, 17, 1, 8, 1808);
		m2EC = 2;
		break;
	case 3:
		FUN_8002fcdc(this, 17, 1813);
		m2EC = 1;
		break;
	case 4:
		FUN_8002fcdc(this, 67, 1817);
		m2EC = 0;
		break;
	case 5:
		FUN_8002fcdc(this, 68, 1823);
		m2EC = 0;
		break;
	case 6:
		FUN_8002fcdc(this, 70, 1827);
		m2EC = 0;
		break;
	case 8:
		FUN_8002fcdc(this, 57, 1831);
		m2EC = 0;
		break;
	case 7:
		FUN_8002fcdc(this, 58, 1835);
		m2EC = 0;
		break;
	}
}

void CBruce::HandleStickToRail()
{
	int Bailing;
	int Limit;
	int RailTrick;
	int Flags;

	if (!mPad->Triangle.Pressed)
		m310 = 0;
	if (!mPad->Triangle.Pressed || m358 || (mPhysicsState == 2 && mVel.vy > 0) || m314)
		goto NoRail;
	if (m70C > 0 && --m70C > 0) {
		m6DC = 0;
		goto NoRail;
	}
	if (!m6E0 || m6DC)
		goto NoRail;
	m70C = 0;
	if (mPhysicsState == 0) {
		m32C = 0;
		m328 = 0;
	}
	Limit = 10000;
	{
		int State = m368;
		int Trick = State & 0xff;
		if (State & 0x4000)
			Limit = m14E - DAT_800a7358[Trick].MinFrame;
		else if (State & 0x2000)
			Limit = m14E - DAT_800a7358[Trick].MinFrame;
	}
	Bailing = 0;
	if (m720) {
		if (m728 > 0) {
			if ((m724 & 4095) < 3796)
				Bailing = 1;
		} else if ((m724 & 4095) > 300)
			Bailing = 1;
	}
	if ((m35C && !m360 && mFrame < Limit) || Bailing) {
		FUN_8002fe9c(this, 0);
		m220++;
		return;
	}
	if (m35C) {
		FUN_8003159c(this);
		m364 = 1;
	}
	RailTrick = 0;
	Flags = 0;
	if (m254 && m278 && DAT_800d1770 - m274 < 35 && m268 && DAT_800d1770 - m26C < 45) {
		STrick *pTab = DAT_800a7358;
		Flags = DAT_800a44fc[mSkaterIndex].Style + (m268 << 8) + (m278 << 4) + 3;
		int f;
		for (RailTrick = 32; (f = DAT_800a7358[RailTrick].Flags) > 0; RailTrick++) {
			if ((pTab[RailTrick].Flags & 0xfffff) == Flags) {
				Flags = pTab[RailTrick].Flags;
				break;
			}
		}
		if (DAT_800a7358[RailTrick].Flags <= 0)
			RailTrick = 0;
	}
	if (mVel.vy < 0 && ABS(mUp.vy) < 3000 && ABS(mRight.vy) < 2048 && mPad->Up.Pressed)
		StartHandPlant(RailTrick, Flags);
	else if (m760)
		StartGrind(RailTrick);
	else
		goto NoRail;
	return;
NoRail:
	m6E0 = 0;
}
