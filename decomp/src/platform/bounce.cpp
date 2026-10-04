/* Bounce__9CPlatformP6CBruceRC7CVector (0x8003d820) */
/* C++ (PLATFORM.CPP). Locals from the demo's MAIN.SYM. THPS1's CPlatform fields sit 8 bytes past
   the demo's; the CBaddy/CBody part is laid out by offset. */
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
	void Set(int a, int b, int c) { vx = a; vy = b; vz = c; }
	int Length() const;
};
struct CSVector { short vx, vy, vz; };

class CBruce {
public:
	void Vibrate(int, int, int);
};

class CPlatform {
public:
	ushort mFlags;              /* 0x000 */
	ushort mInquiry;
	CVector mPos;
	CSVector mAngles;           /* 0x010 */
	char pad16[0x6c - 0x16];
	CVector mVel;               /* 0x06c */
	char pad78[0x1ac - 0x78];
	uint mBaddyFlags;           /* 0x1ac */
	char pad1b0[0x22a - 0x1b0];
	ushort mNumBounces;         /* 0x22a */
	ushort mType;               /* 0x22c */
	ushort mWidth;
	ushort mHeight;
	ushort mDepth;
	ushort mDeathTimer;
	CSVector mTargetAngles;     /* 0x236 */
	void Bounce(CBruce *pSkater, const CVector &Direction);
};

int Rnd(int);
void SFX_PlayX(unsigned int, short, int);
void SFX_Grunt(CBruce *);
extern int DAT_800d1e28;
#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

void CPlatform::Bounce(CBruce *pSkater, const CVector &Direction)
{
	int Height;
	int Speed;
	CVector Dir;

	if (mBaddyFlags & 0x10)
	if (!(mBaddyFlags & 0x20))
	{
		Dir = Direction;
		Dir.vy = 0;
		Speed = Dir.Length();
		mBaddyFlags |= 0x20;
		mNumBounces = 0;
		mFlags |= 0x20;
		mTargetAngles.vy = Rnd(4096);
		mTargetAngles.vx = mAngles.vx - 1024 + (Rnd(2) << 11);
		mTargetAngles.vz = mAngles.vz - 1024 + (Rnd(2) << 11);

		switch (mType)
		{
		case 1:
			SFX_PlayX(104, 0x2000, 0);
			goto Bouncy;
		case 3:
			SFX_PlayX(40, 0x2000, 0);
		Bouncy:
			SFX_Grunt(pSkater);
			pSkater->Vibrate(6, 1, 120);
			Height = -0x40000;
			if (Speed < 40)
				Height = -0x20000;
			if (Speed < 18)
			{
				mTargetAngles.vy = mAngles.vy + Rnd(1024) - 512;
				mTargetAngles.vx = (mAngles.vx + 512) & 0xc00;
				mTargetAngles.vz = (mAngles.vz + 512) & 0xc00;
			}
			mVel.Set(Direction.vx, Height, Direction.vz);
			break;
		case 2:
		case 4:
		case 5:
			if (mType == 2)
				SFX_PlayX(DAT_800d1e28 ? 106 : Rnd(2) + 83, 0x2000, 0);
			else if (mType == 4)
			{
				SFX_Grunt(pSkater);
				SFX_PlayX(82, 0x2000, 0);
			}
			pSkater->Vibrate(2, 1, 180);
			mVel.Set(Direction.vx + (Direction.vx >> 1), -0x50000, Direction.vz + (Direction.vz >> 1));
			if (ABS(mTargetAngles.vx) == 0x800 && mTargetAngles.vz == 0)
				mTargetAngles.vz = mAngles.vz;
			if (mTargetAngles.vx == 0 && ABS(mTargetAngles.vz) == 0x800)
				mTargetAngles.vx = mAngles.vx;
			break;
		default:
			mVel.Set(Direction.vx, -0x40000, Direction.vz);
			break;
		}
	}
}
