/* __6CGLine (0x80027590) */
/* C++ (BIT2.CPP). Demo twin. */
#pragma interface

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

CVector operator+(const CVector &, const CVector &);

struct CFriction {
	uchar x, y, z;
	void Set(uchar a, uchar b, uchar c) {
		x = a;
		y = b;
		z = c;
	}
};

class CBody {
  public:
	ushort mFlags;
	ushort mInquiry;
	CVector mPos;
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
	CBit();
	virtual ~CBit();
	void AttachTo(void *);
};

class CGLine : public CBit {
  public:
	uint mCodeBGR0;
	uint mPadBGR1;
	CVector mStart;
	CVector mEnd;
	CGLine();
	virtual ~CGLine();
};

extern char GLineList[];

CGLine::CGLine() {
	mCodeBGR0 = 0x50808080;
	mPadBGR1 = 0x55808080;
	AttachTo(GLineList);
}
