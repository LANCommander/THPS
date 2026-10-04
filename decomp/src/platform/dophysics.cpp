/* DoPhysics__9CPlatform (0x8003e9d8) */
typedef unsigned char uchar;
typedef unsigned short ushort;
struct CFriction { uchar x, y, z; };
struct CVector {
	int x, y, z;
	CVector &operator+=(const CVector &);
	CVector &operator%=(const CFriction &);
	void KillSmall();
};
struct CSVector {
	short x, y, z;
	CSVector &operator+=(const CSVector &);
	CSVector &operator%=(const CFriction &);
	void Mask();
	void KillSmall();
};
struct CPlatform {
	char pad0[4];
	CVector mPos;
	CSVector mAngles;
	char pad1[0x6c - 0x16];
	CVector mVel;
	CVector mAcc;
	char pad2;
	CFriction mFric;
	CSVector mAngVel;
	CSVector mAngAcc;
	CFriction mAngFric;
	char pad3[0xa8 - 0x97];
	CSVector mS;
	char pad4[0x1d8 - 0xae];
	ushort mState;
	void DoPhysics();
};
void CPlatform::DoPhysics()
{
	mS.z = 0;
	mS.y = 0;
	mS.x = 0;
	if (mState == 0) {
		int vx, vy, vz;
		short sx, sy, sz;
		vx = mVel.x + mAcc.x;
		vy = mVel.y + mAcc.y;
		vz = mVel.z + mAcc.z;
		if (vx >= -2048 && vx <= 2048) vx = 0;
		if (vy >= -2048 && vy <= 2048) vy = 0;
		if (vz >= -2048 && vz <= 2048) vz = 0;
		mVel.x = vx;
		mVel.y = vy;
		mVel.z = vz;
		mPos.x += vx;
		mPos.y += vy;
		mPos.z += vz;
		sx = mAngVel.x;
		sy = mAngVel.y;
		sz = mAngVel.z;
		mAngles.x = (mAngles.x + sx) & 4095;
		mAngles.y = (mAngles.y + sy) & 4095;
		mAngles.z = (mAngles.z + sz) & 4095;
		sx = sx + mAngAcc.x;
		sy = sy + mAngAcc.y;
		sz = sz + mAngAcc.z;
		if (sx >= -1 && sx <= 1) sx = 0;
		if (sy >= -1 && sy <= 1) sy = 0;
		if (sz >= -1 && sz <= 1) sz = 0;
		mAngVel.x = sx;
		mAngVel.y = sy;
		mAngVel.z = sz;
	} else if (mState == 1 || mState == 2) {
		mVel += mAcc;
		mVel %= mFric;
		mVel.KillSmall();
		mPos += mVel;
		mAngles += mAngVel;
		mAngles.Mask();
		mAngVel += mAngAcc;
		mAngVel %= mAngFric;
		mAngVel.KillSmall();
	}
}
