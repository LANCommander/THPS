/* __7CRibbonRC7CVectoriiPcT4ii (0x80029e28) */
/* C++ (BIT.CPP). Fuzzy demo twin; members and locals from its MAIN.SYM. A real constructor, with the
   parameters left unmodified so the prologue copies them in retail's order. */
typedef unsigned char uchar;
typedef unsigned short ushort;

struct CVector {
	int vx, vy, vz;
};

class CBit {
  public:
	char pad0[0x42];
	uchar mProtected; /* 0x42 */
	uchar mType;
	void *operator new(unsigned int) throw();
	virtual ~CBit();
};

class CNonRenderedBit : public CBit {
  public:
	CNonRenderedBit();
};

class CFT4Bit : public CBit {
  public:
	char pad48[0x58 - 0x48];
	uchar mFlags; /* 0x58 */
	void SetAnim(char *);
};

class CRibbonBit : public CFT4Bit {
  public:
	char pad59[116 - 0x59];
	CRibbonBit();
};

extern "C" void SetScale__7CFT4BitUs(CRibbonBit *, ushort); /* scale */
extern "C" void FUN_800280b0(CRibbonBit *);         /* semi-transparent */

class CRibbon : public CNonRenderedBit {
  public:
	int mNumBits;
	int mPointsPerBit;
	int mNumPoints;
	int mCurrent;
	CVector *mPoints;
	CRibbonBit **mBits;
	CRibbon(const CVector &pos, int numbits, int pointsperbit, char *pMiddleAnimName,
	        char *pEndAnimName, int scale, int semitrans);
	virtual ~CRibbon();
};

void *Mem_New(unsigned int, int, int);

CRibbon::CRibbon(const CVector &pos, int numbits, int pointsperbit, char *pMiddleAnimName,
                 char *pEndAnimName, int scale, int semitrans) {
	mNumBits = numbits;
	mPointsPerBit = pointsperbit - 1;
	mNumPoints = numbits * mPointsPerBit + 1;
	mPoints = (CVector *)Mem_New(mNumPoints * sizeof(CVector), 0, 1);

	{
		int i;

		for (i = 0; i < mNumPoints; i++)
			mPoints[i] = pos;
	}

	{
		int i;

		mBits = (CRibbonBit **)Mem_New(numbits * 4, 0, 1);

		for (i = mNumBits - 1; i >= 0; i--) {
			mBits[i] = new CRibbonBit;
			mBits[i]->mProtected = 1;
			mBits[i]->SetAnim(pMiddleAnimName);
			SetScale__7CFT4BitUs(mBits[i], scale);

			if (semitrans)
				FUN_800280b0(mBits[i]);
		}
	}

	mBits[0]->mFlags |= 16;
	mBits[0]->SetAnim(pEndAnimName);
}
