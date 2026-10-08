/* CM_Normal__7CCamera (0x8007c240) */
/* C++ (CAMERA.CPP). Fuzzy demo twin (opcode-identical but for one instruction); locals from its
   MAIN.SYM. THPS1's CCamera members sit 0x2c past the demo's (its CBody is bigger).
   #pragma interface keeps g++ from emitting CQuat's inline virtual destructor and vtable here. */
#pragma interface

extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

struct CVector {
	int vx, vy, vz;
	CVector() {}
	CVector(int x, int y, int z) {
		vx = x;
		vy = y;
		vz = z;
	}
	int Length() const;
	int operator==(const CVector &);
	CVector operator-() const;
};

CVector operator-(const CVector &, const CVector &);
CVector operator+(const CVector &, const CVector &);
CVector operator>>(const CVector &, const int &);
CVector operator<<(const CVector &, const int &);

struct CSVector {
	short vx, vy, vz;
};

class CClass {
  public:
	virtual ~CClass() {}
};

class CQuat : public CClass {
  public:
	int x, y, z, w;
};

CQuat Quat_FromYRot(short);
CQuat operator*(const CQuat &, const CQuat &);
void MToQ(const MATRIX &, CQuat &);

class CCamera {
  public:
	char pad0[0x420];
	char *mTripod; /* 0x420 */
	char pad424[0x42c - 0x424];
	CVector mOldTripodPos; /* 0x42c */
	int new_focus;         /* 0x438 */
	CVector mTripodPos;    /* 0x43c */
	char pad448[0x4d4 - 0x448];
	CQuat mDesiredO; /* 0x4d4 */
	char pad4e8[0x590 - 0x4e8];
	unsigned int mTimer; /* 0x590 */
	char pad594[0x5f0 - 0x594];
	int extra_YRot;     /* 0x5f0 */
	CVector mVFront;    /* 0x5f4 */
	CVector mOldVFront; /* 0x600 */
	int prev_speed_lag_dist;
	int big_air; /* 0x610 */
	int big_air_timer;
	int big_air_end_timer;
	int big_air_mph;
	int new_hang_time;
	int in_pool_timer; /* 0x624 */
	char pad628[0x648 - 0x628];
	int turn_delay_timer; /* 0x648 */
	CVector vFront;       /* 0x64c */
	void CM_Normal();
};

int Mips_CVecDotProd(CVector *, CVector *);
void Utils_CalcAim(CSVector &, const CVector &, const CVector &);
void Utils_GetVecFromMagDir(CVector &, int, const CSVector &);

extern char *GSkater;
extern MATRIX tm;

#define ABS(x) (((x) ^ ((x) >> 31)) - ((x) >> 31))

void CCamera::CM_Normal() {
	CVector vUp;
	CVector vRight;
	CSVector ang1;
	int dot_up;
	int dot_front;
	CVector temp_vel = mTripodPos - mOldTripodPos;

	vUp = *(CVector *)(mTripod + 0x7f0);
	CVector Down(0, 4096, 0);
	CVector Zero(0, 0, 0);
	CVector temp_front;

	dot_up = ABS(Mips_CVecDotProd(&Down, &vUp));
	Utils_CalcAim(ang1, Zero, temp_vel);
	Utils_GetVecFromMagDir(temp_front, 4096, ang1);

	dot_front = ABS(Mips_CVecDotProd(&temp_front, &vUp));

	in_pool_timer++;

	if (dot_up < 3572 && (*(int *)(mTripod + 0x734) == 2 || *(int *)(mTripod + 0x734) == 8)) {
		if (!big_air && *(int *)(mTripod + 0x740))
			(*(int *)(mTripod + 0x244))++;

		if (++turn_delay_timer >= 4)
			vFront = CVector(0, 0x1000000, 0);
		else
			Utils_GetVecFromMagDir(vFront, 4096, ang1);

		big_air = 1;
		in_pool_timer = 0;
	} else if ((dot_front >> 12) > 2000 || temp_vel.Length() < 5) {
		turn_delay_timer = 0;

		if (dot_up < 3572 && big_air == 1)
			in_pool_timer = 0;

		big_air = 0;
	} else {
		turn_delay_timer = 0;
		Utils_GetVecFromMagDir(vFront, 4096, ang1);

		if (dot_up < 3572 && big_air == 1)
			in_pool_timer = 0;

		big_air = 0;
	}

	mOldVFront = mVFront;

	if (mTripodPos == mOldTripodPos)
		mVFront = mOldVFront;
	else
		mVFront = (mOldVFront + vFront) >> 1;

	if (mTimer < 12) {
		mVFront = (-*(CVector *)(GSkater + 0x7d8)) << 12;
		mOldVFront = mVFront;
		vFront = mOldVFront;
	}

	vFront = mVFront;

	CVector U;
	CVector V;
	CVector N;

	N = vFront >> 12;
	V.vx = -vUp.vx;
	V.vy = -vUp.vy;
	V.vz = -vUp.vz;
	gte_ldopv1(&V);
	gte_ldopv2(&N);
	gte_op0();
	gte_stlvnl(&U);
	U.vx >>= 12;
	U.vy >>= 12;
	U.vz >>= 12;
	gte_ldopv1(&U);
	gte_ldopv2(&V);
	gte_op0();
	gte_stlvnl(&N);
	N.vx >>= 12;
	N.vy >>= 12;
	N.vz >>= 12;
	tm.m[0][0] = U.vx;
	tm.m[1][0] = U.vy;
	tm.m[2][0] = U.vz;
	tm.m[0][1] = V.vx;
	tm.m[1][1] = V.vy;
	tm.m[2][1] = V.vz;
	tm.m[0][2] = N.vx;
	tm.m[1][2] = N.vy;
	tm.m[2][2] = N.vz;
	MToQ(tm, mDesiredO);

	mDesiredO = mDesiredO * Quat_FromYRot(extra_YRot);
}
