/* ResetOrientation__7CCamera (0x80078d94) */
struct CVector {
	int x, y, z;
};

struct VECTOR {
	int vx, vy, vz, pad;
};

struct CClass {
	virtual void v0();
};

struct CQuat : CClass {
	int x, y, z, w;
};

struct CBruce {
	int vf;
	CVector mPos;
};

CVector operator<<(const CVector &, const int &);
extern "C" void ApplyMatrixLV(void *, VECTOR *, VECTOR *);

unsigned int DAT_800d2048;

struct CCamera {
	char pad0[0x134];
	unsigned short mMikeIndex;
	char pad1[0x420 - 0x136];
	CBruce *mFocus;
	char pad2[0x42c - 0x424];
	CVector mOldFocusPos;
	char pad3;
	CVector mFocusPos;
	char pad4[0x4c0 - 0x448];
	CQuat q4c0;
	CQuat q4d4;
	CQuat q4e8;
	char pad5[0x510 - 0x4fc];
	CQuat q510;
	int mStoppedOValid;
	char pad6[0x5f4 - 0x528];
	CVector v5f4;
	CVector v600;
	char pad7[0x64c - 0x60c];
	VECTOR real_cam_offset;
	void ResetOrientation();
	void CM_Normal();
	void LoadIntoMikeCamera();
};

void CCamera::ResetOrientation() {
	VECTOR vtemp1, vtemp2;
	CBruce *pBruce;

	pBruce = mFocus;
	vtemp1.vx = 0;
	vtemp1.vy = 0;
	vtemp1.vz = -4096;
	ApplyMatrixLV((char *)mFocus + 0x78c, &vtemp1, &vtemp2);

	real_cam_offset.vx = vtemp2.vx;
	real_cam_offset.vy = vtemp2.vy;
	real_cam_offset.vz = vtemp2.vz;
	v5f4 = v600 = (*(CVector *)&real_cam_offset) << 12;
	mOldFocusPos = mFocusPos = mFocus->mPos;
	DAT_800d2048 = mMikeIndex;
	CM_Normal();

	q510 = q4e8 = q4c0 = q4d4;
	mStoppedOValid = 1;
	LoadIntoMikeCamera();
}
