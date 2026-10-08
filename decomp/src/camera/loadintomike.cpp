/* LoadIntoMikeCamera__7CCamera (0x80078b04) flags=-fstructure-noalias */
#pragma interface

struct MATRIX {
	short m[3][3];
	int t[3];
};

struct VECTOR {
	int vx, vy, vz, pad;
};

struct CVector {
	int vx, vy, vz;
};

class CClass {
  public:
	virtual void vf0();
};

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

struct Tripod {
	char pad[0x734];
	int state;
};

class CCamera {
  public:
	int a0;
	CVector mPos;
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

extern SCamEntry MikeCamera[];
extern CVector Camera_CamOffset;

int Camera_CurrentMikeCamera;

void QToM(const CQuat &, MATRIX &);
extern "C" void FUN_80093100(MATRIX *, CVector *);

void CCamera::LoadIntoMikeCamera() {
	VECTOR v;

	if (mTripod->state == 5) {
		MikeCamera[Camera_CurrentMikeCamera].pos.vx = (mTripodPos.vx + old_offset.vx) >> 12;
		MikeCamera[Camera_CurrentMikeCamera].pos.vy = (mTripodPos.vy + old_offset.vy) >> 12;
		MikeCamera[Camera_CurrentMikeCamera].pos.vz = (mTripodPos.vz + old_offset.vz) >> 12;
		mO = old_orientation;
	} else {
		MikeCamera[Camera_CurrentMikeCamera].pos.vx = (mPos.vx + real_cam_offset.vx) >> 12;
		MikeCamera[Camera_CurrentMikeCamera].pos.vy = (mPos.vy + real_cam_offset.vy) >> 12;
		MikeCamera[Camera_CurrentMikeCamera].pos.vz = (mPos.vz + real_cam_offset.vz) >> 12;
		old_orientation = mO;
		old_offset.vx = (MikeCamera[Camera_CurrentMikeCamera].pos.vx << 12) - mTripodPos.vx;
		old_offset.vy = (MikeCamera[Camera_CurrentMikeCamera].pos.vy << 12) - mTripodPos.vy;
		old_offset.vz = (MikeCamera[Camera_CurrentMikeCamera].pos.vz << 12) - mTripodPos.vz;
	}

	MikeCamera[Camera_CurrentMikeCamera].p14.vx = (mFocusPos.vx + Camera_CamOffset.vx) >> 12;
	MikeCamera[Camera_CurrentMikeCamera].p14.vy = (mFocusPos.vy + Camera_CamOffset.vy) >> 12;
	MikeCamera[Camera_CurrentMikeCamera].p14.vz = (mFocusPos.vz + Camera_CamOffset.vz) >> 12;
	QToM(mO, MikeCamera[Camera_CurrentMikeCamera].mat);
	FUN_80093100(&MikeCamera[Camera_CurrentMikeCamera].mat, &MikeCamera[Camera_CurrentMikeCamera].pos);
}
