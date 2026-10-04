/* __9CChunkBitRC8CSVectorN21 (0x8002876c) */
#pragma interface
typedef unsigned char uchar;
typedef unsigned int uint;
struct CVector { int vx, vy, vz; };
struct CSVector { short vx, vy, vz; };
typedef struct { int x, y, z; } __attribute__((aligned(8))) V;

class CBit {
public:
	CBit *mPrevious;
	CBit *mNext;
	short mAge;
	unsigned short mLifetime;
	CVector mTweenPos;
	CVector mPos;
	CVector mVel;
	CVector mAcc;
	uchar mFric[3];
	uchar mDead;
	unsigned short mFrigDeltaZ;
	uchar mProtected;
	uchar mType;
	CBit();
	virtual ~CBit();
	void AttachTo(void *);
};

class CChunkBit : public CBit {
public:
	CSVector mA; short p0;
	CSVector mB; short p1;
	CSVector mC; short p2;
	CSVector mD;
	CChunkBit(const CSVector &a, const CSVector &b, const CSVector &c);
};

int Redbook_Rnd(int);
void Utils_CalcUnit(CVector &, const CVector &);
char DAT_800d18e4[8];

static inline void VI(V *p, int x, int y, int z) { p->x = x; p->y = y; p->z = z; }

CChunkBit::CChunkBit(const CSVector &a, const CSVector &b, const CSVector &c)
{
	V ca, ba, cprod, norm;
	int mul;
	mType = 6;
	mA.vx = a.vx; mA.vy = a.vy; mA.vz = a.vz;
	mB.vx = b.vx; mB.vy = b.vy; mB.vz = b.vz;
	mC.vx = c.vx; mC.vy = c.vy; mC.vz = c.vz;
	VI(&ca, c.vx - a.vx, c.vy - a.vy, c.vz - a.vz);
	VI(&ba, b.vx - a.vx, b.vy - a.vy, b.vz - a.vz);
	cprod.x = ca.y * ba.z - ca.z * ba.y;
	cprod.y = ca.z * ba.x - ca.x * ba.z;
	cprod.z = ca.x * ba.y - ca.y * ba.x;
	Utils_CalcUnit(*(CVector*)&norm, *(CVector*)&cprod);
	mul = Redbook_Rnd(96) + 128;
	mD.vx = (norm.x * mul) >> 12;
	mD.vy = (norm.y * mul) >> 12;
	mD.vz = (norm.z * mul) >> 12;
	AttachTo(DAT_800d18e4);
}
