/* __6CSparkR7CVectoriii (0x80029684) flags=-fstructure-noalias */
/* C++ (BIT.CPP). Fuzzy demo twin; members and the inlined CFriction block from its MAIN.SYM, written
   as a real constructor. A spark is a TILE (or a 1x1 TILE_1 when the global spark size is 1) coloured
   from the current spark colour, given a random-ish velocity, gravity and lifetime. Needs
   -fstructure-noalias: retail loads the globals above the vptr and mLifetime stores. */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct CVector { int vx, vy, vz; };
struct CFriction {
	uchar x, y, z;
	void Set(uchar a, uchar b, uchar c) { x = a; y = b; z = c; }
};

class CBit {
public:
	CBit *mPrevious;
	CBit *mNext;
	short mAge;
	ushort mLifetime;
	CVector mTweenPos;
	CVector mPos;
	CVector mVel;
	CVector mAcc;
	CFriction mFric;
	uchar mDead;
	ushort mFrigDeltaZ;
	uchar mProtected;
	uchar mType;
	virtual ~CBit();
};
class CPixel : public CBit {
public:
	uint tag;
	uchar r0, g0, b0, code;
	uint mWidthHeight;
	CPixel();
};
class CSpark : public CPixel {
public:
	uchar mFadeR;
	uchar mFadeG;
	uchar mFadeB;
	CSpark(CVector &pos, int vel, int gravity, int life);
	virtual ~CSpark();
};

uint DAT_800d18b4;
int DAT_800d18b8;
uchar DAT_800d18bc;
uchar DAT_800d18bd;
uchar DAT_800d18be;
uchar DAT_800d18c0;
uchar DAT_800d18c1;
uchar DAT_800d18c2;
short Redbook_Rnd(int);
void Bit_CalculateSparkVelocity(CVector &, int);

CSpark::CSpark(CVector &pos, int vel, int gravity, int life)
{
	if ((DAT_800d18b4 & 15) == 1) {
		code = 0x68;
		tag = 0x02000000;
		mWidthHeight = 1;
	} else {
		code = 0x60;
		mWidthHeight = DAT_800d18b4;
		tag = 0x03000000;
	}
	r0 = DAT_800d18bc;
	g0 = DAT_800d18bd;
	b0 = DAT_800d18be;
	mFadeR = DAT_800d18c0;
	mFadeG = DAT_800d18c1;
	mFadeB = DAT_800d18c2;
	mPos = pos;
	Bit_CalculateSparkVelocity(mVel, vel);
	mAcc.vy = gravity;
	mFric.Set(3, 3, 3);
	mLifetime = Redbook_Rnd(life);
	if (DAT_800d18b8)
		code |= 2;
}
