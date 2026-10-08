/* ReflectHeadingVelocityInPlane__6CBruceG7SVECTORi (0x80039f2c) */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

struct CVector {
	int x, y, z;
	CVector() {}
	void Set(int _x, int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

extern "C" int Mips_CVecDotProd__FP7CVectorT0(CVector *, CVector *);
extern "C" int Mips_FixMul__Fii(int, int);
extern "C" int FUN_8008b5dc(int);
extern "C" void FUN_80093130(MATRIX *, MATRIX *);
extern "C" void FUN_80093240(SVECTOR *, MATRIX *);
void M3dUtils_NormaliseVector(CVector *);

struct CBruce {
	char pad0[0x6c];
	CVector mVel;
	char pad1[0x78c - 0x78];
	MATRIX mRotMatrix;
	char pad2[0x7d8 - 0x7ac];
	CVector mFront;
	CVector mRight;
	CVector mUp;
	void FRUVectorsFromRotMatrix();
	void RotMatrixFromFRUVectors();
	void ReflectHeadingVelocityInPlane(SVECTOR Normal, int Angle);
};

void CBruce::ReflectHeadingVelocityInPlane(SVECTOR Normal, int Angle) {
	CVector TmpCV;
	int dot;
	MATRIX SurfaceRotMatrix;
	CVector OldVel;

	if (!Angle)
		Angle = 25;

	OldVel = mVel;

	{
		int _x = Normal.vx;
		int _y = Normal.vy;
		int _z = Normal.vz;

		TmpCV.x = _x;
		TmpCV.y = _y;
		TmpCV.z = _z;
	}

	dot = Mips_CVecDotProd__FP7CVectorT0(&mVel, &TmpCV);

	if (dot < 0) {
		mVel.x -= Mips_FixMul__Fii(Normal.vx, dot);
		mVel.y -= Mips_FixMul__Fii(Normal.vy, dot);
		mVel.z -= Mips_FixMul__Fii(Normal.vz, dot);
		mVel.x += Mips_FixMul__Fii(Normal.vx, 205);
		mVel.y += Mips_FixMul__Fii(Normal.vy, 205);
		mVel.z += Mips_FixMul__Fii(Normal.vz, 205);
	}

	{
		int _x = -Normal.vx;
		int _y = -Normal.vy;
		int _z = -Normal.vz;

		TmpCV.x = _x;
		TmpCV.y = _y;
		TmpCV.z = _z;
	}

	dot = Mips_CVecDotProd__FP7CVectorT0(&mFront, &TmpCV);

	if (dot < 0) {
		int sin;
		int cos;
		short *pShort;
		SVECTOR RotAngle;

		sin = FUN_8008b5dc(0x1000000 - dot * dot);
		pShort = (short *)&SurfaceRotMatrix;
		cos = dot;
		dot = Mips_CVecDotProd__FP7CVectorT0(&mRight, &TmpCV);

		if (dot > 0)
			sin = -sin;

		pShort[0] = cos;
		pShort[1] = 0;
		pShort[2] = -sin;
		pShort[3] = 0;
		pShort[4] = 4096;
		pShort[5] = 0;
		pShort[6] = sin;
		pShort[7] = 0;
		pShort[8] = cos;
		FUN_80093130(&mRotMatrix, &SurfaceRotMatrix);

		RotAngle.vz = 0;
		RotAngle.vx = 0;
		RotAngle.vy = (dot > 0 ? Angle - 1024 : 1024 - Angle) & 4095;
		FUN_80093240(&RotAngle, &SurfaceRotMatrix);
		FUN_80093130(&mRotMatrix, &SurfaceRotMatrix);
		FRUVectorsFromRotMatrix();
		M3dUtils_NormaliseVector(&mFront);
		M3dUtils_NormaliseVector(&mUp);
		gte_ldopv1(&mFront);
		gte_ldopv2(&mUp);
		gte_op12();
		gte_stlvnl(&mRight);
		M3dUtils_NormaliseVector(&mRight);
		gte_ldopv1(&mUp);
		gte_ldopv2(&mRight);
		gte_op12();
		gte_stlvnl(&mFront);
		RotMatrixFromFRUVectors();
	}
}
