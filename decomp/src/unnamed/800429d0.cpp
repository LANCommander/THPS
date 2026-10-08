/* FlipToVelocity__6CBruce (0x800429d0) size=224 */
/* C++ (PHYSICS.CPP-style CBruce method): flips the skater about the up axis by negating the
   front and right columns of the rotation matrix. The function finder split it in three
   (0x800429d0, 0x80042a54, 0x80042aa0). */
struct CVector {
	int x, y, z;
};

extern "C" int Mips_CVecDotProd__FP7CVectorT0(CVector *, CVector *);

struct CBruce {
	char pad0[0x6c];
	CVector mVel; /* 0x06c */
	char pad78[0x134 - 0x78];
	int mFlags; /* 0x134 */
	char pad138[0x146 - 0x138];
	unsigned short mState; /* 0x146 */
	char pad148[0x78c - 0x148];
	short m[3][3]; /* 0x78c */
	char pad79e[0x7d8 - 0x79e];
	CVector mFront; /* 0x7d8 */
	CVector mRight; /* 0x7e4 */
	void Flip();
};

void CBruce::Flip() {
	if (mState == 34)
		return;

	if (Mips_CVecDotProd__FP7CVectorT0(&mFront, &mVel) <= 20480)
		return;

	m[0][2] = -mFront.x;
	mFront.x = m[0][2];
	m[1][2] = -mFront.y;
	mFront.y = m[1][2];
	m[2][2] = -mFront.z;
	mFront.z = m[2][2];
	m[0][0] = -mRight.x;
	mRight.x = m[0][0];
	m[1][0] = -mRight.y;
	mRight.y = m[1][0];
	m[2][0] = -mRight.z;
	mRight.z = m[2][0];
	mFlags ^= 2;
}
