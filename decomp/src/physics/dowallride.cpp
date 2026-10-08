/* DoWallRidePhysics__6CBruce (0x800376f4) */
/* C++ (PHYSICS.CPP). Demo twin, locals from its MAIN.SYM. Wall ride: moves the skater by the
   frame-scaled velocity and kick, turns along the fall line, sweeps the movement against the
   world (snapping to the wall and re-orienting if it was hit), then probes along -mUp for the
   wall: on it, the skater is stuck to it and gravity projected into its plane is added; off it,
   the skater drops back into the air.
   Levers: DAT_800d1774/1778 are plain `extern int` (one `la`/`lw` macro insn each, so the HIGH
   part isn't CSE'd into a saved reg); SetVector is a macro with block locals _x/_y/_z (as in the
   demo's MAIN.SYM blocks); `CheckDist` as a variable gives retail's `slt` with 116 in a register;
   the `Steep` int gives the slti/xori scc; the unused SquareRoot0 call goes through a void cast. */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

struct CVector {
	int vx, vy, vz;
	CVector &operator+=(const CVector &);
	int operator!=(const CVector &);
};

CVector operator*(const CVector &, const int &);
CVector operator>>(const CVector &, const int &);
CVector operator/(const CVector &, const int &);
CVector operator+(const CVector &, const CVector &);
CVector operator-(const CVector &, const CVector &);

#define SetVector(v, x, y, z)                                                                      \
	{                                                                                              \
		int _x = (x);                                                                              \
		int _y = (y);                                                                              \
		int _z = (z);                                                                              \
		(v)->vx = _x;                                                                              \
		(v)->vy = _y;                                                                              \
		(v)->vz = _z;                                                                              \
	}

struct SHandle {
	int a, b;
};

struct SItem {
	char pad0[0x1b];
	unsigned char Type; /* 0x1b */
};

struct SFace {
	char pad0[0xe];
	unsigned short Flags; /* 0xe */
};

struct SItemType {
	char pad0[0x14];
	void *p14; /* 0x14 */
	char pad18[0x40 - 0x18];
};

struct SLineInfo {
	CVector StartCoords;
	CVector EndCoords;
	CVector MinCoords;
	CVector MaxCoords;
	int iLo, iHi, jLo, jHi;
	int Distance; /* 0x40 */
	int Length;
	char pad48[0x68 - 0x48];
	SItem *pItem;     /* 0x68 */
	CVector HitPoint; /* 0x6c */
	SVECTOR Normal;   /* 0x78 */
	SFace *pFace;     /* 0x80 */
	char pad84[168 - 0x84];
};

class CBruce {
  public:
	char pad0[0x4];
	CVector mPos; /* 0x4 */
	char pad10[0x6c - 0x10];
	CVector mVel;  /* 0x6c */
	CVector mKick; /* 0x78 */
	char pad84[0xa8 - 0x84];
	SVECTOR mLastNormal; /* 0xa8 */
	char padb0[0xf0 - 0xb0];
	CVector mOldPos; /* 0xf0 */
	char padfc[0x144 - 0xfc];
	short mFrame;         /* 0x144 */
	unsigned short mAnim; /* 0x146 */
	char pad148[0x14f - 0x148];
	unsigned char m14F; /* 0x14f */
	int m150;           /* 0x150 */
	char pad154[0x304 - 0x154];
	int m304; /* 0x304 */
	char pad308[0x324 - 0x308];
	int m324; /* 0x324 */
	int m328; /* 0x328 */
	int m32C; /* 0x32c */
	char pad330[0x334 - 0x330];
	int mMaxSpeed; /* 0x334 */
	char pad338[0x358 - 0x338];
	int mInAir; /* 0x358 */
	int m35C;   /* 0x35c */
	char pad360[0x418 - 0x360];
	SItem *mpWallItem;   /* 0x418 */
	SHandle mWallHandle; /* 0x41c */
	char pad424[0x720 - 0x424];
	int m720; /* 0x720 */
	char pad724[0x734 - 0x724];
	int m734; /* 0x734 */
	char pad738[0x73c - 0x738];
	int m73C; /* 0x73c */
	int m740; /* 0x740 */
	char pad744[0x768 - 0x744];
	int m768; /* 0x768 */
	char pad76c[0x7d8 - 0x76c];
	CVector mFront;      /* 0x7d8 */
	CVector mRight;      /* 0x7e4 */
	CVector mUp;         /* 0x7f0 */
	CVector mFallLine;   /* 0x7fc */
	int mFallLineTurn;   /* 0x808 */
	SVECTOR mPolyNormal; /* 0x80c */
	char pad814[0x820 - 0x814];
	int m820;     /* 0x820 */
	CVector m824; /* 0x824 */
	void StateTransition(int, int);
	void OrientToNormal();
	void FRUVectorsFromRotMatrix();
	void RotMatrixFromFRUVectors();
	void AlignToFallLine(int);
	void RotateHeadingAndVelocity(int, int, int);
	void DoWallRidePhysics();
};

extern int DAT_800d1774;
extern int DAT_800d1778;
extern CVector DAT_800a824c;
extern SItemType DAT_800bf7a8[];

int DAT_800d1974;
int DAT_800d1978;
int DAT_800d1980;

short PingPong(int, int, int);
void ProjectCVectorToPlane(CVector *, SVECTOR);
void M3dUtils_NormaliseVector(CVector *);
void CVectorRotateToPlane(CVector *, SVECTOR *, CVector *);
void M3dColij_InitLineInfo(SLineInfo *);
int GetFaceFlags(SLineInfo *);

extern "C" {
	int Mips_CVecDotProd__FP7CVectorT0(void *, void *);
	int FUN_8008b5dc(int);
	int Mips_FixMul__Fii(int, int);
	int M3dZone_LineToItemNotSCached__FP9SLineInfoi(SLineInfo *, int);
	SHandle FUN_8004d7ac(void *);
	void FUN_8002f1a0(CBruce *);
	void Debug_RunAnim__6CBruceii(CBruce *, int, int);
	void ReflectHeadingVelocityInPlane__6CBruceG7SVECTORi(CBruce *, SVECTOR, int);
	void SFX_Grunt__FP6CBruce(CBruce *);
}

void CBruce::DoWallRidePhysics() {
	CVector u0, u1, u2; /* unused: retail's frame keeps their slots */
	CVector vMovement;
	CVector InplaneGravity;
	CVector u3, u4, u5; /* unused, likewise */
	SVECTOR u6;
	int Speed;
	int TurnAngle;
	SLineInfo line_info;
	int OnInvisible;
	CVector Gravity;

	Gravity.vx = 0;
	Gravity.vy = 9000;
	Gravity.vz = 0;
	OnInvisible = m734 == 2;

	if (m14F) {
		if (mAnim == 36)
			mFrame = PingPong(7, 9, 15);
		else if (mAnim == 35)
			mFrame = PingPong(7, 9, 15);
	}

	mPos += ((mVel * DAT_800d1774) >> 8) + ((mKick * DAT_800d1778) >> 8) / 2;
	vMovement = mPos - mOldPos;
	/* result unused; called as void so v0 isn't reserved (retail's register choice) */
	((void (*)(int))FUN_8008b5dc)(Mips_CVecDotProd__FP7CVectorT0(&vMovement, &vMovement));
	TurnAngle = 0;

	if (!m720 && !m324) {
		AlignToFallLine(4);

		TurnAngle = mFallLineTurn;
	}

	Mips_FixMul__Fii(TurnAngle, 3072);
	RotateHeadingAndVelocity((TurnAngle * DAT_800d1774) >> 8, !OnInvisible, 0);

	SetVector(&line_info.StartCoords, mOldPos.vx, mOldPos.vy, mOldPos.vz)
	    SetVector(&line_info.EndCoords, mPos.vx, mPos.vy, mPos.vz) vMovement = mPos - mOldPos;

	if (vMovement != DAT_800a824c) {
		Speed = FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(&vMovement, &vMovement)) << 6;

		if (mInAir ? Speed < 0x64000 : Speed < 0x1e000) {
			if (Speed < 2048)
				Speed = 2048;

			line_info.EndCoords.vx =
			    mOldPos.vx + ((vMovement.vx * (mInAir ? 100 : 30) / Speed) << 12);
			line_info.EndCoords.vy =
			    mOldPos.vy + ((vMovement.vy * (mInAir ? 100 : 30) / Speed) << 12);
			line_info.EndCoords.vz =
			    mOldPos.vz + ((vMovement.vz * (mInAir ? 100 : 30) / Speed) << 12);
		}

		M3dColij_InitLineInfo(&line_info);
		M3dZone_LineToItemNotSCached__FP9SLineInfoi(&line_info, 1);
		GetFaceFlags(&line_info);

		if (line_info.pItem) {
			if (DAT_800d1980 || !DAT_800d1974) {
				mPos.vx = line_info.HitPoint.vx + mUp.vx * 30;
				mPos.vy = line_info.HitPoint.vy + mUp.vy * 30;
				mPos.vz = line_info.HitPoint.vz + mUp.vz * 30;

				if (!OnInvisible) {
					mpWallItem = line_info.pItem;
					mWallHandle = FUN_8004d7ac(DAT_800bf7a8[line_info.pItem->Type].p14);
				}

				if (*(int *)&line_info.Normal == *(int *)&mLastNormal &&
				    line_info.Normal.vz == mLastNormal.vz) {
					m820++;
				} else {
					m820 = 0;
					SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
					          line_info.Normal.vz)
				}

				OrientToNormal();

				if (DAT_800d1978) {
					StateTransition(0, 5840);
					ProjectCVectorToPlane(&mFront, line_info.Normal);
					M3dUtils_NormaliseVector(&mFront);
					SetVector(&mUp, line_info.Normal.vx, line_info.Normal.vy, line_info.Normal.vz)
					    gte_ldopv1(&mFront);
					gte_ldopv2(&mUp);
					gte_op12();
					gte_stlvnl(&mRight);
					RotMatrixFromFRUVectors();

					m820 = 0;
					SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
					          line_info.Normal.vz)
					    SetVector(&m824, line_info.Normal.vx, line_info.Normal.vy,
						          line_info.Normal.vz)
					        ProjectCVectorToPlane(&mVel, line_info.Normal);
				}
			}
		}
	}

	if (mMaxSpeed < FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(&mVel, &mVel)) << 6)
		m304 = 1;
	else
		m304 = 0;

	FRUVectorsFromRotMatrix();

	line_info.StartCoords.vx = mPos.vx + mUp.vx * 70;
	line_info.StartCoords.vy = mPos.vy + mUp.vy * 70;
	line_info.StartCoords.vz = mPos.vz + mUp.vz * 70;
	line_info.EndCoords.vx = line_info.StartCoords.vx - mUp.vx * 128;
	line_info.EndCoords.vy = line_info.StartCoords.vy - mUp.vy * 128;
	line_info.EndCoords.vz = line_info.StartCoords.vz - mUp.vz * 128;
	M3dColij_InitLineInfo(&line_info);
	M3dZone_LineToItemNotSCached__FP9SLineInfoi(&line_info, 1);
	GetFaceFlags(&line_info);

	if (line_info.pItem) {
		int d = line_info.Distance;
		int CheckDist = 116;

		if (d <= CheckDist) {
			m768 = line_info.pFace->Flags & 0x20;
			mPos.vx = line_info.HitPoint.vx + mUp.vx * 30;
			mPos.vy = line_info.HitPoint.vy + mUp.vy * 30;
			mPos.vz = line_info.HitPoint.vz + mUp.vz * 30;

			if (!OnInvisible) {
				mpWallItem = line_info.pItem;
				mWallHandle = FUN_8004d7ac(DAT_800bf7a8[line_info.pItem->Type].p14);
			}

			if (*(int *)&line_info.Normal == *(int *)&mLastNormal &&
			    line_info.Normal.vz == mLastNormal.vz) {
				m820++;
			} else {
				m820 = 0;
				SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
				          line_info.Normal.vz)
			}

			OrientToNormal();

			if (DAT_800d1978) {
				StateTransition(0, 5949);
				ProjectCVectorToPlane(&mFront, line_info.Normal);
				M3dUtils_NormaliseVector(&mFront);
				SetVector(&mUp, line_info.Normal.vx, line_info.Normal.vy, line_info.Normal.vz)
				    gte_ldopv1(&mFront);
				gte_ldopv2(&mUp);
				gte_op12();
				gte_stlvnl(&mRight);
				RotMatrixFromFRUVectors();

				m820 = 0;
				SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
				          line_info.Normal.vz)
				    SetVector(&m824, line_info.Normal.vx, line_info.Normal.vy, line_info.Normal.vz)
				        ProjectCVectorToPlane(&mVel, line_info.Normal);
			} else {
				int Steep = line_info.Normal.vy >= 3278;

				if (Steep) {
					mPos = mOldPos;
					StateTransition(1, 5987);

					m740 = 1;
					mKick += Gravity;
					ReflectHeadingVelocityInPlane__6CBruceG7SVECTORi(this, line_info.Normal, 200);
					SFX_Grunt__FP6CBruce(this);
				}
			}
		}

		InplaneGravity = Gravity;
		ProjectCVectorToPlane(&InplaneGravity, line_info.Normal);

		mKick += InplaneGravity;
		mFallLine = InplaneGravity;
		mPolyNormal = line_info.Normal;
		CVectorRotateToPlane(&mVel, &line_info.Normal, &mVel);
	} else {
		StateTransition(1, 6040);
		FUN_8002f1a0(this);

		m328 = 0;
		m32C = 0;
		m35C = 0;
		m740 = 1;

		if (!mInAir) {
			m150 = 0x10000;

			if (m73C)
				Debug_RunAnim__6CBruceii(this, 26, 6071);
			else
				Debug_RunAnim__6CBruceii(this, 27, 6073);
		}

		mKick += Gravity;
	}
}
