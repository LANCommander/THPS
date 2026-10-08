/* __5CBody (0x800437d4) */
#pragma interface

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

struct CSVector {
	short vx, vy, vz;
	void Set(short x, short y, short z) {
		vx = x;
		vy = y;
		vz = z;
	}
};

struct CFriction {
	uchar x, y, z;
	CFriction() {
		x = 1;
		y = 1;
		z = 1;
	}
	void Set(uchar a, uchar b, uchar c) {
		x = a;
		y = b;
		z = c;
	}
};

struct SLight;
struct CGlow;
struct STapeMessage;

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
	CItem();
	virtual ~CItem();
	void InitItem(char *);
};

class CBody : public CItem {
  public:
	char pad4c[0x52 - 0x4c];
	ushort mCBodyFlags; /* 0x52 */
	char pad54[0x85 - 0x54];
	CFriction mFric; /* 0x85 */
	char pad88[0x94 - 0x88];
	CFriction mAngFric; /* 0x94 */
	char pad97;
	short m98; /* 0x98 */
	char pad9a[0xd4 - 0x9a];
	ushort mShadowScale; /* 0xd4 */
	short mShadowDist;
	short mShadowThreshold; /* 0xd8 */
	int mPushVal;           /* 0xdc */
	ushort mRMinor;         /* 0xe0 */
	ushort mNode;           /* 0xe2 */
	char pade4[0x134 - 0xe4];
	CBody();
	virtual ~CBody();
};

CBody::CBody() {
	mPushVal = 10;
	m98 = 0;
	mNode = 0xffff;
	mShadowScale = 50;
	mShadowThreshold = 300;
	mCBodyFlags |= 18;
	mRMinor = 50;
}
