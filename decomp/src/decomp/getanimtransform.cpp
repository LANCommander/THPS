/* Decomp_GetAnimTransform__FP6CSuper (0x80013cd4) */
/* C++ (DECOMP.CPP). Fuzzy demo twin (0.74, opcode-identical in shape); locals from its MAIN.SYM.
   Returns the per-model matrices for the object's current animation frame. Type-42 files hold
   ready matrices. Type-44 files are compressed Euler/pivot streams: the first call allocates a
   buffer and works out a parent-before-child model order, then each new animation decompresses
   its streams and each new frame rebuilds the matrices down the hierarchy. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <inline_c.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
#define MTC2(n, v) __asm__ volatile ("mtc2 %0, $" #n : : "r"(v))
#define CTC2(n, v) __asm__ volatile ("ctc2 %0, $" #n : : "r"(v))
struct SMatrix {
	short m[3][3];
	short t[3];
};
struct SEulerPivot {
	short rx, ry, rz;
	short tx, ty, tz;
};
struct SPSXRegion {
	char pad0[16];
	uint *pModels;          /* 0x10 */
	uint *pItems;           /* 0x14 */
	uint *pAnimFile;        /* 0x18 */
	ushort *pParent;        /* 0x1c */
	char pad20[64 - 0x20];
};
class CSuper {
public:
	char pad0[0x1b];
	uchar mType;              /* 0x1b */
	char pad1c[0x138 - 0x1c];
	ushort *pOrder;           /* 0x138 */
	SMatrix *pMats;           /* 0x13c */
	ushort mRoot;             /* 0x140 */
	uchar mLastAnim;          /* 0x142 */
	signed char mLastFrame;   /* 0x143 */
	short mFrame;             /* 0x144 */
	ushort mAnim;             /* 0x146 */
};
extern SPSXRegion DAT_800bf7a8[];
extern SMatrix DAT_800c4b3c[];
void M3dUtils_InBetween(CSuper *);
uchar *DecompressStream(uchar *, short *, int, int);
extern "C" {
void *FUN_8004d068(int, int, int);
void FUN_8008b3d4(SEulerPivot *, SMatrix *);
}

SMatrix *Decomp_GetAnimTransform(CSuper *pSuper)
{
	SPSXRegion *pRegion;
	uint *pAnimFile;
	uint NumModels;
	uint NumItems;

	pRegion = &DAT_800bf7a8[pSuper->mType];
	pAnimFile = pRegion->pAnimFile;
	NumModels = pRegion->pModels[-1];
	NumItems = pRegion->pItems[2];
	switch (pAnimFile[-2]) {
	case 42:
		if (*(ushort *)((char *)pAnimFile + pSuper->mAnim * 8 + 10)) {
			M3dUtils_InBetween(pSuper);
			return DAT_800c4b3c;
		}
		return (SMatrix *)((char *)pAnimFile + pAnimFile[pSuper->mAnim * 2 + 1]) + pSuper->mFrame * NumItems;
	case 44: {
		int NewBuffer = 0;
		uint *pAnimHeader;
		int NewAnim;
		if (!pSuper->pMats) {
			{
				uint *pHeader = pAnimFile + 1;
				int NumAnims = pAnimFile[0];
				uint MaxFrames = 0;
				int i;
				for (i = 0; i < NumAnims; i++) {
					pHeader++;
					if (MaxFrames < *pHeader)
						MaxFrames = *pHeader;
					pHeader++;
				}
				pSuper->pMats = (SMatrix *)FUN_8004d068(NumModels * sizeof(SMatrix) + MaxFrames * NumModels * sizeof(SEulerPivot), 1, 1);
			}
			pSuper->pOrder = (ushort *)FUN_8004d068(NumModels * 2, 0, 1);
			pSuper->mRoot = 0xffff;
			{
				uint i;
				for (i = 0; i < NumModels; i++)
					if (pRegion->pParent[i] == i)
						pSuper->mRoot = i;
			}
			pSuper->pOrder[0] = pSuper->mRoot;
			{
				ushort *pParent = pSuper->pOrder;
				ushort *pChild = pParent + 1;
				int c = NumModels - 1;
				while (c) {
					ushort *pHi = pRegion->pParent;
					uint i;
					for (i = 0; i < NumModels; i++, pHi++) {
						if (i != pSuper->mRoot && *pHi == *pParent) {
							*pChild++ = i;
							c--;
						}
					}
					pParent++;
				}
			}
			NewBuffer = 1;
		}
		NewAnim = 0;
		pAnimHeader = &pAnimFile[pSuper->mAnim * 2 + 1];
		if (pSuper->mLastAnim != pSuper->mAnim || NewBuffer) {
			SEulerPivot *pEulerPivot = (SEulerPivot *)(pSuper->pMats + NumModels);
			uchar *pCompressedStream = (uchar *)pAnimFile + pAnimHeader[0];
			int NumFrames = pAnimHeader[1];
			int StepSize = NumModels * 6;
			uint m;
			for (m = 0; m < NumModels; m++) {
				pCompressedStream = DecompressStream(pCompressedStream, &pEulerPivot->rx, StepSize, NumFrames);
				pCompressedStream = DecompressStream(pCompressedStream, &pEulerPivot->ry, StepSize, NumFrames);
				pCompressedStream = DecompressStream(pCompressedStream, &pEulerPivot->rz, StepSize, NumFrames);
				pCompressedStream = DecompressStream(pCompressedStream, &pEulerPivot->tx, StepSize, NumFrames);
				pCompressedStream = DecompressStream(pCompressedStream, &pEulerPivot->ty, StepSize, NumFrames);
				pCompressedStream = DecompressStream(pCompressedStream, &pEulerPivot->tz, StepSize, NumFrames);
				pEulerPivot++;
			}
			pSuper->mLastAnim = pSuper->mAnim;
			NewAnim = 1;
		}
		if (pSuper->mLastFrame != pSuper->mFrame || NewAnim) {
			SEulerPivot *pEulerPivots = (SEulerPivot *)(pSuper->pMats + NumModels);
			SMatrix *pMat;
			SEulerPivot *pRootEuler;
			pEulerPivots += NumModels * pSuper->mFrame;
			pMat = pSuper->pMats + pSuper->mRoot;
			pRootEuler = pEulerPivots + pSuper->mRoot;
			ushort *pModel;
			uint i;
			FUN_8008b3d4(pRootEuler, pMat);
			pMat->t[0] = pRootEuler->tx;
			pMat->t[1] = pRootEuler->ty;
			pMat->t[2] = pRootEuler->tz;
			pModel = pSuper->pOrder + 1;
			for (i = 1; i < NumModels; i++) {
				int m = *pModel++;
				SMatrix *pParentMat;
				SEulerPivot *pEulerPivot;
				pMat = pSuper->pMats + m;
				pEulerPivot = pEulerPivots + m;
				pParentMat = pSuper->pMats + pRegion->pParent[m];
				FUN_8008b3d4(pEulerPivot, pMat);
				if (!((int)pEulerPivot & 3)) {
					SVECTOR vec;
					vec.vx = pEulerPivot->tx;
					vec.vy = pEulerPivot->ty;
					vec.vz = pEulerPivot->tz;
					MTC2(0, *(int *)&vec.vx);
					MTC2(1, *(int *)&vec.vz);
				} else {
					MTC2(0, *(int *)&pEulerPivot->tx);
					MTC2(1, *(int *)&pEulerPivot->tz);
				}
				CTC2(0, ((int *)pParentMat)[0]);
				CTC2(1, ((int *)pParentMat)[1]);
				CTC2(2, ((int *)pParentMat)[2]);
				CTC2(3, ((int *)pParentMat)[3]);
				CTC2(4, ((int *)pParentMat)[4]);
				gte_rtv0();
				gte_stsv(&pMat->t[0]);
				pMat->t[0] += pParentMat->t[0];
				pMat->t[1] += pParentMat->t[1];
				pMat->t[2] += pParentMat->t[2];
			}
			pSuper->mLastFrame = pSuper->mFrame;
		}
		return pSuper->pMats;
	}
	}
}
