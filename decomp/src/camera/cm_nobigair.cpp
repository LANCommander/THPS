/* CM_NoBigAir__7CCamera (0x8007cd78) */
/* C++ (CAMERA.CPP). Demo twin (0.92 by opcode; THPS1 always uses the tripod's up vector); locals from
   its MAIN.SYM. Camera mode for normal skating: smooths the travel direction into vFront, builds
   a look basis from it and the skater's up vector, and aims mDesiredO along it (plus extra_YRot).
   Down, Zero and U/V/N are declared where retail's frame shows them starting. */
#pragma interface

extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

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
	int Length() const;
	int operator==(const CVector &);
};

struct CSVector {
	short vx, vy, vz;
};

struct CFriction {
	uchar x, y, z;
};

class CClass {
  public:
	virtual ~CClass() {}
};

class CQuat : public CClass {
  public:
	int x, y, z, w;
	CQuat() {
		x = 0;
		y = 0;
		z = 0;
		w = 4096;
	}
};

template <class T> class AnimParam : public CClass {
  public:
	uint *mTimer;
	T mParam;
	AnimParam(uint &timer) : mTimer(&timer) {}
	virtual ~AnimParam();
};

class CamPos : public CClass {
  public:
	char pad[180];
	CamPos();
	virtual ~CamPos();
};

class CItem {
  public:
	short mType;      /* 0x000 */
	CVector mPos;     /* 0x004 */
	CSVector mAngles; /* 0x010 */
	char pad16[0x3a - 0x16];
	short m3a; /* 0x03a */
	char pad3c[0x48 - 0x3c];
	virtual ~CItem();
};

class CBody : public CItem {
  public:
	CBody **mppOriginalList; /* 0x04c */
	ushort mInputFlags;      /* 0x050 */
	ushort mCBodyFlags;      /* 0x052 */
	char pad54[0x6c - 0x54];
	CVector mVel; /* 0x06c */
	char pad78[0xe0 - 0x78];
	ushort mRMinor; /* 0x0e0 */
	char pade2[0x134 - 0xe2];
	CBody();
	virtual ~CBody();
	void AttachTo(CBody **);
};

struct SButton {
	uchar Pressed;
	uchar Triggered;
	int PressedTime;
	int ReleasedTime;
	int TriggeredTime;
};

struct SControl {
	SButton Triangle, Square, Circle, X;
	char pad40[364 - 64];
};

class CBruce : public CBody {
  public:
	char pad134[0x35c - 0x134];
	int m35c; /* 0x35c */
	char pad360[0x734 - 0x360];
	int m734; /* 0x734 */
	char pad738[0x740 - 0x738];
	int m740; /* 0x740 */
	char pad744[0x7f0 - 0x744];
	CVector mUp; /* 0x7f0 */
	char pad7fc[0x86c - 0x7fc];
	SControl *mpPad; /* 0x86c */
};

struct SMike {
	char pad0[24];
	CSVector mAngles;
};

class CCamera : public CBody {
  public:
	ushort mMikeIndex; /* 0x134 */
	CamPos mPosA;      /* 0x138 */
	CamPos mLastPos;
	CamPos mCurrentPos;
	CamPos mPosB;
	uint mCamPosDelta; /* 0x418 */
	uint mCamPosRate;
	CBruce *mTripod; /* 0x420 */
	CBody *mOldTripod;
	int mCalcTripod;       /* 0x428 */
	CVector mOldTripodPos; /* 0x42c */
	int new_focus;         /* 0x438 */
	CVector mTripodPos;    /* 0x43c */
	CVector mTripodPosIncrement;
	uint mTripodTime;     /* 0x454 */
	CBody *mFocus;        /* 0x458 */
	int mCalcFocus;       /* 0x45c */
	CVector mOldFocusPos; /* 0x460 */
	CVector mFocusPos;    /* 0x46c */
	CVector mFocusPosIncrement;
	uint mFocusTime;    /* 0x484 */
	int mZoom;          /* 0x488 */
	ushort mZoomTime;   /* 0x48c */
	int mZoomIncrement; /* 0x490 */
	int mOnRail;        /* 0x494 */
	CVector mRailStart; /* 0x498 */
	CVector mRailEnd;
	short mPitchDamper;      /* 0x4b0 */
	short mTripodPosYDamper; /* 0x4b2 */
	CVector mUp;             /* 0x4b4 */
	CQuat mO;                /* 0x4c0 */
	CQuat mDesiredO;
	CQuat mPrevO;
	CQuat mPreFocusO;
	CQuat mStoppedO;
	int mStoppedOValid;  /* 0x524 */
	CSVector mCamAngles; /* 0x528 */
	CVector mPosOffset;  /* 0x530 */
	CVector mDesiredPos;
	CVector mDesiredFocusPos;
	int mCollisionRayLR; /* 0x554 */
	int mCollisionRayBack;
	short mCollisionAngLR; /* 0x55c */
	short mCollisionAngBack;
	short mCollisionBack;      /* 0x560 */
	int saved_mCollisionRayLR; /* 0x564 */
	int saved_mCollisionRayBack;
	short saved_mCollisionAngLR;
	short saved_mCollisionAngBack;
	short saved_mCollisionBack;
	CSVector mShakeAmplitude; /* 0x572 */
	CFriction mShakeDecay;    /* 0x578 */
	CSVector mShakeSpeed;     /* 0x57c */
	int mCameraMode;          /* 0x584 */
	int mCameraModeIncDir;
	int mBossCamSpinRate;      /* 0x58c */
	uint mTimer;               /* 0x590 */
	AnimParam<CQuat> testQuat; /* 0x594 */
	short mColAngBuffer[8];    /* 0x5b0 */
	short mPrevColAngBuffer[8];
	uchar mColCheckIndex; /* 0x5d0 */
	uint mColCheckCycleCounter;
	int mDownDist; /* 0x5d8 */
	int mCompIntroTimer;
	int mSpeedUpIntro; /* 0x5e0 */
	CVector mCompIntroEndPos;
	int extra_YRot; /* 0x5f0 */
	CVector mVFront;
	CVector mOldVFront;
	int prev_speed_lag_dist; /* 0x60c */
	int big_air;             /* 0x610 */
	int big_air_timer;
	int big_air_end_timer;
	int big_air_mph;
	int new_hang_time;
	int in_pool_timer; /* 0x624 */
	int jump_acc;
	int jump_uptimer;
	int max_jump_dist;
	int max_jump_dist2;
	int jump_timer;
	int max_timer;
	int landing_timer;
	int landing_pos;
	int turn_delay_timer;
	CVector vFront; /* 0x64c */
	uint mSpeed;    /* 0x658 */
	int mSpeedBuffer[6];
	short mStoppedExtraYRot; /* 0x674 */
	VECTOR real_cam_offset;  /* 0x678 */
	CQuat old_orientation;   /* 0x688 */
	int old_offset[4];
	int loose_cam_timer; /* 0x6ac */
	CCamera(CBody *tripod, ushort mike_index);
	virtual ~CCamera();
	void LoadIntoMikeCamera();
	void CM_CompetitionIntro();
	void MoveToDesiredPos(uint);
	void CM_NoBigAir();
	void ReactToCollision();
};

extern MATRIX DAT_800c12e4;

void MToQ(const MATRIX &, CQuat &);
extern "C" int Mips_CVecDotProd__FP7CVectorT0(CVector *, CVector *);
void Utils_CalcAim(CSVector &, const CVector &, const CVector &);
void Utils_GetVecFromMagDir(CVector &, int, const CSVector &);
CVector operator-(const CVector &, const CVector &);
CVector operator+(const CVector &, const CVector &);
CVector operator>>(const CVector &, const int &);
CQuat operator*(const CQuat &, const CQuat &);
CQuat Quat_FromYRot(short);

#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

void CCamera::CM_NoBigAir() {
	CVector vUp;
	CVector vRight;
	CSVector ang1;
	int dot_front;
	CVector temp_vel = mTripodPos - mOldTripodPos;

	vUp = mTripod->mUp;
	CVector Down(0, 4096, 0);
	CVector Zero(0, 0, 0);
	CVector temp_front;

	ABS(Mips_CVecDotProd__FP7CVectorT0(&Down, &vUp));
	Utils_CalcAim(ang1, Zero, temp_vel);
	Utils_GetVecFromMagDir(temp_front, 4096, ang1);

	dot_front = ABS(Mips_CVecDotProd__FP7CVectorT0(&temp_front, &vUp)) >> 12;

	if (dot_front > 2000 || temp_vel.Length() < 5) {
		big_air = 0;
	} else {
		big_air = 0;
		Utils_GetVecFromMagDir(vFront, 4096, ang1);
	}

	mOldVFront = mVFront;

	if (mTripodPos == mOldTripodPos)
		mVFront = mOldVFront;
	else
		mVFront = (mOldVFront + vFront) >> 1;

	vFront = mVFront;
	CVector U;
	CVector V;
	CVector N;

	N = vFront >> 12;
	V.vx = -vUp.vx;
	V.vy = -vUp.vy;
	V.vz = -vUp.vz;
	gte_ldopv1(&V);
	gte_ldopv2(&N);
	gte_op0();
	gte_stlvnl(&U);
	U.vx >>= 12;
	U.vy >>= 12;
	U.vz >>= 12;
	gte_ldopv1(&U);
	gte_ldopv2(&V);
	gte_op0();
	gte_stlvnl(&N);
	N.vx >>= 12;
	N.vy >>= 12;
	N.vz >>= 12;
	DAT_800c12e4.m[0][0] = U.vx;
	DAT_800c12e4.m[1][0] = U.vy;
	DAT_800c12e4.m[2][0] = U.vz;
	DAT_800c12e4.m[0][1] = V.vx;
	DAT_800c12e4.m[1][1] = V.vy;
	DAT_800c12e4.m[2][1] = V.vz;
	DAT_800c12e4.m[0][2] = N.vx;
	DAT_800c12e4.m[1][2] = N.vy;
	DAT_800c12e4.m[2][2] = N.vz;
	MToQ(DAT_800c12e4, mDesiredO);

	mDesiredO = mDesiredO * Quat_FromYRot(extra_YRot);
	big_air = 0;
}
