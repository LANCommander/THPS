/* DoPhysics__6CMedal (0x80073cf8) */
struct CVector {
	int vx, vy, vz;
};

struct CSVector {
	short vx, vy, vz;
	CSVector &operator+=(const CSVector &);
	void Mask();
};

struct SSinCos {
	short s, c;
};

extern SSinCos rcossin_tbl[];

#define SIN(a) (rcossin_tbl[(a) & 4095].s)

class CMedal {
  public:
	char pad0[4];
	CVector mPos;
	CSVector mRot;
	char pad16[0x88 - 0x16];
	CSVector mRotVel;
	char pad8e[0x140 - 0x8e];
	CVector mOrgPos;
	unsigned short mT;
	unsigned short mMaxWobbleAmplitude;
	unsigned short mWobbleAmplitude;
	unsigned short mWobbleSpeed;
	void DoPhysics();
};

void CMedal::DoPhysics() {
	mRot += mRotVel;
	mRot.Mask();

	mPos = mOrgPos;
	mPos.vy += ((mWobbleAmplitude * SIN(mT)) / 4096) << 12;
	mT += mWobbleSpeed;
}
