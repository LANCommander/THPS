/* ExecuteCommand__6CBaddyUs (0x8003fcdc) flags=-fstructure-noalias */
/* C++ (BADDY.CPP). Demo twin; locals and blocks from its MAIN.SYM. Layout by THPS1 offsets.
   The generic baddy script commands: power-ups, labels/gotos and conditionals on flags and
   variables, camera shakes, pulses and signals to nodes, animations, sounds, sparks, FMVs and
   screen flashes. Returns 0 to stop the script for this frame. */
#pragma interface
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
	CVector() {}
	void Zero() { vx = vy = vz = 0; }
};
struct CSVector {
	short vx, vy, vz;
	CSVector() {}
	CSVector(short x, short y, short z) { vx = x; vy = y; vz = z; }
};
struct SLight;
class CItem {
public:
	ushort mFlags;
	ushort mInquiry;
	CVector mPos;
	CSVector mAngles;
	ushort mModel;
	char mDummyFrame;
	uchar mTintIndex;
	uchar mDummyAnim;
	uchar mRegion;
	CItem *mNextItem;
	uint mRGB;
	CSVector mScale;
	uint mTRN;
	CItem *mPreviousItem;
	uint mStoredRGB;
	uchar mPredatorEffectType;
	uchar mPredatorEffectFade;
	ushort mType;
	SLight *mpLight;
	ushort mFlashTimer;
	short mFlash_dR;
	short mFlash_dG;
	short mFlash_dB;
	virtual ~CItem();
	virtual void Virtual2();
	virtual void AI();
	virtual void Virtual4();
	virtual void Virtual5();
	virtual void Virtual6();
	virtual void Virtual7();
	virtual int Virtual8();
	virtual void SetVariable(ushort);
	virtual short GetVariable(ushort);
	void InitItem(char *);
	void Hide() { mFlags &= ~1; }
	void Show() { mFlags |= 0x41; }
};
class CBody : public CItem {
public:
	char pad4c[0x6c - 0x4c];
	CVector mVel;            /* 0x6c */
	char pad78[0xe2 - 0x78];
	ushort mNodeId;          /* 0xe2 */
	char pade4[0x110 - 0xe4];
};
class CSuper : public CBody {
public:
	char pad110[0x198 - 0x110];
	void CycleAnim(int, signed char);
	void RunAnim(int, int, int, int);
};
class CBruce;
class CBaddy : public CSuper {
public:
	uint mMode;                         /* 0x198 */
	uchar mDoScript;                    /* 0x19c */
	uchar mReadHooks;
	uchar mApplyGravity;
	uchar mHit;
	uchar mInputSignal;
	uchar mDeathPulseSent;
	uchar mComplexSurfaceInterval;      /* 0x1a2 */
	uchar mComplexSurfaceTimer;         /* 0x1a3 */
	ushort mInputFlagsCopy;             /* 0x1a4 */
	ushort mSubType;
	ushort mVerticalCompliance;
	uint mSpecificFlags;                /* 0x1ac */
	ushort *mpScript;                   /* 0x1b0 */
	ushort *mpScriptLabel[8];           /* 0x1b4 */
	ushort mBaddyAttributes[6];         /* 0x1d4 */
	ushort *mpWeaponAttributes;         /* 0x1e0 */
	uchar mWeapons;
	uchar mAttributesPerWeapon;
	uchar mCollisionOn;
	short mGroundToOrigin;
	short mOriginToEye;
	short mRegister[6];
	ushort mPattern;
	ushort mSubPattern;
	ushort mWaitTimer;                  /* 0x1fc */
	uint mDeadChecksum;
	CVector mTargetPos;
	uint mLoopingSound;
	int mLoopingSoundUpdate;
	CBruce *mpCreatedByPlayer;          /* 0x218 */
	int ExecuteCommand(ushort command);
	int GetScriptValue();
	void SkipToEndif();
	void StopScript() { mDoScript = 0; }
};
class CPowerUp {
public:
	void SetGravity(int, int);
};
enum EShakeType { SHAKE_0, SHAKE_1, SHAKE_2 };
class CCamera {
public:
	void Shake(const CVector &, EShakeType);
};
class CBit {
public:
	char pad0[0x42];
	uchar mKeep;                /* 0x42 */
	char pad43;
	virtual ~CBit();
	static void *operator new(uint) throw();
};
class CSpark : public CBit {
public:
	char pad48[92 - 0x48];
	CSpark(CVector &, int, int, int);
};
struct SLevel {
	char pad0[0x60];
	int f60;
	char pad64[120 - 0x64];
};

extern CVector DAT_800a824c;
extern CBruce *DAT_800d19a4;
extern int DAT_800d16f0;
extern int DAT_800d16f4;
extern int DAT_800d1768;
extern CCamera *DAT_800d2044;
extern int DAT_800d16a4;
extern int DAT_800d1780;
extern int DAT_800d1e28;
extern SLevel DAT_800a5398[];
CBody *DAT_800d1998;
extern CBody *DAT_800d19b0 __attribute__((section(".data")));
extern int DAT_800bf318[];
extern int DAT_800d1868;
extern int DAT_800d186c;

CPowerUp *PowerUp_Create(ushort, const CVector &, uint, int, CVector &);
ushort *Trig_GetPosition(CVector &, int);
ushort *Trig_GetLinksPointer(int);
void Trig_SendPulse(ushort *);
void SendSignalToLinks(ushort *);
void SendSignalToNode(CBody *, int);
int Career_Got(int);
void SFX_MIDIFadeIn(int);
void SFX_MIDIFadeOut(int);
void SFX_PlayX(uint, short, int);
void SFX_PlayPos(uint, const CVector &, int);
void GameFMV_StartFMV(int);
void GameFMV_StopFMV();
void Bit_SetSparkTrajectory(const CSVector &);
void Bit_SetSparkTrajectoryCone(const CSVector &);
void Bit_SetSparkSize(uint);
void Bit_SetSparkRGB(uchar, uchar, uchar);
void Bit_SetSparkFadeRGB(uchar, uchar, uchar);
int Mem_GetFree(char);
void Flash_Screen(uchar, uchar, uchar, int, uchar, int);
extern "C" {
void FUN_80023168(int);
void FUN_800229ec(int);
void FUN_80022aec(CVector *);
void FUN_80023260();
void FUN_80045538(int);
void FUN_8006e454(int);
}

int CBaddy::ExecuteCommand(ushort command)
{
	switch (command) {
	case 17056: {
		ushort type = *mpScript++;
		int gravity;
		CPowerUp *p_powerup;
		if (type & 0x2000)
			type = GetVariable(type);
		uint a = *mpScript++;
		int b = *mpScript++;
		gravity = *mpScript++;
		p_powerup = PowerUp_Create(type, mPos, a, b, DAT_800a824c);
		if (p_powerup)
			p_powerup->SetGravity(gravity << 12, 5);
		break;
	}
	case 17054:
		if (mpCreatedByPlayer) {
			if (mpCreatedByPlayer == DAT_800d19a4) {
				DAT_800d16f0 = mPos.vy;
				break;
			}
			DAT_800d16f4 = mPos.vy;
			break;
		}
		DAT_800d16f0 = mPos.vy;
		DAT_800d16f4 = mPos.vy;
		break;
	case 17058:
		DAT_800d1768 = *mpScript++;
		break;
	case 17050:
	case 17062: {
		CVector pos;
		if (command == 17050) {
			ushort node = *mpScript++;
			if (node & 0x2000)
				node = GetVariable(node);
			Trig_GetPosition(pos, node);
		} else {
			pos = mPos;
		}
		switch (*mpScript++) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			GetScriptValue();
			mpScript += 2;
			break;
		}
		break;
	}
	case 16935: {
		ushort v = *mpScript++;
		if (v) {
			mComplexSurfaceInterval = v;
			mComplexSurfaceTimer = 0;
			mSpecificFlags |= 2;
		} else {
			mSpecificFlags &= ~2;
		}
		break;
	}
	case 17048: {
		ushort shake = *mpScript++;
		if (shake & 0x2000)
			shake = GetVariable(shake);
		if (DAT_800d2044) {
			if (shake == 0)
				DAT_800d2044->Shake(mPos, SHAKE_2);
			else if (shake == 1)
				DAT_800d2044->Shake(mPos, SHAKE_1);
			else
				DAT_800d2044->Shake(mPos, SHAKE_0);
		}
		break;
	}
	case 17046:
		SFX_MIDIFadeIn(*mpScript++);
		break;
	case 17047:
		SFX_MIDIFadeOut(*mpScript++);
		break;
	case 17049:
		FUN_80023168(*mpScript++);
		break;
	case 17043: {
		int *p = (int *)(((int)mpScript + 3) & ~3);
		FUN_800229ec(*p++);
		mpScript = (ushort *)p;
		break;
	}
	case 17044: {
		CVector pos;
		FUN_80022aec(&mPos);
		ushort *p_links = Trig_GetLinksPointer(mNodeId);
		for (int i = 0; i < *p_links; i++) {
			Trig_GetPosition(pos, p_links[i + 1]);
			FUN_80022aec(&mPos);
		}
		if (DAT_800d16a4 == 7)
			break;
		GameFMV_StartFMV(DAT_800d1780 == 1 && DAT_800a5398[DAT_800d1e28].f60);
		break;
	}
	case 17053:
		FUN_80022aec(&mPos);
		FUN_80023260();
		break;
	case 17045:
		GameFMV_StopFMV();
		break;
	case 17073:
	case 17074: {
		ushort node = *mpScript++;
		ushort *p_links;
		if (node & 0x2000)
			node = GetVariable(node);
		p_links = Trig_GetLinksPointer(node);
		if (command == 17073) {
			SendSignalToLinks(p_links);
			break;
		}
		Trig_SendPulse(p_links);
		break;
	}
	case 17075:
	case 17076: {
		ushort node = *mpScript++;
		if (node & 0x2000)
			node = GetVariable(node);
		if (command == 17075) {
			SendSignalToNode(DAT_800d1998, node);
			SendSignalToNode(DAT_800d19b0, node);
			break;
		}
		FUN_80045538(node);
		break;
	}
	case 17088: {
		ushort goals = *mpScript++;
		if (DAT_800d16a4 == 1 && !Career_Got(1)) {
			int ok = DAT_800bf318[0] != 2;
			if (ok)
				FUN_8006e454(goals);
		}
		break;
	}
	case 17072: {
		char *p_string = (char *)mpScript;
		while (*p_string)
			p_string++;
		if ((int)p_string & 1)
			mpScript = (ushort *)(p_string + 1);
		else
			mpScript = (ushort *)(p_string + 2);
		break;
	}
	case 16934:
		mVel.Zero();
		break;
	case 16896: {
		InitItem((char *)mpScript);
		char *p_string = (char *)mpScript;
		while (*p_string)
			p_string++;
		if ((int)p_string & 1)
			mpScript = (ushort *)(p_string + 1);
		else
			mpScript = (ushort *)(p_string + 2);
		break;
	}
	case 16646: {
		ushort node = *mpScript++;
		ushort *pNode;
		CVector dummy;
		if (node & 0x2000)
			node = GetVariable(node);
		pNode = Trig_GetPosition(dummy, node);
		mpScript = pNode + 3;
		break;
	}
	case 16644: {
		ushort label = *mpScript++;
		mpScriptLabel[label] = mpScript;
		break;
	}
	case 16645: {
		ushort *p_return = mpScript;
		while (*mpScript != 16640) {
			if (*mpScript++ == 16644) {
				ushort label = *mpScript++;
				mpScriptLabel[label] = mpScript;
			}
		}
		mpScript = p_return;
		break;
	}
	case 16641: {
		ushort label = *mpScript++;
		mpScript = mpScriptLabel[label];
		break;
	}
	case 16642: {
		ushort label = *mpScript++;
		mpScript = mpScriptLabel[label];
		return 0;
	}
	case 16662:
		if (!(mSpecificFlags & *mpScript++))
			break;
		SkipToEndif();
		break;
	case 16661: {
		ushort f = *mpScript++;
		if ((mSpecificFlags & f) == f)
			break;
		SkipToEndif();
		break;
	}
	case 16656:
	case 16657: {
		ushort dummy_script[8];
		int dummy_script_index = 0;
		int var_id = *mpScript++;
		ushort *p_start = mpScript;
		int v0 = GetVariable(var_id);
		int v1;
		while (p_start != mpScript)
			dummy_script[dummy_script_index++] = *p_start++;
		v1 = *mpScript++;
		if (v1 & 0x2000)
			v1 = GetVariable(v1);
		dummy_script[dummy_script_index] = (command == 16656) ? v0 + v1 : v0 - v1;
		p_start = mpScript;
		mpScript = dummy_script;
		SetVariable(var_id);
		mpScript = p_start;
		break;
	}
	case 16658: {
		int v0 = *mpScript++;
		int v1;
		if (v0 & 0x2000)
			v0 = GetVariable(v0);
		v1 = *mpScript++;
		if (v1 & 0x2000)
			v1 = GetVariable(v1);
		if (v1 < v0)
			break;
		SkipToEndif();
		break;
	}
	case 16659: {
		int v0 = *mpScript++;
		int v1;
		if (v0 & 0x2000)
			v0 = GetVariable(v0);
		v1 = *mpScript++;
		if (v1 & 0x2000)
			v1 = GetVariable(v1);
		if (v0 < v1)
			break;
		SkipToEndif();
		break;
	}
	case 16660: {
		int v0 = *mpScript++;
		int v1;
		if (v0 & 0x2000)
			v0 = GetVariable(v0);
		v1 = *mpScript++;
		if (v1 & 0x2000)
			v1 = GetVariable(v1);
		if (v0 == v1)
			break;
		SkipToEndif();
		break;
	}
	case 17024:
		mWaitTimer = *mpScript++;
		if (mWaitTimer & 0x2000)
			mWaitTimer = GetVariable(mWaitTimer);
		return 0;
	case 17025:
		if (mInputFlagsCopy & 1)
			break;
		mpScript--;
		return 0;
	case 16960:
		StopScript();
	case 16647:
		return 0;
	case 16897: {
		int anim = *mpScript++;
		int dir = *mpScript++;
		CycleAnim(anim, dir);
		break;
	}
	case 16898:
		RunAnim(*mpScript++, 0, -1, -1);
		break;
	case 16899:
		Hide();
		break;
	case 16900:
		Show();
		break;
	case 16901:
		Virtual2();
		break;
	case 17040:
		SFX_PlayX((short)*mpScript++, 0x2000, 0);
		break;
	case 17041:
		SFX_PlayPos((short)*mpScript++, mPos, 0);
		break;
	case 17042: {
		ushort sparks = *mpScript++;
		if (DAT_800d1868 < 200) {
			Bit_SetSparkTrajectory(mAngles);
			CSVector cone(512, 4096, 0);
			Bit_SetSparkTrajectoryCone(cone);
			Bit_SetSparkSize(1);
			Bit_SetSparkRGB(128, 128, 128);
			Bit_SetSparkFadeRGB(4, 4, 4);
			DAT_800d186c = 0;
			for (int i = 0; i < sparks; i++) {
				if (Mem_GetFree(1) > 10000)
					new CSpark(mPos, 32, 0x2000, 32);
			}
			DAT_800d186c = 1;
		}
		break;
	}
	case 17052:
		Flash_Screen(mpScript[0], mpScript[1], mpScript[2], mpScript[3], 0, mpScript[4]);
		mpScript += 5;
		break;
	/* 16768 and 17152 are invisible (same target as default); casetree.py fit. 17152 widens the
	   range past 10x the node count, so the switch stays a compare tree rather than a jump table. */
	case 16768:
	case 17059:
	case 17152:
		break;
	}
	return 1;
}
