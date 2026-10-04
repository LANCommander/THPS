/* Video_Playback__FP6CBruce (0x8006a930) */
/* C++ (VIDEO.CPP). Fuzzy demo twin; locals and blocks from its MAIN.SYM. THPS1's version calls
   Platform_HandleBounce with no argument. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
	CVector() {}
	CVector(int _x, int _y, int _z) { vz = _z; vx = _x; vy = _y; }
};
struct CSVector { short vx, vy, vz; };
struct SHighlight { short FromFrame; short ToFrame; int Score; };
struct SVideoInfo {
	int VideoMode;
	unsigned long *pBlockStart, *pStreamStart, *pStreamEnd, *pStream;
	unsigned long Bits;
	int BitsLeft;
	unsigned long NumFrames;
	unsigned long FramesLeft;
	int CurCameraIndex;
	CVector CamPos;
	int CamMode, CamXblanks, TabuCam, NoLOS, OldCameraIndex, TrailingCameraType;
	int ReplayHighlight;
	SHighlight Highlights[5];
	int OldPhysicsState, OldAnim, OldFrame;
	SVECTOR Euler;
	SVECTOR OldEuler;
	CVector OldPos;
	CVector OldPos2;
	int OldFlipAngle, FlipAngleDelta, OldXblanks, Yblanks, PlaybackFrozen;
};

class CBody;
class CBruce {
public:
	char pad0[4];
	CVector mPos;              /* 0x004 */
	char pad10[0x6c - 0x10];
	int m6c;                   /* 0x06c */
	int pad70;
	int m74;                   /* 0x074 */
	char pad78[0xbc - 0x78];
	int mbc;                   /* 0x0bc */
	int padc0;
	int mc4;                   /* 0x0c4 */
	char padc8[0x146 - 0xc8];
	ushort m146;               /* 0x146 */
	char pad148[0x2e4 - 0x148];
	int m2e4;                  /* 0x2e4 */
	char pad2e8[0x734 - 0x2e8];
	int m734;                  /* 0x734 */
	char pad738[0x7d8 - 0x738];
	int m7d8;                  /* 0x7d8 */
	int pad7dc;
	int m7e0;                  /* 0x7e0 */
	void DoShadowCheck();
	void GlowUpdate();
	void HandleWater();
};
class CBit {
public:
	char pad[120];
	void *operator new(unsigned int) throw();
};
class CGrindSpark : public CBit {
public:
	CGrindSpark(CBody *pParent, CVector &pos, int vel, int gravity, int life);
};

extern SVideoInfo DAT_800bf318[2];
extern CBruce *DAT_800d19a4;
extern int DAT_800d13e8;
extern int DAT_800d1868;
extern int DAT_800d186c;
extern int DAT_800d1780;
int DAT_800d1de8;
extern "C" void FUN_8004e268(CBruce *);
void RestartCompFrig();
extern "C" void FUN_80069684(CBruce *, int, int, int);
extern "C" void FUN_8006a158(CBruce *, int);
extern "C" int FUN_800720ac(int, int, int, int);
extern "C" void FUN_8002952c(const CSVector &);
extern "C" void FUN_8003f65c();
extern "C" void FUN_8001a608();
void Bit_SetSparkTrajectory(const CSVector &);
void Video_SyncObsIfNeeded();
void Video_Stop(CBruce *);
#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

void Video_Playback(CBruce *pSkater)
{
	SVideoInfo *VInfo;

	FUN_8004e268(pSkater);
	if (pSkater == DAT_800d19a4)
		VInfo = &DAT_800bf318[0];
	else
		VInfo = &DAT_800bf318[1];

	if (DAT_800d13e8 == 20 || DAT_800d13e8 == 22 || DAT_800d13e8 == 21)
	{
		if (!VInfo->FramesLeft)
		{
			RestartCompFrig();
			FUN_80069684(pSkater, 2, 1, 0x7fffffff);
		}
	}

	if (VInfo->FramesLeft)
	{
		int IsAGrind;
		FUN_8006a158(pSkater, 1);
		VInfo->FramesLeft--;
		IsAGrind = ABS(FUN_800720ac(-pSkater->m7e0, pSkater->m6c, pSkater->m7d8, pSkater->m74)) < 40000;
		int st = pSkater->m734;
		if (st == 4 && (IsAGrind || pSkater->m146 == 58) && DAT_800d1868 < 200)
		{
			CSVector Angles;
			{
				short x = VInfo->Euler.vx, y = VInfo->Euler.vy, z = VInfo->Euler.vz;
				Angles.vx = x;
				Angles.vy = y;
				Angles.vz = z;
			}
			Bit_SetSparkTrajectory(Angles);
			CSVector cone;
			cone.vx = 450;
			cone.vy = 900;
			cone.vz = 0;
			FUN_8002952c(cone);
			DAT_800d186c = 0;
			CVector SparkPos(0, 0x19000, 0);
			for (int i = 0; i < 9; i++)
				new CGrindSpark((CBody *)pSkater, SparkPos, -40, 4096, 5);
			st = pSkater->m734;
			DAT_800d186c = 1;
		}
		if (st || ABS(pSkater->mPos.vy - pSkater->m2e4) > 64)
		{
			pSkater->m2e4 = pSkater->mPos.vy;
			pSkater->DoShadowCheck();
		}
		else
		{
			pSkater->mbc = pSkater->mPos.vx;
			pSkater->mc4 = pSkater->mPos.vz;
		}
		pSkater->GlowUpdate();
		FUN_8003f65c();
		pSkater->HandleWater();
	}
	else
	{
		if ((uint)(VInfo->ReplayHighlight - 1) < 4 && VInfo->Highlights[VInfo->ReplayHighlight].Score)
		{
			int StartFrame = VInfo->Highlights[VInfo->ReplayHighlight].FromFrame;
			int EndFrame = VInfo->Highlights[VInfo->ReplayHighlight].ToFrame;
			if (EndFrame != 0x7fffffff)
				VInfo->FramesLeft = EndFrame - StartFrame + 1;
			{
				int n = DAT_800d1de8;
				VInfo->ReplayHighlight++;
				DAT_800d1de8 = n + 1;
			}
			Video_SyncObsIfNeeded();
		}
		else
		{
			Video_Stop(pSkater);
			if (DAT_800d1780 == 1 || pSkater == DAT_800d19a4)
				FUN_8001a608();
		}
	}
}
