/* __5CGlowUiUi (0x80028c48) */
/* C++ (BIT.CPP). Fuzzy demo twin; members and locals from its MAIN.SYM. Written as a real constructor so
   `this` is copied where retail copies it. */
typedef unsigned char uchar;
typedef unsigned int uint;
struct CVector { int vx, vy, vz; };
struct SSection { int a, b; };
struct SFringeQuad { uint a; uint code; };

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
	CGlow(uint NumPoints, uint NumFringes);
	virtual ~CGlow();
};

void *Mem_New(uint, int, int);
char DAT_800d18e8[8];

CGlow::CGlow(uint NumPoints, uint NumFringes)
{
	mNumSections = NumPoints * 2;
	mNumFringes = NumFringes;
	mStepAngle = 4096 / mNumSections;
	mpSections = (SSection *)Mem_New((mNumSections + mNumSections * mNumFringes) * sizeof(SSection), 0, 1);
	mpFringes = (SFringeQuad *)(mpSections + mNumSections);
	for (uint i = 0; i < mNumSections * mNumFringes; i++)
		mpFringes[i].code = 0x3a000000;
	mCentreCodeBGR = 0x32000000;
	mMask = 0xffffffff;
	AttachTo(DAT_800d18e8);
}
