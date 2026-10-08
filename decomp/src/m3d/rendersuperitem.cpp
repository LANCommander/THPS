/* RenderSuperItem__FP4Item (0x8008468c) flags=-fstructure-noalias */
/* C++ (M3D.CPP). Fuzzy demo twin (0.83 by opcode); locals from its MAIN.SYM. Renders a "super"
   (multi-part animated) item: builds its camera-space transform (mirrored if flagged, with a finer
   translation when it is close), then for each part multiplies in the part's animation matrix,
   draws it (lit, coloured or plain), and adds the part's ellipsoid and shadows. THPS1 calls
   MulMatrix0 where the demo inlined the GTE sequence, and skips a part's extras up front. */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct CVector {
	int vx, vy, vz;
};

struct CSVector {
	short vx, vy, vz;
};

struct SModel {
	ushort Flags;
	ushort NumVertices;
	ushort NumNormals;
};

struct Texture;

struct SAnimFrame {
	int m0;
	Texture *pTexture;
};

struct SMatrix {
	short m[3][3];
	short t[3];
};

struct SCamera {
	int pad;
	CVector Pos; /* 0x04 */
	char pad10[0x74 - 0x10];
	MATRIX View; /* 0x74 */
};

struct SPSXRegion {
	char pad0[0x10];
	SModel **ppModels; /* 0x10 */
	char pad14[0x24 - 0x14];
	SAnimFrame *pAnimTex; /* 0x24 */
	char pad28[0x30 - 0x28];
	ushort NumParts; /* 0x30 */
	uchar m32;       /* 0x32 */
	char pad33[64 - 0x33];
};

struct Item {
	ushort Flags; /* 0x000 */
	char pad2[2];
	CVector Pos; /* 0x004 */
	char pad10[0x1b - 0x10];
	uchar Region; /* 0x01b */
	char pad1c[0x3c - 0x1c];
	char *pLight; /* 0x03c */
	char pad40[0xb4 - 0x40];
	uint EllipsoidRGB;         /* 0x0b4 */
	ushort EllipsoidScale;     /* 0x0b8 */
	short EllipsoidOTPushback; /* 0x0ba */
	CVector ShadowPos;         /* 0x0bc */
	CSVector ShadowNormal;     /* 0x0c8 */
	char padce[0x134 - 0xce];
	int SuperFlags; /* 0x134 */
	char pad138[0x15a - 0x138];
	uchar NumShadows;       /* 0x15a */
	SVECTOR *pShadowLights; /* 0x15c */
	CVECTOR *pShadowRGBs;   /* 0x160 */
	MATRIX Matrix;          /* 0x164 */
	char pad184[0x184 - 0x184];
	SMatrix *pAnimTransform; /* 0x184 */
	char pad188[0x194 - 0x188];
	uint HiddenParts; /* 0x194 */
};

extern SPSXRegion PSXRegion[];
extern SAnimFrame *QuickAnimLookup[];
extern int CurrentWaterLevel;

int Fast;
SCamera *pCurrentCamera;
int Dewibble;
uint FrameNo;
char *ProjectedVertices;
char *FreeStitchVertex;
SAnimFrame *pColourTable;
int SubObjectMasked;
int TestTheWater;

void RenderModelInSuperFast(SModel *);
void M3dElips_RenderEllipsoid(SModel *, MATRIX *, uint, int, int, Texture *);
void M3dElips_RenderShadow(SModel *, MATRIX *, CSVector *, CVector *, SVECTOR *, CVECTOR);

extern "C" {
	void FUN_8008b254(MATRIX *, MATRIX *);
	SMatrix *Decomp_GetAnimTransform__FP6CSuper(Item *);
	MATRIX *FUN_8009738c(MATRIX *, MATRIX *, MATRIX *);
	void FUN_80089fc8(MATRIX *, MATRIX *, SMatrix *);
	void FUN_8008a1c8(MATRIX *, MATRIX *, SMatrix *);
	void FUN_800866cc(MATRIX *, long *, SModel *);
	void FUN_80086f20(char *);
	void FUN_80086a4c(char *, int);
	void FUN_80084ebc(SModel *);
	void FUN_8008b71c(MATRIX *);
}

void RenderSuperItem(Item *pItem) {
	uint NumParts;
	uint Rgb;
	VECTOR Position;
	SMatrix *pAnimTransform;
	MATRIX Transform;
	MATRIX SuperTransform;
	MATRIX WorldTransform;
	MATRIX SuperLightTransform;
	int i;
	int Type;
	SModel *pModel;
	SModel **ppModels;
	SAnimFrame *pAnimTex;
	ushort Scale;
	short OTPushback;
	uint ItemFlags;

	ItemFlags = pItem->Flags;

	if (!PSXRegion[pItem->Region].m32 || (ItemFlags & 0xc80))
		Fast = 0;
	else
		Fast = 1;

	if (pItem->SuperFlags & 2) {
		pItem->Matrix.m[0][0] = -pItem->Matrix.m[0][0];
		pItem->Matrix.m[1][0] = -pItem->Matrix.m[1][0];
		pItem->Matrix.m[2][0] = -pItem->Matrix.m[2][0];
		*(short *)0x1f8002d4 = 1;
	} else {
		*(short *)0x1f8002d4 = 0;
	}

	gte_SetRotMatrix(&pCurrentCamera->View);
	FUN_8008b254(&pItem->Matrix, &SuperTransform);

	Position.vx = (pItem->Pos.vx >> 12) - pCurrentCamera->Pos.vx;
	Position.vy = (pItem->Pos.vy >> 12) - pCurrentCamera->Pos.vy;
	Position.vz = (pItem->Pos.vz >> 12) - pCurrentCamera->Pos.vz;
	gte_ldlvl(&Position);
	gte_rtir();
	gte_stlvnl(&SuperTransform.t[0]);

	if (*(short *)&SuperTransform.t[2] < 1000) {
		Dewibble = 1;
		Position.vx = (pItem->Pos.vx >> 8) - (pCurrentCamera->Pos.vx << 4);
		Position.vy = (pItem->Pos.vy >> 8) - (pCurrentCamera->Pos.vy << 4);
		Position.vz = (pItem->Pos.vz >> 8) - (pCurrentCamera->Pos.vz << 4);
		gte_ldlvl(&Position);
		gte_rtir();
		gte_stlvnl(&SuperTransform.t[0]);
	} else {
		Dewibble = 0;
	}

	ppModels = PSXRegion[pItem->Region].ppModels;
	NumParts = PSXRegion[pItem->Region].NumParts;

	if (ItemFlags & 4)
		pAnimTransform = pItem->pAnimTransform;
	else
		pAnimTransform = Decomp_GetAnimTransform__FP6CSuper(pItem);

	FUN_8009738c((MATRIX *)pItem->pLight, &pItem->Matrix, &SuperLightTransform);

	Type = pItem->EllipsoidRGB >> 24;

	if (Type & 127) {
		int Lookup = (Type - 1) & 127;

		if (Lookup > 1)
			Lookup = 1;

		if (Lookup < 0)
			Lookup = 0;

		pAnimTex = QuickAnimLookup[Lookup];
		pAnimTex += FrameNo % ((uint *)pAnimTex)[-1];
		Rgb = pItem->EllipsoidRGB & 0xffffff;
		Scale = pItem->EllipsoidScale;
		OTPushback = pItem->EllipsoidOTPushback;
	}

	FreeStitchVertex = Fast ? (char *)0x1f8003f8 : ProjectedVertices + 3192;
	pColourTable = PSXRegion[pItem->Region].pAnimTex;

	for (i = 0; i < NumParts; i++, pAnimTransform++) {
		SubObjectMasked = (pItem->HiddenParts & (1 << i)) != 0;
		pModel = ppModels[i];
		FUN_8009738c(&pItem->Matrix, (MATRIX *)pAnimTransform, &WorldTransform);

		if (Dewibble)
			FUN_80089fc8(&SuperTransform, &SuperLightTransform, pAnimTransform);
		else
			FUN_8008a1c8(&SuperTransform, &SuperLightTransform, pAnimTransform);

		if ((pModel->Flags & 1) || (pItem->Flags & 0x4000)) {
			FUN_800866cc(&WorldTransform, SuperTransform.t, pModel);
		} else if ((pModel->Flags & 4) || (ItemFlags & 128)) {
			gte_SetColorMatrix((MATRIX *)(pItem->pLight + 20));
			FUN_80086f20(pItem->pLight + 40);
			FUN_80086a4c((char *)pModel + (pModel->NumVertices * 8 + 28), pModel->NumNormals);
		}

		if (!(Type & 128)) {
			if (Fast)
				RenderModelInSuperFast(pModel);
			else
				FUN_80084ebc(pModel);
		}

		if (!SubObjectMasked) {
			int DoEllipsoids = Type & 127;
			int DoShadows = pItem->NumShadows != 0;

			if (DoEllipsoids || DoShadows) {
				gte_ldsv(&pAnimTransform->t[0]);
				FUN_8008b71c(&pItem->Matrix);
				gte_stlvnl(&WorldTransform.t[0]);
				WorldTransform.t[0] >>= 4;
				WorldTransform.t[1] >>= 4;
				WorldTransform.t[2] >>= 4;
				WorldTransform.t[0] += pItem->Pos.vx >> 12;
				WorldTransform.t[1] += pItem->Pos.vy >> 12;
				WorldTransform.t[2] += pItem->Pos.vz >> 12;
			}

			if (DoEllipsoids && (!TestTheWater || WorldTransform.t[1] < (CurrentWaterLevel >> 12) - 40))
				M3dElips_RenderEllipsoid(pModel, &WorldTransform, Rgb, Scale, OTPushback,
				                         pAnimTex->pTexture);

			if (DoShadows) {
				int s;

				for (s = 0; s < pItem->NumShadows; s++)
					M3dElips_RenderShadow(pModel, &WorldTransform, &pItem->ShadowNormal,
					                      &pItem->ShadowPos, &pItem->pShadowLights[s],
					                      pItem->pShadowRGBs[s]);
			}
		}
	}

	if (pItem->SuperFlags & 2) {
		pItem->Matrix.m[0][0] = -pItem->Matrix.m[0][0];
		pItem->Matrix.m[1][0] = -pItem->Matrix.m[1][0];
		pItem->Matrix.m[2][0] = -pItem->Matrix.m[2][0];
	}
}
