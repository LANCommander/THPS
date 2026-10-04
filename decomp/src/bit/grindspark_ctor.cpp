/* __11CGrindSparkP5CBodyR7CVectoriii (0x80027650) */
/* C++ (BIT2.CPP). Fuzzy demo twin; members and locals from its MAIN.SYM, written as a real constructor.
   The negative-velocity path works on a temporary: assigning the parameter itself moves its prologue copy. */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct CVector { int vx, vy, vz; };
CVector operator+(const CVector &, const CVector &);
struct CFriction {
	uchar x, y, z;
	void Set(uchar a, uchar b, uchar c) { x = a; y = b; z = c; }
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
	virtual ~CBit();
};
class CGLine : public CBit {
public:
	uint mCodeBGR0;
	uint mPadBGR1;
	CVector mStart;
	CVector mEnd;
	CGLine();
};
class CGrindSpark : public CGLine {
public:
	CVector mOldPos;
	CBody *mpParent;
	CGrindSpark(CBody *pParent, CVector &pos, int vel, int gravity, int life);
	virtual ~CGrindSpark();
};

int Rnd(int);
void Bit_CalculateSparkVelocity(CVector &, int);

CGrindSpark::CGrindSpark(CBody *pParent, CVector &pos, int vel, int gravity, int life)
{
	{
		int vel2;
		if (vel < 0)
		{
			int t = -vel;
			{
				int r = Rnd(t);
				t >>= 1;
				t += r;
			}
			vel2 = -t;
		}
		else
		{
			vel2 = (vel >> 1) + Rnd(vel);
		}
		Bit_CalculateSparkVelocity(mVel, vel2);
		mAcc.vy = gravity;
		mFric.Set(3, 3, 3);
	}
	mLifetime = Rnd(life) + 1;
	mpParent = pParent;
	mOldPos = pos;
	mPos = pos;
	mEnd = pos + mpParent->mPos;
	mStart = mEnd;
	mCodeBGR0 = 0x52000080;
	{
		int r = ((Rnd(159) >> 5) + 2) << 12;
		mPadBGR1 = 0x55000000;
		mCodeBGR0 |= r;
	}
}
