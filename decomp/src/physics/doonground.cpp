/* DoOnGroundPhysics__6CBruce (0x800347a8) size=5664 flags=-fstructure-noalias */
/* C++ (PHYSICS.CPP). Demo twin, locals from its MAIN.SYM. One function: functions.tsv splits it into
   FUN_800347a8 (3092) + FUN_800353bc (4) + FUN_800353c0 (2568) at the OrientToNormal call, but
   the only prologue/epilogue pair spans all 5664 bytes and nothing calls 0x800353c0.
   On the ground: terrain sparks and pad rumble (rails/metal/etc. by m72C), moves the skater by the
   frame-scaled velocity and kick, turns along the fall line, sweeps the movement against the world
   (bouncing off walls, stepping up kerbs, sliding along), pushes out of side walls, then probes
   down along -mUp for the floor: on it, snaps to it, handles the bail / grind / wallride hand-offs
   and adds gravity projected into the floor plane; off it, skates off the ground. Finally the side
   velocity is removed and the forwards velocity damped (auto-kick, top speed, terrain drag).
   Levers: the mPos update is wrapped in do{}while(0) (its refs count double, so &mKick wins fp
   over OnInvisible, which is spilled as in retail); CVector Old is declared mid-function at
   function scope, after the early temps, so it takes sp+344 and later block locals sit above it;
   -Normal.vy > ABS(Normal.vx) loads vy first; the rumble switch lists the empty cases 0,1,2,4
   (jump table from 0); CSpark is 92 bytes (one more int than the ctor TU declares).
   Residue (3 words): &mOldPos gets s1 where retail has s2. */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

struct CVector {
	int vx, vy, vz;
	void Set(int x, int y, int z) {
		vx = x;
		vy = y;
		vz = z;
	}
	CVector &operator+=(const CVector &);
	CVector &operator-=(const CVector &);
	int operator!=(const CVector &);
	int Length() const;
};

struct CSVector {
	short vx, vy, vz;
	void Set(short x, short y, short z) {
		vx = x;
		vy = y;
		vz = z;
	}
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

struct CFriction {
	unsigned char x, y, z;
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
	CFriction mFric;
	unsigned char mDead;
	unsigned short mFrigDeltaZ;
	unsigned char mProtected;
	unsigned char mType;
	virtual ~CBit();
	void *operator new(unsigned int) throw();
};

class CPixel : public CBit {
  public:
	unsigned int tag;
	unsigned char r0, g0, b0, code;
	unsigned int mWidthHeight;
};

class CSpark : public CPixel {
  public:
	unsigned char mFadeR, mFadeG, mFadeB;
	int m58;
	CSpark(CVector &pos, int vel, int gravity, int life);
	virtual ~CSpark();
};

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

struct SColl {
	char pad0[0x10];
	unsigned char x10; /* 0x10 */
	char pad11[0x20 - 0x11];
	unsigned char x20; /* 0x20 */
};

struct SPadOptions {
	char pad0[0x940];
	int AutoKick[2]; /* 0x940 */
};

class CBruce {
  public:
	char pad0[0x4];
	CVector mPos;     /* 0x4 */
	CSVector mAngles; /* 0x10 */
	char pad16[0x6c - 0x16];
	CVector mVel;  /* 0x6c */
	CVector mKick; /* 0x78 */
	char pad84[0xa8 - 0x84];
	SVECTOR mLastNormal; /* 0xa8 */
	char padb0[0xf0 - 0xb0];
	CVector mOldPos; /* 0xf0 */
	char padfc[0x146 - 0xfc];
	unsigned short mAnim; /* 0x146 */
	char pad148[0x150 - 0x148];
	int m150; /* 0x150 */
	char pad154[0x1c8 - 0x154];
	CVector mGravity; /* 0x1c8 */
	char pad1d4[0x1f8 - 0x1d4];
	int m1F8; /* 0x1f8 */
	int m1FC; /* 0x1fc */
	char pad200[0x214 - 0x200];
	int m214; /* 0x214 */
	char pad218[0x284 - 0x218];
	int m284; /* 0x284 */
	int m288; /* 0x288 */
	char pad28c[0x304 - 0x28c];
	int m304; /* 0x304 */
	char pad308[0x324 - 0x308];
	int m324; /* 0x324 */
	int m328; /* 0x328 */
	int m32C; /* 0x32c */
	char pad330[0x334 - 0x330];
	int mMaxSpeed; /* 0x334 */
	char pad338[0x358 - 0x338];
	int mInAir; /* 0x358 */
	char pad35c[0x368 - 0x35c];
	int m368; /* 0x368 */
	char pad36c[0x418 - 0x36c];
	SItem *mpWallItem;   /* 0x418 */
	SHandle mWallHandle; /* 0x41c */
	char pad424[0x720 - 0x424];
	int m720; /* 0x720 */
	int m724; /* 0x724 */
	char pad728[0x72c - 0x728];
	int m72C; /* 0x72c */
	char pad730[0x734 - 0x730];
	int m734; /* 0x734 */
	char pad738[0x740 - 0x738];
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
	CVector m814;        /* 0x814 */
	int m820;            /* 0x820 */
	CVector m824;        /* 0x824 */
	char pad830[0x838 - 0x830];
	int m838; /* 0x838 */
	char pad83c[0x86c - 0x83c];
	SColl *mpColl; /* 0x86c */
	int mPad;      /* 0x870 */
	void StateTransition(int, int);
	void OrientToNormal();
	void FRUVectorsFromRotMatrix();
	void RotMatrixFromFRUVectors();
	void SetAnglesFromHeading();
	void AlignToFallLine(int);
	void RotateHeadingAndVelocity(int, int, int);
	void Vibrate(int, int, int);
	void HandleBailPerpendicular(SVECTOR);
	void DoOnGroundPhysics();
};

extern int DAT_800d16a4;
extern int DAT_800d179c;
extern SPadOptions DAT_800a6844;
extern int DAT_800d1868;
extern int DAT_800d186c;
extern int DAT_800d1770;
extern int DAT_800d1774;
extern int DAT_800d1778;
extern CVector DAT_800a824c;
extern SItemType DAT_800bf7a8[];

int DAT_800d1974;
int DAT_800d1978;
int DAT_800d197c;
int DAT_800d1980;
int DAT_800d1984;

void Platform_HandleBounce();
void Bit_SetSparkTrajectory(const CSVector &);
void ProjectCVectorToPlane(CVector *, SVECTOR);
void M3dUtils_NormaliseVector(CVector *);
void CVectorRotateToPlane(CVector *, SVECTOR *, CVector *);
void M3dColij_InitLineInfo(SLineInfo *);
int GetFaceFlags(SLineInfo *);

extern "C" {
	int Mips_CVecDotProd__FP7CVectorT0(void *, void *);
	int FUN_8008b5dc(int);
	int Mips_FixMul__Fii(int, int);
	int FUN_800827d4(SLineInfo *, int);
	SHandle FUN_8004d7ac(void *);
	void FUN_8002952c(CSVector *);
	void FUN_80029648(int);
	void FUN_8002965c(int, int, int);
	void FUN_80029670(int, int, int);
	int FUN_8004d878(int);
	void FUN_800429d0(CBruce *);
	int FUN_800343f0(CBruce *, int);
	void FUN_8003434c(CBruce *);
	void FUN_8002f1a0(CBruce *);
	void FUN_8002fcdc(CBruce *, int, int);
	void FUN_80039f2c(CBruce *, SVECTOR, int);
	void FUN_80043408(CBruce *);
}

void CBruce::DoOnGroundPhysics() {
	CVector u0, u1, u2; /* unused: retail's frame keeps their slots */
	CVector vMovement;
	CVector InplaneGravity;
	CVector u3, u4, u5;
	SVECTOR u6;
	int Speed;
	int TurnAngle;
	SLineInfo line_info;
	int OnInvisible;
	int AutoKickEnabled;
	CVector Gravity;

	OnInvisible = m734 == 2;

	if (DAT_800d16a4 != 7)
		AutoKickEnabled = DAT_800a6844.AutoKick[mPad];
	else
		AutoKickEnabled = DAT_800a6844.AutoKick[mPad ^ DAT_800d179c];

	Gravity.vx = 0;
	Gravity.vy = 6500;
	Gravity.vz = 0;

	if (!m734)
		m724 = 0;

	Speed = FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(&mVel, &mVel)) << 6;

	if ((m72C == 5 || m72C == 6 || m72C == 3) && DAT_800d1868 < 200) {
		SetAnglesFromHeading();
		Bit_SetSparkTrajectory(mAngles);
		CSVector Cone;

		Cone.Set(512, 4096, 0);
		FUN_8002952c(&Cone);
		FUN_80029648(1);

		if (Speed > 0x10000) {
			int i;

			switch (m72C) {
				case 5:
					FUN_8002965c(2, 160, 32);
					break;
				case 6:
					FUN_8002965c(160, 160, 160);
					break;
				case 3:
					FUN_8002965c(128, 64, 32);
					break;
			}

			FUN_80029670(0, 0, 0);

			DAT_800d186c = 0;

			for (i = 0; i < 6; i++) {
				if (FUN_8004d878(1) > 10000) {
					CSpark *p = new CSpark(mPos, 20, Speed >> 16, 20);

					p->mVel += mVel;
				}
			}

			DAT_800d186c = 1;
		}
	}

	if (Speed > 0x10000) {
		Speed >>= 12;

		if (Speed > 64)
			Speed = 64;

		switch (m72C) {
			case 0:
			case 1:
			case 2:
			case 4:
				break;
			case 5:
				Vibrate(8, 1, 9600 / Speed);
				break;
			case 6:
				Vibrate(8, 1, 4480 / Speed);
				break;
			case 3:
				Vibrate(8, 1, 16320 / Speed);
				break;
		}
	}

	do {
		mPos += ((mVel * DAT_800d1774) >> 8) + ((mKick * DAT_800d1778) >> 8) / 2;
	} while (0);

	Platform_HandleBounce();

	if (!OnInvisible && !mInAir)
		FUN_800429d0(this);

	vMovement = mPos - mOldPos;
	((void (*)(int))FUN_8008b5dc)(Mips_CVecDotProd__FP7CVectorT0(&vMovement, &vMovement));
	TurnAngle = m838 >> 12;
	mFallLineTurn = 0;

	if (!m720 && !m324 && m1FC && !m284) {
		if (!TurnAngle) {
			AlignToFallLine(40);
		} else if (mpColl->x10 || mpColl->x20) {
			m1FC = m1FC - 1;
		} else {
			m1FC = m1FC - 3;

			if (m1FC < 0)
				m1FC = 0;
		}

		TurnAngle += mFallLineTurn;
	} else {
		m1FC = 0;
	}

	Mips_FixMul__Fii(TurnAngle, 3072);
	RotateHeadingAndVelocity((TurnAngle * DAT_800d1774) >> 8, !OnInvisible, 0);

	m328 += (TurnAngle * DAT_800d1774) >> 8;

	if (m328 >= 2048) {
		m328 -= 2048;

		if (!m288)
			m32C++;
	}

	if (m328 <= -2048) {
		m328 += 2048;

		if (!m288)
			m32C++;
	}

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
		FUN_800827d4(&line_info, 1);
		GetFaceFlags(&line_info);

		if (line_info.pItem) {
			if (!DAT_800d1978 && !DAT_800d197c && !DAT_800d1974) {
				int TurnAway;

				mPos = mOldPos;
				TurnAway = 0;

				if (mAnim != 12 && !mInAir && !m368) {
					CVector WallFloorNormal;

					SetVector(&WallFloorNormal, line_info.Normal.vx, line_info.Normal.vy,
					          line_info.Normal.vz) if (Mips_CVecDotProd__FP7CVectorT0(&WallFloorNormal, &mFront) >
					                                   2896) {
						m150 = 0x10000;
						FUN_8002fcdc(this, 12, 4120);

						TurnAway = 200;
						FUN_80043408(this);
					}
				}

				FUN_80039f2c(this, line_info.Normal, TurnAway);
			} else if (line_info.pItem) {
				if (!DAT_800d1974 || DAT_800d1980) {
					CVector WallFloorNormal;
					int UpDot;

					SetVector(&WallFloorNormal, line_info.Normal.vx, line_info.Normal.vy,
					          line_info.Normal.vz) UpDot = Mips_CVecDotProd__FP7CVectorT0(&WallFloorNormal, &mUp);

					if (UpDot > -2048 && UpDot < 2048) {
						int TurnAway = 0;

						if (-line_info.Normal.vy > ABS(line_info.Normal.vx) &&
						    -line_info.Normal.vy > ABS(line_info.Normal.vz)) {
							m820 = 0;
							SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
							          line_info.Normal.vz) mPos.vx =
							    line_info.HitPoint.vx + line_info.Normal.vx * 30;
							mPos.vy = line_info.HitPoint.vy + line_info.Normal.vy * 30;
							mPos.vz = line_info.HitPoint.vz + line_info.Normal.vz * 30;
							OrientToNormal();

							if (m734 == 2) {
								m820 = 25;
								SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
								          line_info.Normal.vz)
								    SetVector(&m824, line_info.Normal.vx, line_info.Normal.vy,
									          line_info.Normal.vz)
								        ProjectCVectorToPlane(&mFront, line_info.Normal);
								M3dUtils_NormaliseVector(&mFront);
								SetVector(&mUp, line_info.Normal.vx, line_info.Normal.vy,
								          line_info.Normal.vz) gte_ldopv1(&mFront);
								gte_ldopv2(&mUp);
								gte_op12();
								gte_stlvnl(&mRight);
								RotMatrixFromFRUVectors();
							}

							StateTransition(0, 4193);
						} else {
							mPos = mOldPos;
							CVector OldVel = mVel;

							if (mAnim != 12 && OldVel.Length() >= 7 && !mInAir && !m368) {
								CVector WallFloorNormal;

								SetVector(&WallFloorNormal, line_info.Normal.vx,
								          line_info.Normal.vy,
								          line_info.Normal.vz) if (Mips_CVecDotProd__FP7CVectorT0(&WallFloorNormal,
								                                                &mFront) > 2896) {
									m150 = 0x10000;
									FUN_8002fcdc(this, 12, 4219);
									FUN_80043408(this);

									TurnAway = 200;
								}
							}

							FUN_80039f2c(this, line_info.Normal, TurnAway);
							m814.Set(0, 0, 0);
						}
					} else if (line_info.Distance <= Speed >> 12) {
						mPos.vx = line_info.HitPoint.vx + line_info.Normal.vx * 30;
						mPos.vy = line_info.HitPoint.vy + line_info.Normal.vy * 30;
						mPos.vz = line_info.HitPoint.vz + line_info.Normal.vz * 30;

						if (*(int *)&line_info.Normal == *(int *)&mLastNormal &&
						    line_info.Normal.vz == mLastNormal.vz) {
							m820++;
						} else {
							m820 = 0;
							SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
							          line_info.Normal.vz)
						}

						OrientToNormal();
					}
				}
			}
		}
	}

	Speed = FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(&mVel, &mVel)) << 6;

	if (mMaxSpeed < Speed)
		m304 = 1;
	else
		m304 = 0;

	CVector Old = mPos;

	if (FUN_800343f0(this, -1)) {
		if (FUN_800343f0(this, 1))
			mPos = Old;
	} else if (FUN_800343f0(this, 1)) {
		if (FUN_800343f0(this, -1))
			mPos = Old;
	}

	FRUVectorsFromRotMatrix();

	line_info.StartCoords.vx = mPos.vx + mUp.vx * 70;
	line_info.StartCoords.vy = mPos.vy + mUp.vy * 70;
	line_info.StartCoords.vz = mPos.vz + mUp.vz * 70;
	line_info.EndCoords.vx = line_info.StartCoords.vx - mUp.vx * 256;
	line_info.EndCoords.vy = line_info.StartCoords.vy - mUp.vy * 256;
	line_info.EndCoords.vz = line_info.StartCoords.vz - mUp.vz * 256;
	M3dColij_InitLineInfo(&line_info);
	FUN_800827d4(&line_info, 1);
	GetFaceFlags(&line_info);

	if (line_info.pItem) {
		m72C = DAT_800d1984;

		if (!DAT_800d1978 && !DAT_800d197c && !DAT_800d1974) {
			StateTransition(1, 4363);
		} else if (line_info.pItem) {
			int d = line_info.Distance;
			int CheckDist;

			if (m734 == 2) {
				m214 = 20;
				CheckDist = 160;
			} else {
				CheckDist = m214 + 116;
			}

			if (d <= CheckDist) {
				m768 = line_info.pFace->Flags & 0x20;
				CVector Orig = mPos;

				mPos.vx = line_info.HitPoint.vx + mUp.vx * 30;
				mPos.vy = line_info.HitPoint.vy + mUp.vy * 30;
				mPos.vz = line_info.HitPoint.vz + mUp.vz * 30;
				CVector Move = Orig - mPos;

				if (Mips_CVecDotProd__FP7CVectorT0(&Move, &Move) < 4096)
					mPos = Orig;

				if (DAT_800d1974) {
					if (!DAT_800d1980 && m1F8 && DAT_800d1770 - m1F8 >= 5 && !mInAir && m734 != 2) {
						SVECTOR N;

						N = line_info.Normal;
						mVel.vx -= Mips_FixMul__Fii(N.vx, Speed / 4);
						mVel.vz -= Mips_FixMul__Fii(N.vz, Speed / 4);
						mVel.vy /= 2;

						if (!m734) {
							m32C = 0;
							m328 = 0;
						}

						StateTransition(1, 4466);
						FUN_8002f1a0(this);

						m768 = 0;
						m150 = 0x10000;
						FUN_8002fcdc(this, 14, 4470);

						m740 = 1;
					} else {
						if (m734 != 2 && !m740 && !mInAir) {
							m150 = 0x10000;
							FUN_8002fcdc(this, 14, 4478);

							m740 = 1;
						}

						if (m734 != 2) {
							FUN_8002f1a0(this);

							m328 = 0;
							m32C = 0;
						}

						StateTransition(2, 4488);
					}
				} else if (DAT_800d1978) {
					if (m734)
						HandleBailPerpendicular(line_info.Normal);

					if (!m734) {
						CVector NewNormal;
						CVector LastNormal;
						int Dot;

						SetVector(&NewNormal, line_info.Normal.vx, line_info.Normal.vy,
						          line_info.Normal.vz)
						    SetVector(&LastNormal, mLastNormal.vx, mLastNormal.vy, mLastNormal.vz)
						        Dot = Mips_CVecDotProd__FP7CVectorT0(&LastNormal, &NewNormal);

						if (Mips_CVecDotProd__FP7CVectorT0(&mFront, &NewNormal) < 0 && mVel.vy <= 0 && Dot > 0 &&
						    Dot < 3000)
							FUN_8003434c(this);
					} else {
						StateTransition(0, 4551);
					}

					if (!OnInvisible) {
						mpWallItem = line_info.pItem;
						mWallHandle = FUN_8004d7ac(DAT_800bf7a8[line_info.pItem->Type].p14);
					}
				} else {
					FUN_8003434c(this);
				}

				if (m734 != 1) {
					if (*(int *)&line_info.Normal == *(int *)&mLastNormal &&
					    line_info.Normal.vz == mLastNormal.vz) {
						m820++;
					} else {
						m820 = 0;
						SetVector(&mLastNormal, line_info.Normal.vx, line_info.Normal.vy,
						          line_info.Normal.vz)
					}

					OrientToNormal();
				}
			} else {
				m768 = line_info.pFace->Flags & 0x20;
				FUN_8003434c(this);
			}
		} else {
			FUN_8003434c(this);
		}
	} else {
		FUN_8003434c(this);
	}

	if (m734 != 1 && line_info.pItem) {
		if (m734 == 2)
			InplaneGravity = mGravity;
		else
			InplaneGravity.Set(0, 6500, 0);

		ProjectCVectorToPlane(&InplaneGravity, line_info.Normal);

		mKick += InplaneGravity;

		if (m734 != 2)
			mFallLine = InplaneGravity;

		mPolyNormal = line_info.Normal;
		CVectorRotateToPlane(&mVel, &line_info.Normal, &mVel);
	} else {
		mKick += Gravity;
	}

	if (m734 != 2 && !mInAir) {
		CVector SideVelocity;
		CVector ForwardsVelocity;
		int dot;

		dot = Mips_CVecDotProd__FP7CVectorT0(&mVel, &mRight);
		SideVelocity.vx = Mips_FixMul__Fii(dot, mRight.vx);
		SideVelocity.vy = Mips_FixMul__Fii(dot, mRight.vy);
		SideVelocity.vz = Mips_FixMul__Fii(dot, mRight.vz);
		mVel -= SideVelocity;
		dot = Mips_CVecDotProd__FP7CVectorT0(&mVel, &mFront);
		ForwardsVelocity.vx = Mips_FixMul__Fii(dot, mFront.vx);
		ForwardsVelocity.vy = Mips_FixMul__Fii(dot, mFront.vy);
		ForwardsVelocity.vz = Mips_FixMul__Fii(dot, mFront.vz);

		if (!m304) {
			if (AutoKickEnabled) {
				mKick.vx -= Mips_FixMul__Fii(8, ForwardsVelocity.vx);
				mKick.vy -= Mips_FixMul__Fii(8, ForwardsVelocity.vy);
				mKick.vz -= Mips_FixMul__Fii(8, ForwardsVelocity.vz);
			}
		} else {
			mKick.vx -= Mips_FixMul__Fii(82, ForwardsVelocity.vx);
			mKick.vy -= Mips_FixMul__Fii(82, ForwardsVelocity.vy);
			mKick.vz -= Mips_FixMul__Fii(82, ForwardsVelocity.vz);
		}

		if (m72C == 5) {
			mKick.vx -= Mips_FixMul__Fii(120, ForwardsVelocity.vx);
			mKick.vy -= Mips_FixMul__Fii(120, ForwardsVelocity.vy);
			mKick.vz -= Mips_FixMul__Fii(120, ForwardsVelocity.vz);
		}

		if (m72C == 6) {
			mKick.vx -= Mips_FixMul__Fii(120, ForwardsVelocity.vx);
			mKick.vy -= Mips_FixMul__Fii(120, ForwardsVelocity.vy);
			mKick.vz -= Mips_FixMul__Fii(120, ForwardsVelocity.vz);
		}

		if (m72C == 3) {
			mKick.vx -= Mips_FixMul__Fii(180, ForwardsVelocity.vx);
			mKick.vy -= Mips_FixMul__Fii(180, ForwardsVelocity.vy);
			mKick.vz -= Mips_FixMul__Fii(180, ForwardsVelocity.vz);
		}
	}
}
