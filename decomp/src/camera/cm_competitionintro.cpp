/* CM_CompetitionIntro__7CCamera (0x8007c83c) flags=-fstructure-noalias */
/* C++ (CAMERA.CPP). Fuzzy demo twin (0.92 by opcode); locals from its MAIN.SYM. The competition
   intro: on the first frame, settle the world and place the camera behind the skater; then slerp
   from the level's intro orientation to the desired one over 130 ticks while sliding the camera in
   from the intro position (X on either pad speeds it up), and start the run when done. The later
   locals are declared mid-block so their slots reuse the freed CQuat temporaries, as retail's do. */
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
	CQuat() { x = 0; y = 0; z = 0; w = 4096; }
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
	short mType;               /* 0x000 */
	CVector mPos;              /* 0x004 */
	CSVector mAngles;          /* 0x010 */
	char pad16[0x3a - 0x16];
	short m3a;                 /* 0x03a */
	char pad3c[0x48 - 0x3c];
	virtual ~CItem();
};
class CBody : public CItem {
public:
	CBody **mppOriginalList;   /* 0x04c */
	ushort mInputFlags;        /* 0x050 */
	ushort mCBodyFlags;        /* 0x052 */
	char pad54[0x6c - 0x54];
	CVector mVel;              /* 0x06c */
	char pad78[0xe0 - 0x78];
	ushort mRMinor;            /* 0x0e0 */
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
	char pad134[0x7d8 - 0x134];
	CVector mSpeedVec;         /* 0x7d8 */
	char pad7e4[0x86c - 0x7e4];
	SControl *mpPad;           /* 0x86c */
};
struct SMike {
	char pad0[24];
	CSVector mAngles;
};
class CCamera : public CBody {
public:
	ushort mMikeIndex;         /* 0x134 */
	CamPos mPosA;              /* 0x138 */
	CamPos mLastPos;
	CamPos mCurrentPos;
	CamPos mPosB;
	uint mCamPosDelta;         /* 0x418 */
	uint mCamPosRate;
	CBody *mTripod;            /* 0x420 */
	CBody *mOldTripod;
	int mCalcTripod;           /* 0x428 */
	CVector mOldTripodPos;     /* 0x42c */
	int new_focus;             /* 0x438 */
	CVector mTripodPos;        /* 0x43c */
	CVector mTripodPosIncrement;
	uint mTripodTime;          /* 0x454 */
	CBody *mFocus;             /* 0x458 */
	int mCalcFocus;            /* 0x45c */
	CVector mOldFocusPos;      /* 0x460 */
	CVector mFocusPos;         /* 0x46c */
	CVector mFocusPosIncrement;
	uint mFocusTime;           /* 0x484 */
	int mZoom;                 /* 0x488 */
	ushort mZoomTime;          /* 0x48c */
	int mZoomIncrement;        /* 0x490 */
	int mOnRail;               /* 0x494 */
	CVector mRailStart;        /* 0x498 */
	CVector mRailEnd;
	short mPitchDamper;        /* 0x4b0 */
	short mTripodPosYDamper;   /* 0x4b2 */
	CVector mUp;               /* 0x4b4 */
	CQuat mO;                  /* 0x4c0 */
	CQuat mDesiredO;
	CQuat mPrevO;
	CQuat mPreFocusO;
	CQuat mStoppedO;
	int mStoppedOValid;        /* 0x524 */
	CSVector mCamAngles;       /* 0x528 */
	CVector mPosOffset;        /* 0x530 */
	CVector mDesiredPos;
	CVector mDesiredFocusPos;
	int mCollisionRayLR;       /* 0x554 */
	int mCollisionRayBack;
	short mCollisionAngLR;     /* 0x55c */
	short mCollisionAngBack;
	short mCollisionBack;      /* 0x560 */
	int saved_mCollisionRayLR; /* 0x564 */
	int saved_mCollisionRayBack;
	short saved_mCollisionAngLR;
	short saved_mCollisionAngBack;
	short saved_mCollisionBack;
	CSVector mShakeAmplitude;  /* 0x572 */
	CFriction mShakeDecay;     /* 0x578 */
	CSVector mShakeSpeed;      /* 0x57c */
	int mCameraMode;           /* 0x584 */
	int mCameraModeIncDir;
	int mBossCamSpinRate;      /* 0x58c */
	uint mTimer;               /* 0x590 */
	AnimParam<CQuat> testQuat; /* 0x594 */
	short mColAngBuffer[8];    /* 0x5b0 */
	short mPrevColAngBuffer[8];
	uchar mColCheckIndex;      /* 0x5d0 */
	uint mColCheckCycleCounter;
	int mDownDist;             /* 0x5d8 */
	int mCompIntroTimer;
	int mSpeedUpIntro;         /* 0x5e0 */
	CVector mCompIntroEndPos;
	int extra_YRot;            /* 0x5f0 */
	CVector mVFront;
	CVector mOldVFront;
	int prev_speed_lag_dist;   /* 0x60c */
	int big_air;               /* 0x610 */
	int big_air_timer;
	int big_air_end_timer;
	int big_air_mph;
	int new_hang_time;
	int in_pool_timer;         /* 0x624 */
	int jump_acc;
	int jump_uptimer;
	int max_jump_dist;
	int max_jump_dist2;
	int jump_timer;
	int max_timer;
	int landing_timer;
	int landing_pos;
	int turn_delay_timer;
	CVector vFront;            /* 0x64c */
	uint mSpeed;               /* 0x658 */
	int mSpeedBuffer[6];
	short mStoppedExtraYRot;   /* 0x674 */
	VECTOR real_cam_offset;    /* 0x678 */
	CQuat old_orientation;     /* 0x688 */
	int old_offset[4];
	int loose_cam_timer;       /* 0x6ac */
	CCamera(CBody *tripod, ushort mike_index);
	virtual ~CCamera();
	void LoadIntoMikeCamera();
	void CM_CompetitionIntro();
};
struct SIntroCam {
	char pad0[100];
	int Pos[3];                /* 100 */
	CSVector Angles;           /* 112 */
	char pad118[120 - 118];
};
extern SControl DAT_800c0a48[2];
extern SIntroCam DAT_800a5398[];
extern CVector DAT_800c1154;
extern CBruce *DAT_800d17c8;
extern CBruce *DAT_800d19a4;
extern int DAT_800d1e28;
int DAT_800d203c;
CBody *DAT_800d2044;
enum EVideoMode { VIDEO_0, VIDEO_1 };
void Ob_AI(CBody **);
void QToM(const CQuat &, MATRIX &);
extern "C" VECTOR *FUN_80092f60(MATRIX *, VECTOR *, VECTOR *);
CQuat operator*(const CQuat &, const CQuat &);
CQuat Quat_FromXRot(short);
CQuat Quat_FromYRot(short);
CQuat Quat_FromZRot(short);
void Quat_Slerp(CQuat, CQuat, int, CQuat &);
void Video_Start(CBruce *, EVideoMode, int, int);
void Competition_MarqueeDisplay();
CVector operator-(const CVector &, const CVector &);
CVector operator/(const CVector &, const int &);
CVector operator*(const CVector &, const int &);
CVector operator*(const int &, const CVector &);

void CCamera::CM_CompetitionIntro()
{
	if (!mCompIntroTimer) {
		VECTOR v1;
		VECTOR v2;
		int speed_lag_dist;
		MATRIX m;
		mCameraMode = 1;
		DAT_800d17c8->mVel.vx = DAT_800d17c8->mSpeedVec.vx * 20;
		DAT_800d17c8->mVel.vy = DAT_800d17c8->mSpeedVec.vy * 20;
		DAT_800d17c8->mVel.vz = DAT_800d17c8->mSpeedVec.vz * 20;
		{
			int i;
			for (i = 0; i < 10; i++)
				Ob_AI(&DAT_800d2044);
		}
		DAT_800d17c8->mVel.vx = 0;
		DAT_800d17c8->mVel.vy = 0;
		DAT_800d17c8->mVel.vz = 0;
		mCameraMode = 23;
		speed_lag_dist = DAT_800d203c >> 1;
		prev_speed_lag_dist = speed_lag_dist;
		v1.vx = 0;
		v1.vy = 0;
		v1.vz = -(speed_lag_dist << 12);
		QToM(mO, m);
		FUN_80092f60(&m, &v1, &v2);
		v1.vx = DAT_800c1154.vx;
		v1.vy = DAT_800c1154.vy;
		v1.vz = DAT_800c1154.vz;
		FUN_80092f60(&m, &v1, &real_cam_offset);
		mPos.vx = mTripodPos.vx + v2.vx;
		mPos.vy = mTripodPos.vy + v2.vy;
		mPos.vz = mTripodPos.vz + v2.vz;
		mCompIntroEndPos.vx = mPos.vx;
		mCompIntroEndPos.vy = mPos.vy;
		mCompIntroEndPos.vz = mPos.vz;
	}
	CQuat begin_o;
	CQuat end_o;
	end_o = mDesiredO;
	begin_o = Quat_FromYRot(DAT_800a5398[DAT_800d1e28].Angles.vy) * Quat_FromXRot(DAT_800a5398[DAT_800d1e28].Angles.vx) * Quat_FromZRot(DAT_800a5398[DAT_800d1e28].Angles.vz);
	{
		int t = (uint)(mCompIntroTimer << 12) / 130;
		Quat_Slerp(begin_o, end_o, t, mO);
	}
	if ((uint)mCompIntroTimer > 130) {
		Video_Start(DAT_800d19a4, VIDEO_1, 1, 0x7fffffff);
		mCameraMode = 1;
		return;
	}
	Competition_MarqueeDisplay();
	CVector begin_pos;
	CVector offset_inc;
	begin_pos.vx = DAT_800a5398[DAT_800d1e28].Pos[0] << 12;
	begin_pos.vy = DAT_800a5398[DAT_800d1e28].Pos[1] << 12;
	begin_pos.vz = DAT_800a5398[DAT_800d1e28].Pos[2] << 12;
	offset_inc = (begin_pos - mCompIntroEndPos) / 130;
	CVector offset = offset_inc * 130 - mCompIntroTimer * offset_inc;
	int activated;
	mPos.vx = mCompIntroEndPos.vx + offset.vx;
	mPos.vy = mCompIntroEndPos.vy + offset.vy;
	mPos.vz = mCompIntroEndPos.vz + offset.vz;
	activated = DAT_800c0a48[0].X.Pressed || DAT_800c0a48[1].X.Pressed;
	if (activated)
		mSpeedUpIntro = 1;
	if (mSpeedUpIntro)
		mCompIntroTimer += 6;
	else
		mCompIntroTimer++;
}
