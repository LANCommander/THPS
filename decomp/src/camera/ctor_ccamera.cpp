/* __7CCameraP5CBodyUs (0x800785f0) flags=-fstructure-noalias */
/* C++ (CAMERA.CPP). Fuzzy demo twin (0.97 by opcode); members from its MAIN.SYM, laid out by THPS1
   offsets (CCamera members = demo + 0x2c). Most members are set in the initialiser list. */
#pragma interface

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
};

struct CSVector {
	short vx, vy, vz;
};

struct CFriction {
	uchar x, y, z;
};

class CClass {
  public:
	virtual ~CClass();
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
	char pad54[0xe0 - 0x54];
	ushort mRMinor; /* 0x0e0 */
	char pade2[0x134 - 0xe2];
	CBody();
	virtual ~CBody();
	void AttachTo(CBody **);
};

struct SControl {
	char pad[364];
};

class CBruce : public CBody {
  public:
	char pad134[0x86c - 0x134];
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
	CBody *mTripod; /* 0x420 */
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
	int real_cam_offset[4];  /* 0x678 */
	CQuat old_orientation;   /* 0x688 */
	int old_offset[4];
	int loose_cam_timer; /* 0x6ac */
	CCamera(CBody *tripod, ushort mike_index);
	virtual ~CCamera();
	void LoadIntoMikeCamera();
};

extern SControl Pad[2];
extern SMike Presets;

int camDist;
int camPitch;
int camYOffset;
int Camera_Preset;
int NumCameras;
CBody *CameraList;

CCamera::CCamera(CBody *tripod, ushort mike_index)
    : mMikeIndex(mike_index), mTripod(tripod), mCalcTripod(1), new_focus(0), mFocus(tripod),
      mCalcFocus(1), mZoom(192), mOnRail(0), mPitchDamper(0), mTripodPosYDamper(0),
      mCollisionRayLR(-1), mCollisionRayBack(-1), mCollisionAngLR(512), mCollisionAngBack(784),
      mCollisionBack(1384), mCameraMode(1), mCameraModeIncDir(0), mBossCamSpinRate(15), mTimer(0),
      testQuat(mTimer), mColCheckIndex(0), mColCheckCycleCounter(0), mDownDist(0), mSpeedUpIntro(0),
      mStoppedExtraYRot(0) {
	loose_cam_timer = 0;

	if (((CBruce *)mTripod)->mpPad == &Pad[0])
		mMikeIndex = 0;
	else if (((CBruce *)mTripod)->mpPad == &Pad[1])
		mMikeIndex = 1;

	vFront = CVector(0, 0, 4096);
	big_air = 0;
	in_pool_timer = 1000;
	extra_YRot = 0;
	mTripodPos = mTripod->mPos;
	mTripodTime = 0;
	mFocusPos = mFocus->mPos;
	mFocusTime = 0;
	m3a = 99;
	Camera_Preset = 2;

	{
		SMike &m = Presets;
		CSVector &a = m.mAngles;

		camDist = a.vz;
		camPitch = a.vy;
		camYOffset = a.vx;
	}

	mType = 1;
	LoadIntoMikeCamera();
	AttachTo(&CameraList);

	NumCameras++;
	mRMinor = 0;
	mCBodyFlags &= ~2;
}
