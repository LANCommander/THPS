/* GetVariable__6CBaddyUs (0x80040f50) */
/* C++ (BADDY.CPP). Fuzzy demo twin (0.74); locals from its MAIN.SYM. Reads a script variable:
   distance to / line of sight to the skater, positions (>> 12), counters, and script operands. */
#pragma interface
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;
struct CVector { int vx, vy, vz; };
struct CSVector { short vx, vy, vz; };
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
	virtual void Virtual8();
	virtual void Virtual9();
	virtual int GetNode(ushort);
};

class CBody : public CItem {
public:
	char pad4c[0xe2 - 0x4c];
	short mNodeId;          /* 0xe2 */
	short mE4;
	short mE6;              /* 0xe6 */
};
class CBaddy : public CBody {
public:
	char pade8[0x19f - 0xe8];
	uchar m19F;             /* 0x19f */
	uchar m1A0;             /* 0x1a0 */
	char pad1a1[0x1a8 - 0x1a1];
	short m1A8;             /* 0x1a8 */
	char pad1aa[0x1b0 - 0x1aa];
	ushort *pScript;        /* 0x1b0 */
	char pad1b4[0x1ea - 0x1b4];
	short mEyeHeight;       /* 0x1ea */
	short mVars[8];         /* 0x1ec */
	short GetVariable(ushort variable);
};
class CBruce : public CItem {
};
extern short DAT_800d1654;
extern CBruce *DAT_800d19a4;
uint Utils_XZDist(const CVector &, const CVector &);
int Utils_LineOfSight(const CVector &, const CVector &);
int Redbook_Rnd(int);
ushort *Trig_GetLinksPointer(int);

short CBaddy::GetVariable(ushort variable)
{
	switch (variable) {
	case 0x2136:
		return DAT_800d1654;
	case 0x2132:
		if (DAT_800d19a4) {
			uint dist = Utils_XZDist(mPos, DAT_800d19a4->mPos);
			if (dist >= 0x2000)
				dist = 0x1fff;
			return dist;
		}
		return 0x1fff;
	case 0x2133:
		if (DAT_800d19a4) {
			CVector eye_pos = mPos;
			eye_pos.vy -= mEyeHeight << 12;
			return Utils_LineOfSight(eye_pos, DAT_800d19a4->mPos);
		}
		break;
	case 0x212e:
		return m1A8;
	case 0x212c:
		return m1A0;
	case 0x212d:
		return m19F;
	case 0x2140:
		return mPos.vx >> 12;
	case 0x2141:
		return mPos.vy >> 12;
	case 0x2142:
		return mPos.vz >> 12;
	case 0x2150:
		if (DAT_800d19a4)
			return DAT_800d19a4->mPos.vx >> 12;
		break;
	case 0x2151:
		if (DAT_800d19a4)
			return DAT_800d19a4->mPos.vy >> 12;
		break;
	case 0x2152:
		if (DAT_800d19a4)
			return DAT_800d19a4->mPos.vz >> 12;
		break;
	case 0x2100:
		return mE6;
	case 0x2129:
		return Redbook_Rnd(*pScript++);
	case 0x2120: {
		uchar i = *(uchar *)pScript;
		pScript++;
		return mVars[i];
	}
	case 0x212a:
		return mNodeId;
	case 0x212b: {
		ushort node = *pScript++;
		ushort *p_links;
		if (node & 0x2000)
			node = GetNode(node);
		p_links = Trig_GetLinksPointer(node);
		if (*p_links)
			return p_links[1];
		break;
	}
	}
	return 0;
}
