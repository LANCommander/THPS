/* AI__16CScriptOnlyBaddy (0x80041388) */
/* C++ (BADDY.CPP). Fuzzy demo twin; locals and blocks from its MAIN.SYM. Layout by THPS1 offsets. */
typedef unsigned char uchar;
typedef unsigned short ushort;

struct CVector {
	int vx, vy, vz;
	CVector() {}
	CVector(int x, int y, int z) {
		vx = x;
		vy = y;
		vz = z;
	}
	CVector &operator+=(const CVector &);
};

CVector operator-(const CVector &, const CVector &);
CVector operator+(const CVector &, const CVector &);
CVector operator>>(const CVector &, const int &);

struct CGPolyLine {
	char pad[0x4c];
	CVector *pEnd; /* 0x4c */
	CVector Start; /* 0x50 */
};

struct SRainEntry {
	CVector vel;
	CGPolyLine *p_line;
};

struct SSkater {
	char pad[4];
	CVector mPos;
	char pad10[0xc0 - 0x10];
	int yc0;
};

struct SObj {
	char pad[0x6c];
	CVector v6c;
};

struct VT {
	char pad[0x10];
	short off;
	short pad2;
	void (*fn)(char *);
};

class CScriptOnlyBaddy {
  public:
	ushort mFlags;
	ushort mInquiry;
	CVector mPos;
	char p0[0x48 - 0x10];
	VT *vt;
	char p1[0x50 - 0x4c];
	ushort w50;
	char p2[0x19c - 0x52];
	uchar b19c;
	char p3[3];
	uchar b1a0;
	char p4[3];
	ushort w1a4;
	char p5[0x1b0 - 0x1a6];
	int i1b0;
	char p6[0x1fc - 0x1b4];
	ushort w1fc;
	char p7[0x220 - 0x1fe];
	ushort mNumRain; /* 0x220 */
	char p8[2];
	SRainEntry *mpRain; /* 0x224 */
	char p9[0x22c - 0x228];
	unsigned int mLoopingSound; /* 0x22c */
	int mLoopingSoundUpdate;    /* 0x230 */
	int mLoopingSoundVolume;    /* 0x234 */
	void AI();
};

extern int DAT_800d13cc;
extern volatile int DAT_800d16e4;
extern SSkater *DAT_800d19a4;
extern SObj *DAT_800d2044;

extern "C" int FUN_8003fc1c(CScriptOnlyBaddy *, int);
void SFX_ModifyPos(unsigned int, const CVector &, int);
int Rnd(int);

void CScriptOnlyBaddy::AI() {
	mFlags |= 0x41;
	w1a4 = w50;

	if (w50 & 1) {
		w50 &= 0xfffe;
		b1a0++;
	}

	if (b19c) {
		if (w1fc)
			w1fc--;
		else
			FUN_8003fc1c(this, i1b0);
	} else {
		vt->fn((char *)this + vt->off);
	}

	if (mLoopingSoundUpdate != -1 && DAT_800d16e4 % mLoopingSoundUpdate == 0) {
		int t = DAT_800d13cc;
		unsigned int snd = mLoopingSound;

		DAT_800d13cc = t * mLoopingSoundVolume / 100;
		SFX_ModifyPos(snd, mPos, 0);

		DAT_800d13cc = t;
	}

	if (mpRain) {
		int ground = DAT_800d19a4->yc0;

		for (int i = 0; i < mNumRain; i++) {
			SRainEntry *p_entry = &mpRain[i];
			CVector pos = p_entry->p_line->Start;

			pos += p_entry->vel;

			if (ground < pos.vy) {
				CVector offset((Rnd(2400) - 1200) << 12, (Rnd(400) - 1200) << 12,
				               (Rnd(2400) - 1200) << 12);

				pos = DAT_800d19a4->mPos + offset;
			}

			p_entry->p_line->Start = pos;
			*p_entry->p_line->pEnd = (pos - p_entry->vel) + (DAT_800d2044->v6c >> 1);
		}
	}
}
