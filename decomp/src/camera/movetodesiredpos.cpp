/* MoveToDesiredPos__7CCameraUi (0x8007a494) flags=-fstructure-noalias */
/* C++ (CAMERA.CPP). Fuzzy demo twin (0.89 by opcode); locals from its MAIN.SYM. Moves the camera
   each frame. With no tripod it builds a look-at basis from the focus direction and slerps to it.
   Otherwise it averages the tripod's speed into mph and a speed lag, tilts down if a ray behind
   the camera is clear, then either does big-air handling (lifting the offset by hang time) or
   normal tilt/loosen handling, slerps mO toward mDesiredO, and places the camera.
   THPS1 drops the demo's |N.V| test (always the second basis) and the gp camera-offset copy.
   fold() moves a constant onto the *other* factor of a product: `temptime * 8000 * big_air_mph`
   shifts big_air_mph and multiplies by temptime, as retail does. Locals are declared where
   first used so their stack slots reuse the earlier blocks' slots. */
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
	int Length() const;
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
	char pad744[0x86c - 0x744];
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
	void ReactToCollision();
};

struct Vector {
	int vx, vy, vz;
};

struct SLineInfo {
	Vector StartCoords;
	Vector EndCoords;
	Vector MinCoords;
	Vector MaxCoords;
	int iLo, iHi, jLo, jHi;
	int Distance;
	int Length;
	char pad48[104 - 72];
	int m68; /* 104 */
	char pad6c[136 - 108];
	char m88; /* 136 */
	char pad89[168 - 137];
};

extern MATRIX DAT_800c12e4;
extern CVector DAT_800c1154;
extern int DAT_800d20cc;

int DAT_800d203c;
int DAT_800d2038;

void QToM(const CQuat &, MATRIX &);
void MToQ(const MATRIX &, CQuat &);
extern "C" VECTOR *FUN_80092f60(MATRIX *, VECTOR *, VECTOR *);
extern "C" int Mips_CVecDotProd__FP7CVectorT0(CVector *, CVector *);
extern "C" int FUN_8008b5dc(int);
extern "C" int M3dZone_LineToItemNotSCached__FP9SLineInfoi(SLineInfo *, int);
void M3dColij_InitLineInfo(SLineInfo *);
void Utils_CalcUnit(CVector &, const CVector &);
CVector operator-(const CVector &, const CVector &);
CQuat operator*(const CQuat &, const CQuat &);
CQuat Quat_FromXRot(short);
void Quat_Slerp(CQuat, CQuat, int, CQuat &);

void CCamera::MoveToDesiredPos(uint normal_slerp) {
	mPrevO = mO;

	if (!mTripod) {
		CVector U;
		CVector V;
		CVector N;

		Utils_CalcUnit(N, mFocusPos - mTripodPos);

		V.vx = 0;
		V.vy = 4096;
		V.vz = 0;
		gte_ldopv1(&V);
		gte_ldopv2(&N);
		gte_op0();
		gte_stlvnl(&U);
		U.vx >>= 12;
		U.vy >>= 12;
		U.vz >>= 12;
		gte_ldopv1(&N);
		gte_ldopv2(&U);
		gte_op0();
		gte_stlvnl(&V);
		V.vx >>= 12;
		V.vy >>= 12;
		V.vz >>= 12;
		DAT_800c12e4.m[0][0] = U.vx;
		DAT_800c12e4.m[1][0] = U.vy;
		DAT_800c12e4.m[2][0] = U.vz;
		DAT_800c12e4.m[0][1] = V.vx;
		DAT_800c12e4.m[1][1] = V.vy;
		DAT_800c12e4.m[2][1] = V.vz;
		DAT_800c12e4.m[0][2] = N.vx;
		DAT_800c12e4.m[1][2] = N.vy;
		DAT_800c12e4.m[2][2] = N.vz;
		CQuat tempO;

		MToQ(DAT_800c12e4, tempO);

		if (new_focus) {
			mO = tempO;
			new_focus = 0;
		} else {
			Quat_Slerp(mPrevO, tempO, 2047, mO);
		}

		mPos = mTripodPos;
		return;
	}

	CVector old_pos;
	CVector Dist;
	int Spd;
	int Frames;
	int mph;
	VECTOR v1;
	VECTOR v2;
	int speed_lag_dist;
	int temptime;

	old_pos = mPos;
	Dist = mTripod->mVel;

	if (mTripod->m734 == 0 || mTripod->m734 == 4) {
		{
			int i;

			for (i = 5; i > 0; i--)
				mSpeedBuffer[i] = mSpeedBuffer[i - 1];
		}

		if (Dist.Length() > 100) {
			Dist.vx = 0x64000;
			Dist.vy = 0;
			Dist.vz = 0;
		}

		mSpeedBuffer[0] = FUN_8008b5dc(Mips_CVecDotProd__FP7CVectorT0(&Dist, &Dist)) << 6;
	}

	Spd = 0;

	{
		int i;

		for (i = 0; i < 6; i++)
			Spd += mSpeedBuffer[i];
	}

	Spd /= 6;
	Frames = 2;
	mph = Spd / 34 * 60 / Frames * 3600 / 5278;
	mph >>= 12;
	mSpeed = mph;
	speed_lag_dist = (DAT_800d203c + mph * 4 + prev_speed_lag_dist) >> 1;
	prev_speed_lag_dist = speed_lag_dist;
	v1.vx = 0;
	v1.vy = 0;
	v1.vz = -(speed_lag_dist << 12);

	if (turn_delay_timer >= 4) {
		CQuat wouldbeO = mDesiredO * Quat_FromXRot(-450);
		MATRIX m;
		VECTOR v;
		VECTOR vCheck;
		SLineInfo line_info;

		v.vx = 0;
		v.vy = 0;
		v.vz = -(DAT_800d203c << 12);
		QToM(wouldbeO, m);
		FUN_80092f60(&m, &v, &vCheck);

		line_info.StartCoords.vx = mTripodPos.vx;
		line_info.StartCoords.vy = mTripodPos.vy;
		line_info.StartCoords.vz = mTripodPos.vz;
		line_info.EndCoords.vx = mTripodPos.vx + vCheck.vx;
		line_info.EndCoords.vy = mTripodPos.vy + vCheck.vy;
		line_info.EndCoords.vz = mTripodPos.vz + vCheck.vz;
		M3dColij_InitLineInfo(&line_info);

		line_info.m88 = 0;
		DAT_800d20cc = 1;
		M3dZone_LineToItemNotSCached__FP9SLineInfoi(&line_info, 1);

		DAT_800d20cc = 0;

		if (!line_info.m68)
			mDesiredO = wouldbeO;
	}

	if ((big_air && mTripod->m35c) || big_air_timer > 0) {
		ReactToCollision();

		if (!big_air_timer)
			big_air_mph = mph;

		if (big_air_mph > 30)
			big_air_mph = 30;

		if (!big_air) {
			temptime = big_air_timer;

			if (temptime <= 0) {
				temptime = 0;
			} else {
				if (!big_air_end_timer) {
					if (temptime >= 8)
						temptime = 7;

					big_air_end_timer = temptime + 1;
				} else {
					temptime = big_air_end_timer - 1;
				}
			}

			if (!temptime) {
				big_air_end_timer = 1;
				big_air_timer = -1;
				new_hang_time = 0;
			}

			temptime = temptime * temptime;
			big_air_end_timer--;
			DAT_800c1154.vy += temptime * 8000 * big_air_mph / 30;
			v1.vz += big_air_mph * 600 * temptime;
		} else {
			big_air_end_timer = 0;

			if (big_air_timer >= 7) {
				temptime = 49;
				DAT_800c1154.vy += temptime * 8000 * big_air_mph / 30;
				v1.vz += big_air_mph * 600 * temptime;
				new_hang_time++;
			} else if (big_air_timer >= 0) {
				temptime = big_air_timer * big_air_timer;
				new_hang_time = 0;
				DAT_800c1154.vy += temptime * 8000 * big_air_mph / 30;
				v1.vz += big_air_mph * 600 * temptime;
			}
		}

		Quat_Slerp(mPrevO, mDesiredO, 222, mO);

		big_air_timer++;
	} else {
		int loosen_up = 0;

		if (loose_cam_timer > 0) {
			loosen_up = 1;
			loose_cam_timer--;
		}

		mDesiredO = mDesiredO * Quat_FromXRot(DAT_800d2038);
		ReactToCollision();

		if (mTripod->m740) {
			if (mTripod->m734 == 3) {
				loosen_up = 1;
				loose_cam_timer = 20;
			} else if (mTripod->m734 == 1) {
				mDesiredO = mDesiredO * Quat_FromXRot(200);
			}
		}

		if (in_pool_timer >= 2 && in_pool_timer < 20)
			Quat_Slerp(mPrevO, mDesiredO, 311, mO);
		else if (loosen_up)
			Quat_Slerp(mPrevO, mDesiredO, (20 - loose_cam_timer) * 13 + 51, mO);
		else
			Quat_Slerp(mPrevO, mDesiredO, normal_slerp, mO);
	}

	if (mTimer < 12)
		mPrevO = mO = mDesiredO;

	MATRIX m;

	QToM(mO, m);
	FUN_80092f60(&m, &v1, &v2);

	v1.vx = DAT_800c1154.vx;
	v1.vy = DAT_800c1154.vy;
	v1.vz = DAT_800c1154.vz;
	FUN_80092f60(&m, &v1, &real_cam_offset);

	mPos.vx = mTripodPos.vx + v2.vx;
	mPos.vy = mTripodPos.vy + v2.vy;
	mPos.vz = mTripodPos.vz + v2.vz;
	mVel = mPos - old_pos;
}
