/* M3dColij_LineToThisItem__FP4ItemP9SLineInfo (0x80080964) */
/* C++ (M3DCOLIJ.CPP). Fuzzy demo twin (0.97); locals from its MAIN.SYM. Tests the line against one
   item's model. An unrotated, unscaled item just offsets the line start. Otherwise the item's
   matrix is built in DAT_800c13cc, with the axis-swapped variant for flagged lines. The model's
   vertices are projected (into the scratchpad when small enough) and the faces tested. A hit on a
   trigger face fires that face's node. */
extern "C" {
	#include <sys/types.h>
	#include <libgte.h>
	#include <inline_c.h>
}

typedef unsigned char uchar;
typedef unsigned short ushort;

struct CVector {
	int vx, vy, vz;
};

struct SProjectedVertex;

struct SModel {
	short pad0;
	ushort NumVerts; /* 2 */
};

struct SPSXRegion {
	char pad0[16];
	SModel **pModels; /* 0x10 */
	char pad14[64 - 0x14];
};

struct Item {
	ushort Flags; /* 0 */
	ushort pad2;
	CVector Pos;       /* 4 */
	short Angles[3];   /* 16 */
	ushort ModelIndex; /* 22 */
	char pad18[27 - 24];
	uchar Region; /* 27 */
};

struct SLineInfo {
	CVector Start; /* 0 */
	char padc[0x44 - 12];
	int x44;       /* 0x44 */
	MATRIX Matrix; /* 0x48 */
	char pad68[0x89 - 0x68];
	uchar Swapped; /* 0x89 */
};

extern SPSXRegion DAT_800bf7a8[];
extern MATRIX DAT_800c13cc;
extern SProjectedVertex *DAT_800d2160;
extern int DAT_800d1ef0;
extern int *DAT_800d1f0c[2];

int DAT_800d210c;
int DAT_800d20d8;

int Spool_GetEnvIndex(int);

extern "C" {
	void FUN_800972bc(MATRIX *);
	void FUN_8008b3d4(short *, MATRIX *);
	void FUN_8008b4e0(Item *, MATRIX *);
	void FUN_8008b314(MATRIX *, MATRIX *);
	void FUN_8008b238(MATRIX *);
	int FUN_8008aa50(SModel *, SProjectedVertex *, int, VECTOR *);
	void FUN_8008ab28(SModel *, SProjectedVertex *, SLineInfo *, Item *);
	void FUN_80044a20(int, int);
}

static inline void FireNode(int node, int env) {
	DAT_800d1ef0 = env ^ 1;
	DAT_800d20d8 = 0;
	FUN_80044a20(node, 1);
}

void M3dColij_LineToThisItem(Item *pItem, SLineInfo *pInfo) {
	VECTOR PosnRelStart;
	SModel *pModel;
	SProjectedVertex *pVertices;

	gte_SetColorMatrix(&pInfo->Matrix);

	pModel = DAT_800bf7a8[pItem->Region].pModels[pItem->ModelIndex];

	if (pModel->NumVerts > 128)
		pVertices = DAT_800d2160;
	else
		pVertices = (SProjectedVertex *)0x1f800000;

	if (!*(int *)pItem->Angles && !pItem->Angles[2] && !(pItem->Flags & 0x200)) {
		PosnRelStart.vx = (pItem->Pos.vx - pInfo->Start.vx) >> 12;
		PosnRelStart.vy = (pItem->Pos.vy - pInfo->Start.vy) >> 12;
		PosnRelStart.vz = (pItem->Pos.vz - pInfo->Start.vz) >> 12;
		__asm__ volatile("ctc2 $0, $5; ctc2 $0, $6; ctc2 $0, $7");
	} else {
		if (pInfo->Swapped) {
			DAT_800c13cc.t[0] = (pItem->Pos.vx - pInfo->Start.vx) >> 12;
			DAT_800c13cc.t[1] = (pInfo->Start.vz - pItem->Pos.vz) >> 12;
			DAT_800c13cc.t[2] = (pItem->Pos.vy - pInfo->Start.vy) >> 12;
		} else {
			DAT_800c13cc.t[0] = (pItem->Pos.vx - pInfo->Start.vx) >> 12;
			DAT_800c13cc.t[1] = (pItem->Pos.vy - pInfo->Start.vy) >> 12;
			DAT_800c13cc.t[2] = (pItem->Pos.vz - pInfo->Start.vz) >> 12;
			gte_ldlv0(&DAT_800c13cc.t[0]);
			gte_lcv0();
			gte_stlvnl(&DAT_800c13cc.t[0]);
		}

		FUN_800972bc(&DAT_800c13cc);

		PosnRelStart.vx = 0;
		PosnRelStart.vy = 0;
		PosnRelStart.vz = 0;

		if (*(int *)pItem->Angles || pItem->Angles[2]) {
			FUN_8008b3d4(pItem->Angles, &DAT_800c13cc);

			if (pItem->Flags & 0x200)
				FUN_8008b4e0(pItem, &DAT_800c13cc);

			FUN_8008b314(&DAT_800c13cc, &DAT_800c13cc);
			gte_SetColorMatrix(&DAT_800c13cc);
		} else {
			FUN_8008b238(&DAT_800c13cc);
			FUN_8008b4e0(pItem, &DAT_800c13cc);
			FUN_8008b314(&DAT_800c13cc, &DAT_800c13cc);
			gte_SetColorMatrix(&DAT_800c13cc);
		}
	}

	if (!(FUN_8008aa50(pModel, pVertices, pInfo->x44, &PosnRelStart) & 0x60f)) {
		DAT_800d210c = -1;
		FUN_8008ab28(pModel, pVertices, pInfo, pItem);

		if (DAT_800d210c != -1) {
			int i = Spool_GetEnvIndex(pItem->Region);

			FireNode(DAT_800d1f0c[i][DAT_800d210c], i);
		}
	}
}
