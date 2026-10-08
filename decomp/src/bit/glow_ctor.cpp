/* __5CGlowRC7CVectoriiUcUcUcUcUcUc (0x80028d54) */
/* C++ (BIT.CPP). Fuzzy demo twin; members and locals from its MAIN.SYM. Written as a real constructor so
   `this` is copied where retail copies it. */
typedef unsigned char uchar;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

struct SSection {
	int Radius;
	uint CodeBGR;
};

struct SFringeQuad {
	int Radius;
	uint code;
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
	void AttachTo(void *);
};

class CGlow : public CBit {
  public:
	SSection *mpSections;
	SFringeQuad *mpFringes;
	uint mNumSections;
	uint mNumFringes;
	uint mCentreCodeBGR;
	short mStepAngle;
	uchar mSkipTriangles;
	short mAngle;
	uint mMask;
	CGlow(const CVector &Pos, int InnerRadius, int FringeRadius, uchar r0, uchar g0, uchar b0,
	      uchar r1, uchar g1, uchar b1);
	virtual ~CGlow();
};

void *Mem_New(uint, int, int);

char DAT_800d18e8[8];

CGlow::CGlow(const CVector &Pos, int InnerRadius, int FringeRadius, uchar r0, uchar g0, uchar b0,
             uchar r1, uchar g1, uchar b1) {
	uint PadBGR;

	mNumSections = 8;
	mStepAngle = 512;
	mNumFringes = 1;
	mpSections = (SSection *)Mem_New(128, 0, 1);
	mpFringes = (SFringeQuad *)(mpSections + mNumSections);
	AttachTo(DAT_800d18e8);

	mPos = Pos;

	{
		uint i;

		for (i = 0; i < mNumSections; i++)
			mpSections[i].Radius = InnerRadius;
	}

	PadBGR = ((b1 << 16) | (g1 << 8)) | r1;
	mCentreCodeBGR = 0x32000000 | (b0 << 16) | (g0 << 8) | r0;

	{
		uint i;

		for (i = 0; i < mNumSections; i++)
			mpSections[i].CodeBGR = PadBGR;
	}

	{
		uint i;

		for (i = 0; i < mNumSections; i++) {
			mpFringes[i].Radius = FringeRadius;
			mpFringes[i].code = 0x3a000000;
		}
	}

	mMask = 0xffffffff;
}
