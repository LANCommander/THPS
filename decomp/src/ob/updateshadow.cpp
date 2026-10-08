/* UpdateShadow__5CBody (0x80043b50) */
/* C++ (OB.CPP). Exact demo twin; written from its MAIN.SYM (up/trans in the flag block). The
   null-checked new is spelled out as the CBit pool allocator plus the CQuadBit ctor (cf. BloodSplat). */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
}

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

struct CSVector {
	short vx, vy, vz;
};

extern int UseCacheForBits;
extern char ShadowTextureName[];

struct CBit {
	char pad0[0x40];
	ushort mFrigDeltaZ;
	uchar mProtected;
	uchar mType;
};

struct CQuadBit : CBit {
	char pad44[0x9c - 0x44];
	void SetTexture(char *, int);
	void FlagOn(uchar);
	void SetSemiTransparent();
	void OrientUsing(const CVector &, const SVECTOR &, int, int, int);
	void SetTransparency(uchar);
};

extern "C" {
	void *__nw__4CBitUi(unsigned int);
	CQuadBit *CQuadBit_ctor(CQuadBit *);
}

struct CBody {
	char pad0[0x52];
	ushort mCBodyFlags;
	char pad54[0xbc - 0x54];
	CVector mShadowPos;
	CSVector mShadowNormal;
	CQuadBit *mpShadow;
	ushort mShadowScale;
	short mShadowDist;
	short mShadowThreshold;
	void KillShadow();
	void UpdateShadow();
};

void CBody::UpdateShadow() {
	if (mCBodyFlags & 8) {
		SVECTOR up;
		int trans;

		if (!mpShadow) {
			UseCacheForBits = 0;
			CQuadBit *p = (CQuadBit *)__nw__4CBitUi(sizeof(CQuadBit));

			if (p)
				p = CQuadBit_ctor(p);

			mpShadow = p;
			UseCacheForBits = 1;
			p->SetTexture(ShadowTextureName, 0);
			mpShadow->FlagOn(4);
			mpShadow->SetSemiTransparent();

			mpShadow->mFrigDeltaZ = 32;
			mpShadow->mProtected = 1;
		}

		if (mShadowNormal.vy < -128) {
			up.vx = mShadowNormal.vx;
			up.vy = mShadowNormal.vy;
			up.vz = mShadowNormal.vz;
			mpShadow->OrientUsing(mShadowPos, up, mShadowScale, mShadowScale, 0);
		}

		trans = ((mShadowThreshold - mShadowDist) << 7) / mShadowThreshold;

		if (trans < 0)
			trans = 0;

		trans /= 6;
		mpShadow->SetTransparency(trans);
	} else {
		KillShadow();
	}
}
