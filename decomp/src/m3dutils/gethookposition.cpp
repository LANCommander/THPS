/* M3dUtils_GetHookPosition__FP6VECTORP6CSuperi (0x8008125c) */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char uchar;

struct SVector {
	short x, y, z;
};

struct SHook {
	SVector Offset;
	ushort Part;
};

struct SMatrix {
	short m[3][3];
	short t[3];
};

struct SEnv {
	char pad0[0x18];
	uint *pAnimFile;
	char pad1[4];
	SHook *pHooks;
	char pad2[0x30 - 0x24];
	ushort NumParts;
	char pad3[0x40 - 0x32];
};

extern SEnv PSXRegion[];
extern SMatrix TweenBuffer[];

struct CSuper {
	ushort mFlags;
	char pad0[2];
	int mPosX, mPosY, mPosZ;
	char pad1[0x1b - 0x10];
	uchar mRegion;
	char pad2[0x134 - 0x1c];
	uint mExtraFlags;
	char pad3[0x146 - 0x138];
	ushort mAnim;
	char pad4[0x164 - 0x148];
	short mat[3][3];
	char pad5[0x184 - 0x176];
	SMatrix *mpFrame;
};

SMatrix *Decomp_GetAnimTransform(CSuper *);

struct Item;

void M3dUtils_InterpolateVectors(int, int, uint *, Item *, int, int);
void M3dAsm_TransformTwice(SVector *, SMatrix *, MATRIX *);

void M3dUtils_GetHookPosition(VECTOR *pResult, CSuper *pSuper, int Hook) {
	SMatrix *pAnimTransform;
	int Anim;
	int Part;
	uint *pAnimFile;
	SHook *pHook;

	pHook = PSXRegion[pSuper->mRegion].pHooks + Hook;
	Anim = pSuper->mAnim;
	Part = pHook->Part;
	pAnimFile = PSXRegion[pSuper->mRegion].pAnimFile;

	if (pSuper->mExtraFlags & 2) {
		pSuper->mat[0][0] = -pSuper->mat[0][0];
		pSuper->mat[1][0] = -pSuper->mat[1][0];
		pSuper->mat[2][0] = -pSuper->mat[2][0];
	}

	if (pSuper->mFlags & 4) {
		pAnimTransform = pSuper->mpFrame + Part;
	} else {
		ushort Interval = ((ushort *)pAnimFile)[Anim * 4 + 5];

		if (Interval) {
			M3dUtils_InterpolateVectors(4, Interval + 1, pAnimFile, (Item *)pSuper, Part,
			                            PSXRegion[pSuper->mRegion].NumParts);

			pAnimTransform = TweenBuffer + Part;
		} else {
			pAnimTransform = Decomp_GetAnimTransform(pSuper) + Part;
		}
	}

	M3dAsm_TransformTwice((SVector *)pHook, pAnimTransform, (MATRIX *)pSuper->mat);
	gte_stlvnl(pResult);
	pResult->vx <<= 12;
	pResult->vy <<= 12;
	pResult->vz <<= 12;
	pResult->vx = pSuper->mPosX + ((pResult->vx - pSuper->mPosX) >> 4);
	pResult->vy = pSuper->mPosY + ((pResult->vy - pSuper->mPosY) >> 4);
	pResult->vz = pSuper->mPosZ + ((pResult->vz - pSuper->mPosZ) >> 4);

	if (pSuper->mExtraFlags & 2) {
		pSuper->mat[0][0] = -pSuper->mat[0][0];
		pSuper->mat[1][0] = -pSuper->mat[1][0];
		pSuper->mat[2][0] = -pSuper->mat[2][0];
	}
}
