/* HandleBailPerpendicular__6CBruceG7SVECTOR (0x80031224) */
/* C++ (PHYSICS.CPP). Fuzzy demo twin (0.83; retail is trimmed), locals from its MAIN.SYM. When the
   skater runs into a wall (Normal) fast and nearly head-on, flips them, faces them back along
   their last movement, rebuilds the orientation against the wall normal and, if they were
   facing away, starts the perpendicular bail. */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

struct CVector {
	int vx, vy, vz;
};

CVector operator-(const CVector &, const CVector &);

static inline void SetVector(VECTOR *v, int _x, int _y, int _z) {
	v->vx = _x;
	v->vy = _y;
	v->vz = _z;
}

class CBruce {
  public:
	char pad0[0x6c];
	CVector mVel; /* 0x6c */
	char pad78[0xf0 - 0x78];
	CVector mOldPos; /* 0xf0 */
	char padfc[0x134 - 0xfc];
	int mFlags; /* 0x134 */
	char pad138[0x150 - 0x138];
	int m150; /* 0x150 */
	char pad154[0x1b0 - 0x154];
	CVector m1B0; /* 0x1b0 */
	char pad1bc[0x21c - 0x1bc];
	int mBails; /* 0x21c */
	char pad220[0x24c - 0x220];
	int m24C; /* 0x24c */
	char pad250[0x7d8 - 0x250];
	CVector mFront; /* 0x7d8 */
	CVector mRight; /* 0x7e4 */
	CVector mUp;    /* 0x7f0 */
	void Flip();
	void RotMatrixFromFRUVectors();
	void HandleBailPerpendicular(SVECTOR Normal);
};

void ProjectCVectorToPlane(CVector *, SVECTOR);

extern "C" {
	int Mips_CVecDotProd__FP7CVectorT0(void *, void *);
	void Bail__6CBrucei13ELimitBailVel(CBruce *, int);
	int FUN_800934e4(VECTOR *, VECTOR *);
	void Debug_RunAnim__6CBruceii(CBruce *, int, int);
}

void CBruce::HandleBailPerpendicular(SVECTOR Normal) {
	CVector InplaneVel;
	int Speed;
	int Dot;

	InplaneVel = mVel;
	ProjectCVectorToPlane(&InplaneVel, Normal);

	Speed = SquareRoot0(Mips_CVecDotProd__FP7CVectorT0(&InplaneVel, &InplaneVel)) << 6;

	if (Speed <= 0x1e000)
		return;

	Dot = (Mips_CVecDotProd__FP7CVectorT0(&InplaneVel, &mFront) << 6) / (Speed >> 6);

	if (ABS(Dot) >= 1638)
		return;

	Flip();

	{
		int RightDot = Mips_CVecDotProd__FP7CVectorT0(&InplaneVel, &mRight);

		Bail__6CBrucei13ELimitBailVel(this, 0);

		mBails++;

		{
			VECTOR v;
			CVector vv;

			vv = mOldPos - m1B0;
			SetVector(&v, vv.vx, vv.vy, vv.vz);

			if (ABS(v.vx) + ABS(v.vy) + ABS(v.vz) > 0x8000)
				SetVector(&v, v.vx >> 4, v.vy >> 4, v.vz >> 4);

			FUN_800934e4(&v, &v);

			mFront.vx = -v.vx;
			mFront.vy = -v.vy;
			mFront.vz = -v.vz;
			mUp.vx = Normal.vx;
			mUp.vy = Normal.vy;
			mUp.vz = Normal.vz;
			gte_ldopv1(&mFront);
			gte_ldopv2(&mUp);
			gte_op12();
			gte_stlvnl(&mRight);
			gte_ldopv1(&mUp);
			gte_ldopv2(&mRight);
			gte_op12();
			gte_stlvnl(&mFront);
			RotMatrixFromFRUVectors();
		}

		if (mFlags & 2)
			RightDot = -RightDot;

		if (RightDot <= 0) {
			m150 = 0x10000;
			Debug_RunAnim__6CBruceii(this, 46, 1997);

			m24C = 5;
		}
	}
}
