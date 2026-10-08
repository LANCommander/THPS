/* AlignToFallLine__6CBrucei (0x8003a214) */
/* C++ (PHYSICS.CPP). Fuzzy demo twin (0.72; retail is a trimmed version), locals from its
   MAIN.SYM. When the skater is moving across a slope, turns them towards the fall line: the turn
   rate grows with the slope's steepness and shrinks with speed. It's held at 0 while the skater
   faces within a dead zone either side of the fall line's perpendicular. */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

struct CVector {
	int vx, vy, vz;
};

class CBruce {
  public:
	char pad0[0x6c];
	CVector mVel; /* 0x6c */
	char pad78[0x308 - 0x78];
	int mFallLineSide;  /* 0x308 */
	int mFallLineFrame; /* 0x30c */
	char pad310[0x334 - 0x310];
	int mMaxSpeed; /* 0x334 */
	char pad338[0x358 - 0x338];
	int mInAir; /* 0x358 */
	char pad35c[0x7d8 - 0x35c];
	CVector mFront; /* 0x7d8 */
	char pad7e4[0x7fc - 0x7e4];
	CVector mFallLine;   /* 0x7fc */
	int mFallLineTurn;   /* 0x808 */
	SVECTOR mPolyNormal; /* 0x80c */
	void AlignToFallLine(int Amount);
};

extern int XFrames;

void M3dUtils_NormaliseVector(CVector *);
void ProjectCVectorToPlane(CVector *, SVECTOR);
extern "C" int Mips_CVecDotProd__FP7CVectorT0(void *, void *);

void CBruce::AlignToFallLine(int Amount) {
	int Speed;
	int dot;
	int PolyTilt;
	int angle;
	CVector FallLinePerp;
	CVector FallLineUnit;
	VECTOR mLPN;
	CVector FrontInPlane;

	mFallLineTurn = 0;

	if (mInAir)
		return;

	Speed = SquareRoot0(Mips_CVecDotProd__FP7CVectorT0(&mVel, &mVel)) << 6;
	PolyTilt = SquareRoot0(Mips_CVecDotProd__FP7CVectorT0(&mFallLine, &mFallLine)) << 6;
	angle = PolyTilt / 260;
	angle = angle * PolyTilt / 13000;

	if (mMaxSpeed < Speed)
		Speed = mMaxSpeed;

	angle = angle * ((Amount << 12) + mMaxSpeed - Speed) / mMaxSpeed;

	if (!angle)
		return;

	if (mFallLineFrame + 10 < XFrames)
		mFallLineSide = 0;

	mFallLineFrame = XFrames;
	FallLineUnit = mFallLine;
	M3dUtils_NormaliseVector(&FallLineUnit);

	mLPN.vx = mPolyNormal.vx;
	mLPN.vy = mPolyNormal.vy;
	mLPN.vz = mPolyNormal.vz;
	gte_ldopv1(&mLPN);
	gte_ldopv2(&FallLineUnit);
	gte_op12();
	gte_stlvnl(&FallLinePerp);

	FrontInPlane = mFront;
	ProjectCVectorToPlane(&FrontInPlane, mPolyNormal);

	dot = Mips_CVecDotProd__FP7CVectorT0(&FrontInPlane, &FallLineUnit);
	dot = Mips_CVecDotProd__FP7CVectorT0(&mFront, &FallLinePerp);

	if (dot >= 42) {
		if (mFallLineSide != 2) {
			mFallLineTurn = -angle;
			mFallLineSide = 1;
		}
	} else if (dot < -41) {
		if (mFallLineSide != 1) {
			mFallLineTurn = angle;
			mFallLineSide = 2;
		}
	} else {
		mFallLineSide = 0;
	}
}
