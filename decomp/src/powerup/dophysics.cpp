/* DoPhysics__8CPowerUp (0x8001ff84) */
typedef unsigned char uchar;
typedef unsigned short ushort;

struct CFriction {
	uchar x, y, z;
};

struct CVector {
	int x, y, z;
	CVector &operator+=(const CVector &);
	void Set(int px, int py, int pz) {
		x = px;
		y = py;
		z = pz;
	}
};

struct CSVector {
	short x, y, z;
	CSVector &operator+=(const CSVector &);
	void Mask();
};

struct TE {
	short x, y;
};

extern TE DAT_800c9670[2];
extern int DAT_800d16e4;

int Utils_GetGroundHeight(const CVector &, int, int);

struct CPowerUp {
	char pad0[4];
	CVector mPos;
	CSVector mAngles;
	char pad1[0x6c - 0x16];
	CVector mVel;
	CVector mAcc;
	char pad2;
	CFriction mFric;
	CSVector mAngVel;
	char pad3[0xbc - 0x8e];
	CVector mShadowPos;
	char pad4[0xd4 - 0xc8];
	short mShadowScale;
	short mShadowDist;
	char pad5[0x13e - 0xd8];
	uchar mFalling;
	uchar mLanded;
	uchar mHeight;
	char pad6;
	int mGroundY;
	CVector mWorld;
	ushort mBobAngle;
	ushort pad7;
	ushort mBobRadius;
	ushort mBobSpeed;
	void DoPhysics();
};

void CPowerUp::DoPhysics() {
	mAngles += mAngVel;
	mAngles.Mask();

	if (mFalling) {
		if (!mLanded && mGroundY < 0 && mGroundY >= -4) {
			if (DAT_800d16e4 & 1) {
				int ground = Utils_GetGroundHeight(mWorld, 0, 8000);

				if (ground == -1) {
					mGroundY--;

					if (mGroundY < -4)
						mLanded = 1;
				} else {
					mGroundY = ground;
				}
			}
		} else {
			mWorld += mVel;
			mVel.y += mAcc.y;
			mVel.y -= mVel.y >> mFric.y;

			if (!mLanded) {
				int bottom = mGroundY - (mHeight << 12);

				if (bottom < mWorld.y && mVel.y > 0) {
					mWorld.y = bottom;
					mVel.Set(0, 0, 0);

					mFalling = 0;
				}
			}

			mPos = mWorld;
		}
	} else {
		mPos = mWorld;
		int idx = mBobAngle & 4095;
		TE *b;

		b = DAT_800c9670;
		mPos.y += ((mBobRadius * b[idx].x) / 4096) << 12;
		mBobAngle += mBobSpeed;
	}

	mShadowPos = mWorld;
	mShadowPos.y = mGroundY;
	mShadowDist = (mGroundY - mPos.y) >> 12;

	if (mShadowDist)
		mShadowScale = 140 - (mShadowDist * 60) / 128;
	else
		mShadowScale = 0;
}
