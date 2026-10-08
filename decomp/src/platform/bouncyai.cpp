/* BouncyAI__9CPlatform (0x8003db00) */
/* C++ (PLATFORM.CPP). Fuzzy demo twin (opcode-identical but for a few words); locals and blocks from its
   MAIN.SYM. THPS1's CPlatform fields sit 8 bytes past the demo's; the CBaddy part is laid out by offset. */
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
		vx = _x;
		vy = _y;
		vz = _z;
	}
	int Length() const;
	void KillSmall();
	CVector &operator%=(const struct CFriction &);
};

CVector operator+(const CVector &, const CVector &);

struct CSVector {
	short vx, vy, vz;
	void Mask();
	void KillSmall();
	CSVector &operator+=(const CSVector &);
};

struct CFriction {
	uchar vx, vy, vz;
	CFriction() {}
	CFriction(uchar x, uchar y, uchar z) {
		vx = x;
		vy = y;
		vz = z;
	}
};

struct Item;

struct SLineInfo {
	CVector StartCoords;
	CVector EndCoords;
	CVector MinCoords;
	CVector MaxCoords;
	int iLo, iHi, jLo, jHi;
	int Distance;
	int Length;
	MATRIX WorldCst;
	Item *pItem;
	CVector Position;
	SVECTOR Normal;
	uint *pFace;
	int Model;
	uchar RecordTriggerZoneHits;
	uchar DropDown;
	ushort Inquiry;
	int tNear;
	uint tNumtrLo;
	int tNumtrHi;
	uint tDenomLo;
	int tDenomHi;
	uint NormalOffset;
};

struct VT {
	char pad[0x10];
	short off;
	short pad2;
	void (*fn)(char *);
};

class CPlatform {
  public:
	ushort mFlags;
	ushort mInquiry;
	CVector mPos;     /* 0x004 */
	CSVector mAngles; /* 0x010 */
	char pad16[0x48 - 0x16];
	VT *vt; /* 0x048 */
	char pad4c[0x6c - 0x4c];
	CVector mVel; /* 0x06c */
	char pad78[0x88 - 0x78];
	CSVector mAngVel; /* 0x088 */
	char pad8e[0x1ac - 0x8e];
	uint mBaddyFlags; /* 0x1ac */
	char pad1b0[0x22a - 0x1b0];
	ushort mNumBounces; /* 0x22a */
	ushort mType;       /* 0x22c */
	ushort mWidth;      /* 0x22e */
	ushort mHeight;
	ushort mDepth;
	ushort mDeathTimer;     /* 0x234 */
	CSVector mTargetAngles; /* 0x236 */
	void BouncyAI();
};

extern "C" void FUN_8008b3d4(CSVector *, MATRIX *);
void M3dColij_InitLineInfo(SLineInfo *);
void M3dZone_LineToItemNotSCached(SLineInfo *, int);
int Mips_CVecDotProd(CVector *, CVector *);
int Mips_FixMul(int, int);
int Rnd(int);
int SFX_PlayX(unsigned int, short, int);

extern int GLevel;

#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

void CPlatform::BouncyAI() {
	MATRIX m;
	SLineInfo LInfo;
	CVector NewPos;
	CVector NewVel;
	CFriction Fric;
	int ObjectExtent;

	if (mDeathTimer && !--mDeathTimer) {
		vt->fn((char *)this + vt->off);
		return;
	}

	if (!(mBaddyFlags & 0x20))
		return;

	mTargetAngles.Mask();

	mAngVel.vx = (mTargetAngles.vx - mAngles.vx) >> 5;
	mAngVel.vy = (mTargetAngles.vy - mAngles.vy) >> 5;
	mAngVel.vz = (mTargetAngles.vz - mAngles.vz) >> 5;
	mAngVel.KillSmall();

	if (ABS(mAngVel.vx) < 40 && ABS(mTargetAngles.vx - mAngles.vx) > 40)
		mAngVel.vx = mAngVel.vx < 0 ? -40 : 40;

	if (ABS(mAngVel.vy) < 40 && ABS(mTargetAngles.vy - mAngles.vy) > 40)
		mAngVel.vy = mAngVel.vy < 0 ? -40 : 40;

	if (ABS(mAngVel.vz) < 40 && ABS(mTargetAngles.vz - mAngles.vz) > 40)
		mAngVel.vz = mAngVel.vz < 0 ? -40 : 40;

	mAngles += mAngVel;
	mAngles.Mask();
	FUN_8008b3d4(&mAngles, &m);

	ObjectExtent =
	    (mWidth * ABS(m.m[1][0]) + mHeight * ABS(m.m[1][1]) + mDepth * ABS(m.m[1][2])) >> 1;
	NewVel = mVel;
	NewVel.vy += 0x8000;
	Fric = CFriction(6, 6, 6);
	NewVel %= Fric;
	NewVel.KillSmall();

	NewPos = mPos + NewVel;
	CVector Dir = NewVel;

	Dir.vy = 0;
	int Speed = Dir.Length();

	for (int NumChecks = 0; NumChecks < 3; NumChecks++) {
		LInfo.StartCoords.vx = mPos.vx;
		LInfo.StartCoords.vy = mPos.vy;
		LInfo.StartCoords.vz = mPos.vz;
		LInfo.EndCoords.vx = NewPos.vx;
		LInfo.EndCoords.vy = NewPos.vy;
		LInfo.EndCoords.vz = NewPos.vz;
		M3dColij_InitLineInfo(&LInfo);
		M3dZone_LineToItemNotSCached(&LInfo, 1);

		if (!LInfo.pItem) {
			if (NewVel.vy > 0) {
				LInfo.StartCoords.vx = NewPos.vx;
				LInfo.StartCoords.vy = NewPos.vy;
				LInfo.StartCoords.vz = NewPos.vz;
				LInfo.EndCoords = LInfo.StartCoords;
				LInfo.StartCoords.vy -= ObjectExtent;
				LInfo.EndCoords.vy += ObjectExtent;
				M3dColij_InitLineInfo(&LInfo);
				M3dZone_LineToItemNotSCached(&LInfo, 1);
			}

			if (!LInfo.pItem) {
				mPos = NewPos;
				mVel = NewVel;
				break;
			}
		}

		if (mNumBounces < 5) {
			switch (mType) {
				case 1:
					SFX_PlayX(!Rnd(2) ? 103 : 102, 0x2000, 0);
					break;
				case 3:
					SFX_PlayX(40, 0x2000, 0);
					break;
				case 2:
					if (GLevel)
						SFX_PlayX(!Rnd(2) ? 107 : 106, 0x2000, 0);
					else
						SFX_PlayX(Rnd(2) + 83, 0x2000, 0);

					break;
				case 4:
					SFX_PlayX(!Rnd(2) ? 81 : 80, 0x2000, 0);
					break;
				case 5:
					SFX_PlayX(Rnd(2) + 83, 0x2000, 0);
					break;
			}
		}

		mNumBounces++;

		{
			CVector Normal(LInfo.Normal.vx, LInfo.Normal.vy, LInfo.Normal.vz);
			int dot = Mips_CVecDotProd(&NewVel, &Normal);

			NewVel.vx -= Mips_FixMul(Normal.vx, dot) * 2;
			NewVel.vy -= Mips_FixMul(Normal.vy, dot) * 2;
			NewVel.vz -= Mips_FixMul(Normal.vz, dot) * 2;
			Fric = CFriction(3, 2, 3);

			if (ABS(NewVel.vy) < 0xc000) {
				Fric.vy = 0;
				Fric.vz = 2;
				Fric.vx = 2;
			} else {
				mTargetAngles.vy = Rnd(4096);

				if (mNumBounces == 1) {
					mTargetAngles.vx += (short)((Rnd(2) << 11) - 1024);

					if ((mType == 2 || mType == 4) &&
					    ((mTargetAngles.vx == 0x800 && mTargetAngles.vz == 0) ||
					     (mTargetAngles.vx == 0 && mTargetAngles.vz == 0x800)))
						mTargetAngles.vx = (Rnd(2) << 11) - 1024;
				}

				if (mNumBounces == 1) {
					mTargetAngles.vz += (Rnd(3) - 1) << 10;

					if ((mType == 2 || mType == 4) &&
					    ((mTargetAngles.vx == 0x800 && mTargetAngles.vz == 0) ||
					     (mTargetAngles.vx == 0 && mTargetAngles.vz == 0x800)))
						mTargetAngles.vz = (Rnd(2) << 11) - 1024;
				}

				if (mNumBounces == 1 && Speed < 18) {
					mTargetAngles.vy = mAngles.vy + Rnd(1024) - 512;
					mTargetAngles.vx = (mAngles.vx + 512) & 0xc00;
					mTargetAngles.vz = (mAngles.vz + 512) & 0xc00;
				}
			}

			NewVel %= Fric;
			NewVel.KillSmall();

			if (mNumBounces >= 19) {
				mAngles.vx = mTargetAngles.vx;
				mAngles.vz = mTargetAngles.vz;
				FUN_8008b3d4(&mAngles, &m);

				NewVel.vz = 0;
				NewVel.vy = 0;
				NewVel.vx = 0;
				mDeathTimer = 10;
				mBaddyFlags &= ~0x20;
				return;
			}

			NewPos.vx = LInfo.Position.vx + Mips_FixMul(LInfo.Normal.vx, ObjectExtent);
			NewPos.vy = LInfo.Position.vy + Mips_FixMul(LInfo.Normal.vy, ObjectExtent);
			NewPos.vz = LInfo.Position.vz + Mips_FixMul(LInfo.Normal.vz, ObjectExtent);
		}
	}

	if (mNumBounces >= 19) {
		NewVel.vz = 0;
		NewVel.vy = 0;
		NewVel.vx = 0;
		mDeathTimer = 10;
		mAngles.vx = mTargetAngles.vx;
		mAngles.vz = mTargetAngles.vz;
		mBaddyFlags &= ~0x20;
	}
}
