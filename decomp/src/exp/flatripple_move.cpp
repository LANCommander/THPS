/* Move__11CFlatRipple (0x8004ebf4) */
typedef unsigned char uchar;
typedef unsigned short ushort;
struct CVector { int x, y, z; };
struct TE { short x, y; };
struct SLineSeg {
	CVector End;
	uchar r, g, b, code;
};
extern TE DAT_800c9670[2];
struct CBit {
	char pad[0x18];
	CVector mPos;
	char pad2[0x4c - 0x24];
	void Die();
};
struct CFlatRipple : CBit {
	int mNumSegs;
	SLineSeg *mSegs;
	CVector mStart;
	uchar mR, mG, mB;
	int mMaxRadius;
	int mRadius;
	int mGrowRate;
	int mAngle;
	void Move();
};
void CFlatRipple::Move()
{
	int intensity;
	int a;
	int step;
	mRadius += mGrowRate;
	if (mRadius >= mMaxRadius) {
		mRadius = mMaxRadius;
		Die();
	}
	intensity = ((mMaxRadius - mRadius) << 8) / mMaxRadius;
	a = mAngle;
	step = 4096 / mNumSegs;
	TE *e = &DAT_800c9670[a & 4095];
	mStart.x = mPos.x + (((mRadius * e->y) / 4096) << 12);
	mStart.z = mPos.z + (((mRadius * e->x) / 4096) << 12);
	for (int i = 0; i < mNumSegs; i++) {
		mSegs[i].r = (mR * intensity) >> 8;
		mSegs[i].g = (mG * intensity) >> 8;
		mSegs[i].b = (mB * intensity) >> 8;
		a += step;
		if (i == mNumSegs - 1) {
			mSegs[i].End = mStart;
		} else {
			TE *f = &DAT_800c9670[a & 4095];
			mSegs[i].End.x = mPos.x + (((mRadius * f->y) / 4096) << 12);
			mSegs[i].End.z = mPos.z + (((mRadius * f->x) / 4096) << 12);
		}
	}
}
