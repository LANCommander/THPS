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
	CVector(int _x, int _y, int _z) {
		vz = _z;
		vx = _x;
		vy = _y;
	}
};

struct CSVector {
	short vx, vy, vz;
};

struct SHighlight {
	short FromFrame;
	short ToFrame;
	int Score;
};

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
	CVector mPos; /* 0x004 */
	char pad10[0x6c - 0x10];
	int m6c; /* 0x06c */
	int pad70;
	int m74; /* 0x074 */
	char pad78[0xbc - 0x78];
	int mbc; /* 0x0bc */
	int padc0;
	int mc4; /* 0x0c4 */
	char padc8[0x146 - 0xc8];
	ushort m146; /* 0x146 */
	char pad148[0x2e4 - 0x148];
	int m2e4; /* 0x2e4 */
	char pad2e8[0x734 - 0x2e8];
	int m734; /* 0x734 */
	char pad738[0x7d8 - 0x738];
	int m7d8; /* 0x7d8 */
	int pad7dc;
	int m7e0; /* 0x7e0 */
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

extern SVideoInfo GVInfo1[2];
extern CBruce *MechList;
extern int Status;
extern int BitCount;
extern int UseCacheForBits;
extern int GNumberOfPlayers;

int GVideoReplay;

extern "C" void CamPt_SetClosestCamera__FP6CBruce(CBruce *);
void RestartCompFrig();
extern "C" void Video_Start__FP6CBruce10EVideoModeii(CBruce *, int, int, int);
extern "C" void GetDataChunk__FP6CBrucei(CBruce *, int);
extern "C" int Mips_DotProd2(int, int, int, int);
extern "C" void Bit_SetSparkTrajectoryCone__FRC8CSVector(const CSVector &);
extern "C" void Platform_HandleBounce__Fv();
extern "C" void Front_SwitchOnVideoScreen__Fv();
void Bit_SetSparkTrajectory(const CSVector &);
void Video_SyncObsIfNeeded();
void Video_Stop(CBruce *);

#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

void Video_Playback(CBruce *pSkater) {
	SVideoInfo *VInfo;

	CamPt_SetClosestCamera__FP6CBruce(pSkater);

	if (pSkater == MechList)
		VInfo = &GVInfo1[0];
	else
		VInfo = &GVInfo1[1];

	if (Status == 20 || Status == 22 || Status == 21) {
		if (!VInfo->FramesLeft) {
			RestartCompFrig();
			Video_Start__FP6CBruce10EVideoModeii(pSkater, 2, 1, 0x7fffffff);
		}
	}

	if (VInfo->FramesLeft) {
		int IsAGrind;

		GetDataChunk__FP6CBrucei(pSkater, 1);

		VInfo->FramesLeft--;
		IsAGrind =
		    ABS(Mips_DotProd2(-pSkater->m7e0, pSkater->m6c, pSkater->m7d8, pSkater->m74)) < 40000;
		int st = pSkater->m734;

		if (st == 4 && (IsAGrind || pSkater->m146 == 58) && BitCount < 200) {
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
			Bit_SetSparkTrajectoryCone__FRC8CSVector(cone);

			UseCacheForBits = 0;
			CVector SparkPos(0, 0x19000, 0);

			for (int i = 0; i < 9; i++)
				new CGrindSpark((CBody *)pSkater, SparkPos, -40, 4096, 5);

			st = pSkater->m734;
			UseCacheForBits = 1;
		}

		if (st || ABS(pSkater->mPos.vy - pSkater->m2e4) > 64) {
			pSkater->m2e4 = pSkater->mPos.vy;
			pSkater->DoShadowCheck();
		} else {
			pSkater->mbc = pSkater->mPos.vx;
			pSkater->mc4 = pSkater->mPos.vz;
		}

		pSkater->GlowUpdate();
		Platform_HandleBounce__Fv();
		pSkater->HandleWater();
	} else {
		if ((uint)(VInfo->ReplayHighlight - 1) < 4 &&
		    VInfo->Highlights[VInfo->ReplayHighlight].Score) {
			int StartFrame = VInfo->Highlights[VInfo->ReplayHighlight].FromFrame;
			int EndFrame = VInfo->Highlights[VInfo->ReplayHighlight].ToFrame;

			if (EndFrame != 0x7fffffff)
				VInfo->FramesLeft = EndFrame - StartFrame + 1;

			{
				int n = GVideoReplay;

				VInfo->ReplayHighlight++;
				GVideoReplay = n + 1;
			}

			Video_SyncObsIfNeeded();
		} else {
			Video_Stop(pSkater);

			if (GNumberOfPlayers == 1 || pSkater == MechList)
				Front_SwitchOnVideoScreen__Fv();
		}
	}
}
