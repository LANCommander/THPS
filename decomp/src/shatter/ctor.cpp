/* __11CShatterBitRC8CSVectorN21RC7CVectori (0x80020b84) */
/* C++ (SHATTER.CPP). Demo twin; locals from its MAIN.SYM (two inlined CSVector setters, `this` in
   v1). A shattered-glass chunk: random spin about X or Y, a random lifetime, placed at pos, and
   half the time a smoke trail. THPS1 drops the demo's lifetime * 5 / 6. */
#pragma interface

typedef unsigned char uchar;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

struct CSVector {
	short vx, vy, vz;
	void Set(short x, short y, short z) {
		vx = x;
		vy = y;
		vz = z;
	}
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

class CChunkBit : public CBit {
  public:
	CSVector mA;
	short p0;
	CSVector mB;
	short p1;
	CSVector mC;
	short p2;
	CSVector mD;
	char pad66[0xc0 - 0x66];
	CChunkBit(const CSVector &a, const CSVector &b, const CSVector &c);
	void CalculateWorldCoords();
};

class CRibbon : public CBit {
  public:
	char pad48[100 - 0x48];
	void SetScale(int);
	void SetTint(uchar, uchar, uchar);
};

class CSmokeTrail : public CRibbon {
  public:
	CSmokeTrail(CVector &pos, int, int, int, int);
};

class CShatterBit : public CChunkBit {
  public:
	CSVector mAngVel;
	CSmokeTrail *mpSmokeTrail;
	CShatterBit(const CSVector &a, const CSVector &b, const CSVector &c, const CVector &pos,
	            int Smoke);
	virtual ~CShatterBit();
	void SetPos(const CVector &pos);
};

int Redbook_Rnd(int);

CShatterBit::CShatterBit(const CSVector &a, const CSVector &b, const CSVector &c,
                         const CVector &pos, int Smoke)
    : CChunkBit(a, b, c) {
	if (Redbook_Rnd(2))
		mAngVel.Set(Redbook_Rnd(160) + 80, 0, 0);
	else
		mAngVel.Set(0, Redbook_Rnd(160) + 80, 0);

	mLifetime = Redbook_Rnd(30) + 45;
	SetPos(pos);
	CalculateWorldCoords();

	if (Redbook_Rnd(2)) {
		mpSmokeTrail = new CSmokeTrail(mPos, 4, 128, 128, 128);
		mpSmokeTrail->mProtected = 1;
		mpSmokeTrail->SetScale(1200);
		mpSmokeTrail->SetTint(32, 32, 32);
	}
}
