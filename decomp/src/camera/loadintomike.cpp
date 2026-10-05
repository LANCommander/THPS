/* LoadIntoMikeCamera__7CCamera (0x80078b04) flags=-fstructure-noalias */
#pragma interface
struct MATRIX { short m[3][3]; int t[3]; };
struct VECTOR { int vx, vy, vz, pad; };
struct CVector { int vx, vy, vz; };
class CClass { public: virtual void vf0(); };
class CQuat : public CClass {
public:
	int x, y, z, w;
};
struct SCamEntry {
	int p0;
	CVector pos;
	int p10;
	CVector p14;
	char pad[0x34 - 0x20];
	MATRIX mat;
	char pad2[164 - 0x54];
};
struct Tripod { char pad[0x734]; int state; };
class CCamera {
public:
	int a0; CVector mPos;
	char pad1[0x420 - 0x10];
	Tripod *mTripod;
	char pad2[0x43c - 0x424];
	CVector mTripodPos;
	char pad3[0x46c - 0x448];
	CVector mFocusPos;
	char pad4[0x4c0 - 0x478];
	CQuat mO;
	char pad5[0x678 - 0x4d4];
	VECTOR real_cam_offset;
	CQuat old_orientation;
	VECTOR old_offset;
	void LoadIntoMikeCamera();
};
extern SCamEntry DAT_800c119c[];
extern CVector DAT_800c1154;
int DAT_800d2048;
void QToM(const CQuat &, MATRIX &);
extern "C" void FUN_80093100(MATRIX *, CVector *);

void CCamera::LoadIntoMikeCamera()
{
	VECTOR v;
	if (mTripod->state == 5) {
		DAT_800c119c[DAT_800d2048].pos.vx = (mTripodPos.vx + old_offset.vx) >> 12;
		DAT_800c119c[DAT_800d2048].pos.vy = (mTripodPos.vy + old_offset.vy) >> 12;
		DAT_800c119c[DAT_800d2048].pos.vz = (mTripodPos.vz + old_offset.vz) >> 12;
		mO = old_orientation;
	} else {
		DAT_800c119c[DAT_800d2048].pos.vx = (mPos.vx + real_cam_offset.vx) >> 12;
		DAT_800c119c[DAT_800d2048].pos.vy = (mPos.vy + real_cam_offset.vy) >> 12;
		DAT_800c119c[DAT_800d2048].pos.vz = (mPos.vz + real_cam_offset.vz) >> 12;
		old_orientation = mO;
		old_offset.vx = (DAT_800c119c[DAT_800d2048].pos.vx << 12) - mTripodPos.vx;
		old_offset.vy = (DAT_800c119c[DAT_800d2048].pos.vy << 12) - mTripodPos.vy;
		old_offset.vz = (DAT_800c119c[DAT_800d2048].pos.vz << 12) - mTripodPos.vz;
	}
	DAT_800c119c[DAT_800d2048].p14.vx = (mFocusPos.vx + DAT_800c1154.vx) >> 12;
	DAT_800c119c[DAT_800d2048].p14.vy = (mFocusPos.vy + DAT_800c1154.vy) >> 12;
	DAT_800c119c[DAT_800d2048].p14.vz = (mFocusPos.vz + DAT_800c1154.vz) >> 12;
	QToM(mO, DAT_800c119c[DAT_800d2048].mat);
	FUN_80093100(&DAT_800c119c[DAT_800d2048].mat, &DAT_800c119c[DAT_800d2048].pos);
}
