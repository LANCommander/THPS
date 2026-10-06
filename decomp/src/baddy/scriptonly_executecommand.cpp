/* ExecuteCommand__16CScriptOnlyBaddyUs (0x8004169c) flags=-fstructure-noalias */
/* C++ (BADDY.CPP). Demo twin; locals and blocks from its MAIN.SYM. Layout by THPS1 offsets.
   Script-only baddy commands: looping sounds, snapping to the skater, a flag toggle, smoke jets
   and the rain effect (a set of falling CGPolyLine droplets around the skater). */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
	CVector() {}
	CVector(int x, int y, int z) { vx = x; vy = y; vz = z; }
	void Set(int x, int y, int z) { vx = x; vy = y; vz = z; }
	CVector &operator+=(const CVector &);
};
CVector operator-(const CVector &, const CVector &);
CVector operator+(const CVector &, const CVector &);
CVector operator>>(const CVector &, const int &);
struct CSVector { short vx, vy, vz; };

class CBit {
public:
	char pad0[0x42];
	uchar mKeep;                /* 0x42 */
	char pad43;
	virtual ~CBit();
	static void *operator new(uint) throw();
};
struct SLineSeg {
	CVector End;
	uchar r, g, b, code;
};
class CGPolyLine : public CBit {
public:
	int mNumSegs;               /* 0x48 */
	SLineSeg *mSegs;            /* 0x4c */
	CVector mStart;             /* 0x50 */
	uchar mStartR, mStartG, mStartB, mCode;
	uchar mForcedPriority;
	char pad61[3];
	CGPolyLine(int);
	void SetSemiTransparent();
};
class CSmokeJet : public CBit {
public:
	char pad48[0x16c - 0x48];
	CSmokeJet(const CVector &, const CSVector &, int, ushort, int, int, int, int, uchar, uint);
};
struct SRainEntry {
	CVector vel;
	CGPolyLine *p_line;
};
struct SObj { char pad[0x6c]; CVector v6c; };
struct SSkater { char pad[4]; CVector mPos; };

class CBaddy {
public:
	ushort mFlags;
	ushort mInquiry;
	CVector mPos;               /* 0x04 */
	CSVector mAngles;           /* 0x10 */
	char p16[0x1ac - 0x16];
	uint m1AC;                  /* 0x1ac */
	ushort *pScript;            /* 0x1b0 */
	char p1b4[0x220 - 0x1b4];
	int ExecuteCommand(ushort command);
	int GetScriptValue();
};
class CScriptOnlyBaddy : public CBaddy {
public:
	ushort mWeatherData;        /* 0x220 */
	SRainEntry *mpWeather;      /* 0x224 */
	CSmokeJet *mpSmokeJet;      /* 0x228 */
	uint mLoopingSound;         /* 0x22c */
	int mLoopingSoundUpdate;    /* 0x230 */
	int mLoopingSoundVol;       /* 0x234 */
	int ExecuteCommand(ushort command);
};

extern const int DAT_800d1acc;
extern SSkater *DAT_800d19a4;
extern int DAT_800d186c;
extern SObj *DAT_800d2044;
void SFX_Stop(uint);
uint SFX_PlayX(uint, short, int);
uint SFX_PlayPos(uint, const CVector &, int);
void *Mem_New(uint, int, int);
int Rnd(int);

int CScriptOnlyBaddy::ExecuteCommand(ushort command)
{
	switch (command) {
	case 17671:
		if (mLoopingSound)
			SFX_Stop(mLoopingSound);
		mLoopingSound = SFX_PlayX(*pScript++, 0x2000, 0);
		mLoopingSoundUpdate = -1;
		mLoopingSoundVol = DAT_800d1acc;
		break;
	case 17672: {
		if (mLoopingSound)
			SFX_Stop(mLoopingSound);
		ushort sound = *pScript++;
		mLoopingSoundUpdate = *pScript++;
		mLoopingSound = SFX_PlayPos(sound, mPos, 0);
		mLoopingSoundVol = DAT_800d1acc;
		break;
	}
	case 17673:
		if (mLoopingSound)
			SFX_Stop(mLoopingSound);
		mLoopingSound = 0;
		break;
	case 17670:
		if (DAT_800d19a4) {
			mPos = DAT_800d19a4->mPos;
			return 1;
		}
		break;
	case 18176:
		if (*pScript++)
			m1AC |= 0x100;
		else
			m1AC &= ~0x100;
		break;
	case 17668:
		pScript += 4;
	case 17051:
		mpSmokeJet = new CSmokeJet(mPos, mAngles, pScript[0], 0xffff, pScript[1], pScript[2], pScript[3], pScript[4], ((uchar *)pScript)[10], 0xcce0187c);
		mpSmokeJet->mKeep = 1;
		pScript += 6;
		break;
	case 17057:
		mpSmokeJet = new CSmokeJet(mPos, mAngles, pScript[0], 0xffff, pScript[1], pScript[2], pScript[3], pScript[4], ((uchar *)pScript)[10], 0x68b7b136);
		pScript += 6;
		break;
	case 17055:
		delete mpSmokeJet;
		mpSmokeJet = 0;
		break;
	case 17667: {
		mWeatherData = GetScriptValue();
		mpWeather = (SRainEntry *)Mem_New(mWeatherData * 16, 0, 1);
		CVector origin = DAT_800d19a4->mPos;
		DAT_800d186c = 0;
		for (int i = 0; i < mWeatherData; i++) {
			SRainEntry *p_entry = &mpWeather[i];
			CVector offset((Rnd(2400) - 1200) << 12, (Rnd(400) - 1200) << 12, (Rnd(2400) - 1200) << 12);
			offset += origin;
			p_entry->vel.Set((Rnd(16) - 8) << 12, (Rnd(48) + 48) << 12, (Rnd(16) - 8) << 12);
			CGPolyLine *p_droplet = new CGPolyLine(1);
			p_entry->p_line = p_droplet;
			p_droplet->mKeep = 1;
			p_droplet->mStart = offset;
			p_droplet->mSegs->End = (offset - p_entry->vel) + (DAT_800d2044->v6c >> 1);
			p_droplet->mStartR = 64;
			p_droplet->mStartG = 64;
			p_droplet->mStartB = 80;
			p_droplet->mSegs->r = 16;
			p_droplet->mSegs->g = 16;
			p_droplet->mSegs->b = 32;
			p_droplet->SetSemiTransparent();
		}
		DAT_800d186c = 1;
		break;
	}
	default:
		return CBaddy::ExecuteCommand(command);
	}
	return 1;
}
