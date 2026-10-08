/* ParseScript__6CBaddyPUs (0x8003fc1c) */
/* C++ (BADDY.CPP). Demo twin; locals from its MAIN.SYM. Runs script commands until the end marker:
   0x4000 commands go to ExecuteCommand (stopping the parse if it returns 0), 0x2000 ones to another
   virtual; both take the command word (still in a1, which is why retail keeps it there). */
#pragma interface

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

struct CSVector {
	short vx, vy, vz;
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
	virtual int ExecuteCommand(ushort);
	virtual void HandleCommand(ushort); /* slot 9; name unknown */
	virtual int GetNode(ushort);
};

class CBody : public CItem {
  public:
	char pad4c[0xe2 - 0x4c];
	short mNodeId; /* 0xe2 */
	short mE4;
	short mE6;
};

class CBaddy : public CBody {
  public:
	char pade8[0x19c - 0xe8];
	uchar mDoScript; /* 0x19c */
	char pad19d[0x1b0 - 0x19d];
	ushort *mpScript; /* 0x1b0 */
	void ParseScript(ushort *p_script);
};

void CBaddy::ParseScript(ushort *p_script) {
	mpScript = p_script;

	while (*mpScript != 0x4100) {
		ushort command = *mpScript++;

		if (command & 0x4000) {
			if (!ExecuteCommand(command))
				return;
		} else if (command & 0x2000) {
			HandleCommand(command);
		}
	}

	mDoScript = 0;
}
