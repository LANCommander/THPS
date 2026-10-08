/* Shatter_Glass__FiRC7CVectorN31UcUcUc (0x80022004) */
/* C++ (SHATTER.CPP). Demo twin; locals from its MAIN.SYM. Breaks a pane (triangle p0/p1/p2) into n
   glass bits: finds the floor under the middle, scatters bits at random points of the triangle
   flying outward from the middle plus along the normal, and remembers the shatter point nearest
   the camera (for the sound). THPS1 drops the demo's bit-budget check. */
#pragma interface

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
	CVector() {}
	CVector(int x, int y, int z) {
		vx = x;
		vy = y;
		vz = z;
	}
	CVector &operator<<=(const int &);
};

struct Vector {
	int vx, vy, vz;
};

struct Item;

struct SLineInfo {
	Vector StartCoords; /* 0x00 */
	Vector EndCoords;   /* 0x0c */
	char pad18[0x68 - 0x18];
	Item *pItem;     /* 0x68 */
	Vector Position; /* 0x6c */
	char pad78[0xa4 - 0x78];
};

struct SCamera {
	int pad0;
	CVector Pos; /* 0x04 */
	char pad10[0xa4 - 0x10];
};

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
	void *operator new(uint) throw();
};

class CGlassBit : public CBit {
  public:
	char pad48[120 - 0x48];
	CGlassBit(const CVector &, const CVector &, int, uchar, uchar, uchar, int, int, int);
};

int ShatterSound;

extern int Camera_CurrentMikeCamera;
extern CVector ShatterSoundPos;
extern SCamera MikeCamera[];

void M3dColij_InitLineInfo(SLineInfo *);
extern "C" int M3dZone_LineToItemNotSCached__FP9SLineInfoi(SLineInfo *, int);
int Redbook_Rnd(int);
void Utils_CalcUnit(CVector &, const CVector &);
uint Utils_CrapDist(const CVector &, const CVector &);
CVector operator+(const CVector &, const CVector &);
CVector operator-(const CVector &, const CVector &);
CVector operator>>(const CVector &, const int &);
CVector operator<<(const CVector &, const int &);
CVector operator*(const CVector &, const int &);
CVector operator*(const int &, const CVector &);

void Shatter_Glass(int n, const CVector &p0, const CVector &p1, const CVector &p2,
                   const CVector &Normal, uchar r, uchar g, uchar b) {
	CVector middle = (p1 + p2) >> 1;
	SLineInfo ColInfo;
	int GroundY;

	ColInfo.StartCoords.vx = middle.vx + Normal.vx * 500;
	ColInfo.StartCoords.vy = middle.vy + Normal.vy * 500;
	ColInfo.StartCoords.vz = middle.vz + Normal.vz * 500;
	ColInfo.EndCoords.vx = ColInfo.StartCoords.vx;
	ColInfo.EndCoords.vy = ColInfo.StartCoords.vy + 0xbb8000;
	ColInfo.EndCoords.vz = ColInfo.StartCoords.vz;
	M3dColij_InitLineInfo(&ColInfo);
	M3dZone_LineToItemNotSCached__FP9SLineInfoi(&ColInfo, 1);

	GroundY = 0x7fffffff;

	if (ColInfo.pItem)
		GroundY = ColInfo.Position.vy;

	CVector u = (p2 - p0) >> 12;
	CVector v = (p1 - p0) >> 12;

	{
		int i;

		for (i = 0; i < n; i++) {
			int alpha = Redbook_Rnd(4096);
			int beta = Redbook_Rnd(4096);
			CVector p = (alpha * u + beta * v) >> 12;

			p = (p << 12) + p0;
			CVector a = p - middle;

			Utils_CalcUnit(a, a);

			a = a * Redbook_Rnd(40) + Normal * Redbook_Rnd(40);
			new CGlassBit(p, a, GroundY, r, g, b, 100, 100, 100);
		}
	}

	if (!ShatterSound) {
		ShatterSoundPos = middle;
		ShatterSound = 1;
	} else {
		CVector CamPos(MikeCamera[Camera_CurrentMikeCamera].Pos.vx, MikeCamera[Camera_CurrentMikeCamera].Pos.vy,
		               MikeCamera[Camera_CurrentMikeCamera].Pos.vz);

		CamPos <<= 12;

		if (Utils_CrapDist(CamPos, middle) < Utils_CrapDist(CamPos, ShatterSoundPos))
			ShatterSoundPos = middle;
	}
}
