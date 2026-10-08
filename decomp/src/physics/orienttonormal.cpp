/* OrientToNormal__6CBruce (0x8003b0c0) */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

struct CVector {
	int x, y, z;
	void Set(int px, int py, int pz) {
		x = px;
		y = py;
		z = pz;
	}
};

struct CSVector {
	short x, y, z;
};

void M3dUtils_NormaliseVector(CVector *);

struct CBruce {
	char pad0[0xa8];
	CSVector mNormal;
	char pad1[0x78c - 0xae];
	short m[3][3];
	char pad2[0x7d8 - 0x79e];
	CVector mFront;
	CVector mRight;
	CVector mUp;
	char pad3[0x820 - 0x7fc];
	int mState;
	CVector mOldNormal;
	void OrientToNormal();
};

void CBruce::OrientToNormal() {
	VECTOR z1;
	CVector normal;
	CVector x1;

	if (mState < 25) {
		if (mState == 24) {
			int _x = mNormal.x;
			int _y = mNormal.y;
			int _z = mNormal.z;

			normal.x = _x;
			normal.y = _y;
			normal.z = _z;
		} else {
			normal.x = mOldNormal.x + ((mNormal.x - mOldNormal.x) >> 2);
			normal.y = mOldNormal.y + ((mNormal.y - mOldNormal.y) >> 2);
			normal.z = mOldNormal.z + ((mNormal.z - mOldNormal.z) >> 2);
		}

		M3dUtils_NormaliseVector(&normal);
		mFront.Set(m[0][2], m[1][2], m[2][2]);
		gte_ldopv1(&mFront);
		gte_ldopv2(&normal);
		gte_op12();
		gte_stlvnl(&x1);
		M3dUtils_NormaliseVector(&x1);
		gte_ldopv1(&normal);
		gte_ldopv2(&x1);
		gte_op12();
		gte_stlvnl(&z1);

		m[0][0] = x1.x;
		mRight.x = m[0][0];
		m[1][0] = x1.y;
		mRight.y = m[1][0];
		m[2][0] = x1.z;
		mRight.z = m[2][0];
		m[0][1] = normal.x;
		mUp.x = m[0][1];
		m[1][1] = normal.y;
		mUp.y = m[1][1];
		m[2][1] = normal.z;
		mUp.z = m[2][1];
		m[0][2] = z1.vx;
		mFront.x = m[0][2];
		m[1][2] = z1.vy;
		mFront.y = m[1][2];
		m[2][2] = z1.vz;
		mFront.z = m[2][2];

		{
			int _x = normal.x;
			int _y = normal.y;
			int _z = normal.z;

			mOldNormal.x = _x;
			mOldNormal.y = _y;
			mOldNormal.z = _z;
		}
	}
}
