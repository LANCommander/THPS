/* FUN_80045774 (0x80045774) */
/* C++ (TRIG). Sends a trigger event to every body in the list whose node id matches: mode 0 runs
   virtual slot 2, mode 1 slot 6 with the body's +0xe6 value. */
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

extern char DAT_800a824c[];

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
	virtual int Virtual6(int, char *, int);
};

class CBody : public CItem {
  public:
	char pad4c[0x52 - 0x4c];
	ushort mCBodyFlags; /* 0x52 */
	char pad54[0xe2 - 0x54];
	ushort mNodeId; /* 0xe2 */
	short mE4;
	short mE6; /* 0xe6 */
};

extern "C" void FUN_80045774(int id, CBody *pBody, int mode) {
	for (; pBody; pBody = (CBody *)pBody->mNextItem) {
		if (pBody->mNodeId != id)
			continue;

		switch (mode) {
			case 0:
				pBody->Virtual2();
				break;
			case 1:
				pBody->Virtual6(pBody->mE6, DAT_800a824c, 0);
				break;
		}
	}
}
