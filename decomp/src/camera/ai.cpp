/* AI__7CCamera (0x8007b7c4) */
/* C++ (CAMERA.CPP). Demo twin (opcode-identical but for 3 spots); layout by THPS1 offsets
   (CCamera members = demo + 0x2c). Pad is the SControl[2] array at DAT_800c0a48. */
#pragma interface
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
	SButton LeftOne, LeftTwo, RightOne, RightTwo;
	SButton Left, Right, Up, Down;
	SButton AnalogueLeft, AnalogueRight, Start, Select;
	char pad100[0x16c - 0x100];
};
class CBruce {
public:
	char pad0[4];
	CVector mPos;
	char pad10[0x70 - 0x10];
	int mVelY;                 /* 0x70 */
	char pad74[0x358 - 0x74];
	int m358;                  /* 0x358 */
	char pad35c[0x734 - 0x35c];
	int m734;                  /* 0x734 */
	char pad738[0x8fe - 0x738];
	ushort m8fe;               /* 0x8fe */
};
struct SViewport {
	char pad0[14];
	short mZoom;
};
class CCamera {
public:
	char pad0[4];
	CVector mPos;              /* 0x004 */
	CSVector mAngles;          /* 0x010 */
	char pad16[0x134 - 0x16];
	ushort mMikeIndex;         /* 0x134 */
	char pad136[0x420 - 0x136];
	CBruce *mTripod;           /* 0x420 */
	CBruce *mOldTripod;
	int mCalcTripod;           /* 0x428 */
	CVector mOldTripodPos;     /* 0x42c */
	int new_focus;             /* 0x438 */
	CVector mTripodPos;        /* 0x43c */
	CVector mTripodPosIncrement;
	uint mTripodTime;
	CBruce *mFocus;            /* 0x458 */
	int mCalcFocus;            /* 0x45c */
	CVector mOldFocusPos;      /* 0x460 */
	CVector mFocusPos;         /* 0x46c */
	CVector mFocusPosIncrement;
	uint mFocusTime;
	int mZoom;                 /* 0x488 */
	ushort mZoomTime;          /* 0x48c */
	int mZoomIncrement;        /* 0x490 */
	char pad494[0x4b0 - 0x494];
	short mPitchDamper;        /* 0x4b0 */
	short mTripodPosYDamper;   /* 0x4b2 */
	char pad4b4[0x4c0 - 0x4b4];
	CQuat mO;                  /* 0x4c0 */
	char pad4d4[0x572 - 0x4d4];
	CSVector mShakeAmplitude;  /* 0x572 */
	CFriction mShakeDecay;     /* 0x578 */
	CSVector mShakeSpeed;      /* 0x57c */
	int mCameraMode;           /* 0x584 */
	int mCameraModeIncDir;
	int mBossCamSpinRate;
	uint mTimer;               /* 0x590 */
	char pad594[0x5f0 - 0x594];
	int extra_YRot;            /* 0x5f0 */
	char pad5f4[0x628 - 0x5f4];
	int jump_acc;              /* 0x628 */
	int jump_uptimer;          /* 0x62c */
	char pad630[0x658 - 0x630];
	uint mSpeed;               /* 0x658 */
	void AI();
	void CM_Normal();
	void CM_NoBigAir();
	void CM_CompetitionIntro();
	void MoveToDesiredPos(uint);
	void LoadIntoMikeCamera();
};
struct SSinCos { short s, c; };
extern SSinCos DAT_800c9670;
#define SIN(a) ((&DAT_800c9670)[(a) & 4095].s)
extern SControl DAT_800c0a48[2];
extern CVector DAT_800c1154;
extern int DAT_800d1728;
extern int DAT_800d16fc;
extern int DAT_800d140c;
extern SViewport *DAT_800d2178;
extern int DAT_800d16e4;
int DAT_800d2048;
int DAT_800d1ff4;
int DAT_800d1ff8;
int DAT_800d1ffc;
int DAT_800d2038;
int DAT_800d203c;
int DAT_800d2080;
int DAT_800d2084;
int DAT_800d2088;
int DAT_800d208c;
int DAT_800d2090;
int DAT_800d240c;
int DAT_800d2410;
int DAT_800d2414;
CVector operator<<(const CVector &, const int &);
CVector operator+(const CVector &, const CVector &);
CVector operator/(const CVector &, const int &);
int operator==(const CVector &, const CVector &);
CQuat operator*(const CQuat &, const CQuat &);
CQuat Quat_FromXRot(short);
CQuat Quat_FromYRot(short);
CQuat Quat_FromZRot(short);
int Utils_CalcAim(CSVector &, const CVector &, const CVector &);

void CCamera::AI()
{
	{
		int calc = mCalcTripod;
		DAT_800d2048 = mMikeIndex;
		if (calc) {
			mOldTripodPos = mTripodPos;
			if (new_focus)
				mTripodPos = mTripod->mPos;
			else
				mTripodPos = ((mTripod->mPos << 1) + mOldTripodPos) / 3;
		}
	}
	if (mCalcFocus) {
		mOldFocusPos = mFocusPos;
		if (new_focus)
			mFocusPos = mFocus->mPos;
		else
			mFocusPos = ((mFocus->mPos << 1) + mOldFocusPos) / 3;
	}
	if (DAT_800c0a48[0].Select.Pressed) {
		if (DAT_800d2090)
			DAT_800d208c = 1;
		DAT_800d2090 = 0;
	} else {
		DAT_800d2090 = 1;
	}
	if (DAT_800d1728 && DAT_800d208c && DAT_800c0a48[0].Select.Pressed) {
		DAT_800c0a48[1].RightOne.Triggered = 0;
		DAT_800c0a48[1].RightTwo.Triggered = 0;
		DAT_800d2084 = 0;
		DAT_800c0a48[0].LeftTwo.Triggered = 0;
		DAT_800d208c = 0;
		DAT_800c0a48[0].Select.Triggered = 0;
		DAT_800c0a48[0].Start.Triggered = 0;
		DAT_800d2080 ^= 1;
		DAT_800d16fc = DAT_800d2080;
		if (DAT_800d2080) {
			int y = DAT_800d1ffc;
			int d = DAT_800d1ff4;
			int p = DAT_800d1ff8;
			int z = mZoom;
			DAT_800d240c = y;
			DAT_800d2410 = d;
			DAT_800d2414 = p;
			DAT_800d2088 = z;
		}
	}
	if (DAT_800d2080) {
		if (DAT_800c0a48[1].Start.Pressed) {
			DAT_800d1ffc = DAT_800d240c;
			DAT_800d1ff4 = DAT_800d2410;
			DAT_800d1ff8 = DAT_800d2414;
			mZoom = DAT_800d2088;
		}
		if (DAT_800c0a48[0].Square.Pressed)
			mZoom--;
		if (DAT_800c0a48[0].Circle.Pressed)
			mZoom++;
		if (DAT_800c0a48[0].Triangle.Pressed)
			mZoom = 256;
		if (DAT_800c0a48[1].Square.Pressed)
			extra_YRot -= 10;
		if (DAT_800c0a48[1].Circle.Pressed)
			extra_YRot += 10;
		if (DAT_800c0a48[1].Left.Pressed) {
			if (DAT_800c0a48[1].Select.Pressed)
				DAT_800d1ff4 -= 32;
			else
				DAT_800d1ff4 -= 8;
		}
		if (DAT_800c0a48[1].Right.Pressed) {
			if (DAT_800c0a48[1].Select.Pressed)
				DAT_800d1ff4 += 32;
			else
				DAT_800d1ff4 += 8;
		}
		if (DAT_800c0a48[1].Up.Pressed) {
			if (DAT_800c0a48[1].Select.Pressed)
				DAT_800d1ff8 -= 32;
			else
				DAT_800d1ff8 -= 8;
		}
		if (DAT_800c0a48[1].Down.Pressed) {
			if (DAT_800c0a48[1].Select.Pressed)
				DAT_800d1ff8 += 32;
			else
				DAT_800d1ff8 += 8;
		}
		DAT_800d1ff8 &= 4095;
		if (DAT_800c0a48[1].LeftOne.Pressed) {
			if (DAT_800c0a48[1].Select.Pressed)
				DAT_800d1ffc -= 32;
			else
				DAT_800d1ffc -= 8;
		}
		if (DAT_800c0a48[1].LeftTwo.Pressed) {
			if (DAT_800c0a48[1].Select.Pressed)
				DAT_800d1ffc += 32;
			else
				DAT_800d1ffc += 8;
		}
	}
	{
		int dist = DAT_800d1ff4;
		int pitch = DAT_800d1ff8;
		int yoff = DAT_800d1ffc;
		DAT_800c1154.vx = 0;
		DAT_800c1154.vz = 0;
		DAT_800d203c = dist;
		DAT_800d2038 = pitch;
		DAT_800c1154.vy = yoff << 12;
	}
	if (DAT_800d140c) {
		if (DAT_800d2080) {
			CM_Normal();
			MoveToDesiredPos(311);
		}
	} else {
		mTimer++;
		if (mZoomTime) {
			mZoomTime--;
			mZoom += mZoomIncrement;
		}
		DAT_800d2178->mZoom = mZoom;
		Utils_CalcAim(mAngles, mPos, mFocusPos);
		if (mTripod->m8fe && mTripodPosYDamper) {
			if (mTripod->mVelY < 0)
				jump_uptimer++;
			else
				jump_uptimer--;
			jump_acc += (-mTripod->mVelY >> 12) * mTripodPosYDamper;
			if (jump_uptimer > 0)
				mTripodPos.vy += jump_acc;
		} else {
			jump_acc = 0;
			jump_uptimer = 0;
		}
		short damp = mPitchDamper;
		if (damp) {
			int vy = mTripod->mVelY;
			if (vy < 0)
				DAT_800d2038 -= damp;
			if (vy > 0)
				DAT_800d2038 -= damp >> 1;
			DAT_800d2038 &= 4095;
		}
		switch (mCameraMode) {
		case 1:
			CM_Normal();
			break;
		case 2:
			CM_NoBigAir();
			break;
		case 23:
			CM_CompetitionIntro();
			goto Done;
		}
		if (mTripod->m358)
			MoveToDesiredPos(311);
		else if (mTripodPos == mOldTripodPos)
			MoveToDesiredPos(151);
		else if (mSpeed < 4)
			MoveToDesiredPos(151);
		else if (mTripod->m734 == 1) {
			if (mTimer < 18)
				MoveToDesiredPos(311);
			else
				MoveToDesiredPos(151);
		} else
			MoveToDesiredPos(311);
		Utils_CalcAim(mAngles, mPos, mFocusPos);
		if (mShakeAmplitude.vx || *(int *)&mShakeAmplitude.vy) {
			mO = Quat_FromYRot(mShakeAmplitude.vy * SIN(mShakeSpeed.vy * DAT_800d16e4) / 4096) * mO
				* Quat_FromXRot(mShakeAmplitude.vx * SIN(mShakeSpeed.vx * DAT_800d16e4) / 4096)
				* Quat_FromZRot(mShakeAmplitude.vz * SIN(mShakeSpeed.vz * DAT_800d16e4) / 4096);
			{
				CSVector oldamp = mShakeAmplitude;
				if (mShakeAmplitude.vx < 0)
					mShakeAmplitude.vx += mShakeDecay.x;
				else
					mShakeAmplitude.vx -= mShakeDecay.x;
				if (mShakeAmplitude.vy < 0)
					mShakeAmplitude.vy += mShakeDecay.y;
				else
					mShakeAmplitude.vy -= mShakeDecay.y;
				if (mShakeAmplitude.vz < 0)
					mShakeAmplitude.vz += mShakeDecay.z;
				else
					mShakeAmplitude.vz -= mShakeDecay.z;
				if (((ushort)oldamp.vx ^ (ushort)mShakeAmplitude.vx) & 0x8000)
					mShakeAmplitude.vx = 0;
				if (((ushort)oldamp.vy ^ (ushort)mShakeAmplitude.vy) & 0x8000)
					mShakeAmplitude.vy = 0;
				if (((ushort)oldamp.vz ^ (ushort)mShakeAmplitude.vz) & 0x8000)
					mShakeAmplitude.vz = 0;
			}
		}
	Done:
		LoadIntoMikeCamera();
	}
}
