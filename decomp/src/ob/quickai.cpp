/* Ob_QuickAI__FPP5CBody (0x80044620) */
/* C++ (OB.CPP). Fuzzy demo twin; locals from its MAIN.SYM. Runs AI on every body in the list;
   bodies flagged 0x40 are deleted on the second pass (0x80 marks the first). */
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
};

class CBody : public CItem {
  public:
	char pad4c[0x52 - 0x4c];
	ushort mCBodyFlags; /* 0x52 */
};

void Ob_QuickAI(CBody **ppBody) {
	CBody *pBody;
	CBody *pNext;

	/* the exit test loads pNext (probably a list-walk macro), so cc1 can't rotate it into a
	   simple bottom test and `delete` keeps its null check */
	for (pBody = *ppBody; pBody ? (pNext = (CBody *)pBody->mNextItem, 1) : 0; pBody = pNext) {
		if (pBody->mCBodyFlags & 0x40) {
			if (pBody->mCBodyFlags & 0x80)
				delete pBody;
			else
				pBody->mCBodyFlags |= 0x80;
		} else {
			pBody->AI();
		}
	}
}
