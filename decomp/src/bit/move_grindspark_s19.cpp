/* Move__11CGrindSpark (0x8002780c) */
typedef unsigned short ushort;

struct CVector {
	int x, y, z;
};

struct CBody {
	char pad[4];
	CVector mPos;
};

struct CGrindSpark {
	char pad0[8];
	short mAge;
	ushort mLifetime;
	char pad1[0xc];
	CVector mPos;
	CVector mVel;
	CVector mAcc;
	char pad2[0x50 - 0x3c];
	CVector mStart;
	CVector mEnd;
	CVector mOldPos;
	CBody *mpParent;
	void Move();
	void Die();
};

void CGrindSpark::Move() {
	int px, py, pz, nx, ny, nz, sx, sy, sz;

	px = mPos.x;
	py = mPos.y;
	pz = mPos.z;
	nx = px + mVel.x;
	ny = py + mVel.y;
	nz = pz + mVel.z;
	sx = mpParent->mPos.x;
	sy = mpParent->mPos.y;
	sz = mpParent->mPos.z;
	mOldPos.x = px;
	mOldPos.y = py;
	mOldPos.z = pz;
	mEnd.x = px + sx;
	mEnd.y = py + sy;
	mEnd.z = pz + sz;
	mPos.x = nx;
	mPos.y = ny;
	mPos.z = nz;
	mStart.x = nx + sx;
	mStart.y = ny + sy;
	mStart.z = nz + sz;
	nx = mVel.x + mAcc.x;
	ny = mVel.y + mAcc.y;
	nz = mVel.z + mAcc.z;
	nx -= nx >> 3;
	ny -= ny >> 3;
	nz -= nz >> 3;
	mVel.x = nx;
	mVel.y = ny;
	mVel.z = nz;
	mAge++;

	if (mAge >= mLifetime)
		Die();
}
