/* ExecuteCommand__9CPlatformUs (0x8003ec48) */
/* C++ (PLATFORM.CPP). Fuzzy demo twin (0.99); locals from its MAIN.SYM. Platform script commands:
   bounding size, visibility, looping sounds, scale and spin rates per axis, collision radius,
   moves to absolute/relative/node positions, and shattering. Anything else goes to the baddy
   command handler. */
#pragma interface
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
struct CVector {
	int vx, vy, vz;
	CVector &operator<<=(const int &);
	CVector &operator+=(const CVector &);
};
struct SModel {
	char pad0[12];
	ushort Box[6];            /* 12 */
};
struct SPSXRegion {
	char pad0[16];
	SModel **pModels;         /* 0x10 */
	char pad14[64 - 0x14];
};
struct Item;
class CItem {
public:
	ushort mFlags;            /* 0x00 */
	ushort mInquiry;
	CVector mPos;             /* 0x04 */
	short mAngles[3];         /* 0x10 */
	ushort mModel;            /* 0x16 */
	char mDummyFrame;
	uchar mTintIndex;
	uchar mDummyAnim;
	uchar mRegion;            /* 0x1b */
	CItem *mNextItem;         /* 0x1c */
	uint mRGB;
	ushort mScale[3];         /* 0x24 */
	char pad2a[0x48 - 0x2a];
	virtual ~CItem();
	virtual void Virtual2();
	virtual void AI();
	virtual void Virtual4();
	virtual void Virtual5();
	virtual void Virtual6();
	virtual void Virtual7();
	virtual void Virtual8();
	virtual void Virtual9();
	virtual int GetNode(ushort);
};
class CBody : public CItem {
public:
	char pad4c[0x1ac - 0x4c];
	uint m1AC;                /* 0x1ac */
	ushort *pScript;          /* 0x1b0 */
};
class CBaddy : public CBody {
public:
	char pad1b4[0x21c - 0x1b4];
	int ExecuteCommand(ushort command);
};
class CBruce {
public:
	char pad0[0x868];
	CItem *m868;              /* 0x868 */
};
class CPlatform : public CBaddy {
public:
	ushort mScaleTime[3];     /* 0x21c */
	ushort mScaleRate[3];     /* 0x222 */
	ushort mRadius;           /* 0x228 */
	char pad22a[0x22c - 0x22a];
	ushort mVisible;          /* 0x22c */
	ushort mSize[3];          /* 0x22e */
	char pad234[0x23c - 0x234];
	int m23C;                 /* 0x23c */
	char pad240[0x244 - 0x240];
	uint mSound;              /* 0x244 */
	int mSoundId;             /* 0x248 */
	int mSpin[3];             /* 0x24c */
	int ExecuteCommand(ushort command);
	void MoveTo(CVector &);
};
extern SPSXRegion DAT_800bf7a8[];
extern CBruce *DAT_800d19a4;
void SFX_Stop(uint);
ushort *Trig_GetPosition(CVector &, int);
void Shatter_Item(Item *, int, int);
extern "C" {
int FUN_8004b250(int, short, int);
int FUN_8004b464(int, const CVector &, int);
}

int CPlatform::ExecuteCommand(ushort command)
{
	switch (command) {
	case 17161: {
		SModel *m;
		ushort *pBox;
		ushort v = *pScript++;
		mVisible = v;
		if (v)
			m1AC |= 16;
		else
			m1AC &= ~16;
		m = DAT_800bf7a8[mRegion].pModels[mModel];
		pBox = m->Box;
		mSize[0] = pBox[0] - pBox[1];
		mSize[1] = pBox[2] - pBox[3];
		mSize[2] = pBox[4] - pBox[5];
		break;
	}
	case 17157:
		if (*pScript++)
			mFlags |= 8;
		else
			mFlags &= ~8;
		break;
	case 17671:
		if (mSound)
			SFX_Stop(mSound);
		mSound = FUN_8004b250(*pScript++, 0x2000, 0);
		mSoundId = -1;
		break;
	case 17672: {
		int id;
		if (mSound)
			SFX_Stop(mSound);
		id = *pScript++;
		mSoundId = *pScript++;
		mSound = FUN_8004b464(id, mPos, 0);
		break;
	}
	case 17673:
		if (mSound)
			SFX_Stop(mSound);
		mSound = 0;
		break;
	case 17156: {
		short p;
		if (!(mFlags & 0x200)) {
			mFlags |= 0x200;
			mScale[0] = mScale[1] = mScale[2] = 4096;
		}
		p = *pScript++;
		mScaleTime[0] = mScaleTime[1] = mScaleTime[2] = *pScript++;
		if (mScaleTime[0])
			mScaleRate[1] = mScaleRate[2] = mScaleRate[0] = (p << 12) / (mScaleTime[0] * 100);
		else
			mScaleRate[1] = mScaleRate[2] = mScaleRate[0] = (p << 12) / 100;
		mScale[0] += mScaleRate[0];
		mScale[1] += mScaleRate[1];
		mScale[2] += mScaleRate[2];
		break;
	}
	case 17158: {
		short p;
		if (!(mFlags & 0x200)) {
			mFlags |= 0x200;
			mScale[0] = mScale[1] = mScale[2] = 4096;
		}
		p = *pScript++;
		mScaleTime[0] = *pScript++;
		if (mScaleTime[0])
			mScaleRate[0] = (p << 12) / (mScaleTime[0] * 100);
		else
			mScaleRate[0] = (p << 12) / 100;
		mScale[0] += mScaleRate[0];
		break;
	}
	case 17159: {
		short p;
		if (!(mFlags & 0x200)) {
			mFlags |= 0x200;
			mScale[0] = mScale[1] = mScale[2] = 4096;
		}
		p = *pScript++;
		mScaleTime[1] = *pScript++;
		if (mScaleTime[1])
			mScaleRate[1] = (p << 12) / (mScaleTime[1] * 100);
		else
			mScaleRate[1] = (p << 12) / 100;
		mScale[1] += mScaleRate[1];
		break;
	}
	case 17160: {
		short p;
		if (!(mFlags & 0x200)) {
			mFlags |= 0x200;
			mScale[0] = mScale[1] = mScale[2] = 4096;
		}
		p = *pScript++;
		mScaleTime[2] = *pScript++;
		if (mScaleTime[2])
			mScaleRate[2] = (p << 12) / (mScaleTime[2] * 100);
		else
			mScaleRate[2] = (p << 12) / 100;
		mScale[2] += mScaleRate[2];
		break;
	}
	case 17155:
		mRadius = *pScript++;
		break;
	case 17154: {
		int x = *pScript++;
		int y = *pScript++;
		int z = *pScript++;
		m1AC |= 4;
		mSpin[0] = x << 11;
		mSpin[1] = y << 11;
		mSpin[2] = z << 11;
		break;
	}
	case 17152:
		if (m23C)
			return 1;
		pScript--;
		return 0;
	case 16928: {
		int *p_pos;
		CVector pos;
		p_pos = (int *)(((int)pScript + 3) & ~3);
		pos.vx = *p_pos++;
		pos.vy = *p_pos++;
		pos.vz = *p_pos++;
		pos <<= 12;
		pScript = (ushort *)p_pos;
		MoveTo(pos);
		break;
	}
	case 16929: {
		ushort node = *pScript++;
		CVector pos;
		if (node & 0x2000)
			node = GetNode(node);
		Trig_GetPosition(pos, node);
		MoveTo(pos);
		return 1;
	}
	case 16930: {
		int *p_pos;
		CVector pos;
		p_pos = (int *)(((int)pScript + 3) & ~3);
		pos.vx = *p_pos++;
		pos.vy = *p_pos++;
		pos.vz = *p_pos++;
		pos <<= 12;
		pos += mPos;
		pScript = (ushort *)p_pos;
		MoveTo(pos);
		break;
	}
	case 16901:
		Virtual2();
		return 0;
	case 17153:
		if (DAT_800d19a4->m868 == this)
			DAT_800d19a4->m868 = 0;
		mFlags |= 1;
		Virtual2();
		Shatter_Item((Item *)this, 0, 0);
		return 0;
	default:
		return CBaddy::ExecuteCommand(command);
	}
	return 1;
}
