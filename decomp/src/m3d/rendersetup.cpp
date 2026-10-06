/* M3d_RenderSetup__FP7SCameraP9SViewportPUi (0x800831f8) flags=-fstructure-noalias */
/* C++ (M3D.CPP). Demo twin; locals from its MAIN.SYM (Window, pClipArea, opp, adj, hyp, pTex, i).
   Per-frame render setup: region-change count, camera/viewport/OT globals, the clip DR_AREA,
   viewport zoom and centre, the ten frustum plane normals (rotated into camera space with
   ApplyMatrixSV), geometry screen/offset, the scaled view matrix, the sky texture page and the
   pulsing/wibbly texture preprocessing. Levers: -fstructure-noalias; the four camera-up shorts
   at 0x800d2180 are one SVECTOR (a struct, so its stores stay ordered against the camera loads). */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct SCamera {
	uint Style;
	VECTOR Position;           /* 0x04 */
	VECTOR Focus;              /* 0x14 */
	int Distance;              /* 0x24 */
	int Height;                /* 0x28 */
	SVECTOR Angles;            /* 0x2c */
	MATRIX Transform;          /* 0x34 */
	MATRIX Inverse;            /* 0x54 */
	MATRIX View;               /* 0x74 */
	VECTOR Up;                 /* 0x94 */
};
struct SViewport {
	ushort xR;
	ushort yB;
	ushort xL;
	ushort yT;
	ushort Hither;
	ushort Yon;
	ushort TanHalf;
	ushort Zoom;
	ushort xC;
	ushort yC;
};
struct SVec { short vx, vy, vz; };
struct Texture {
	uchar f0;
	uchar f1;
	ushort f2;
	ushort f4;
	ushort f6;
};
struct SScreen {
	ushort pad0;
	ushort y;
};
int M3dMaths_SquareRoot0(int);
void M3dMaths_TransposeMat(ushort *, ushort *);
Texture *Spool_FindTextureEntry(uint);
void M3d_PreprocessPulsingColours(int);
void M3d_PreprocessWibblyTextures(int);
extern SVECTOR DAT_800c7c00[];
extern SVec DAT_800c7c50[];
extern SVec DAT_800c7c70[];
extern int DAT_800d1a24;
extern SScreen *DAT_800d1a48;
extern DR_AREA *DAT_800d1a54;
extern int DAT_800d1ed0;
extern int DAT_800d1ed4;
extern uchar DAT_800d1a14;
extern int DAT_800d16f0;
int DAT_800d21b0, DAT_800d2154, DAT_800d2150;
ushort DAT_800d2168, DAT_800d2188, DAT_800d218c;
SCamera *DAT_800d217c;
SViewport *DAT_800d2178;
uint *DAT_800d21a0;
int DAT_800d2190, DAT_800d2194;
int DAT_800d21a4, DAT_800d21a8, DAT_800d21ac;
SVECTOR DAT_800d2180;

void M3d_RenderSetup(SCamera *pCamera, SViewport *pVP, uint *ot)
{
	RECT Window;
	DR_AREA *pClipArea;
	uint opp;
	uint adj;
	uint hyp;
	Texture *pTex;

	DAT_800d2154 = DAT_800d21b0;
	DAT_800d21b0 = DAT_800d1a24;
	if (DAT_800d2154 != DAT_800d21b0)
		DAT_800d2150++;
	DAT_800d217c = pCamera;
	DAT_800d2178 = pVP;
	pVP->Yon = DAT_800d2168;
	DAT_800d21a0 = ot;
	Window.x = 0;
	Window.y = DAT_800d1a48->y;
	Window.w = DAT_800d2188;
	Window.h = DAT_800d218c;
	pClipArea = DAT_800d1a54;
	SetDrawArea(pClipArea, &Window);
	DAT_800d1a54 = pClipArea + 1;
	addPrim(DAT_800d21a0, pClipArea);
	pVP->Zoom = ((((pVP->xR - pVP->xL) >> 1) << 12) / pVP->TanHalf << 12) / DAT_800d2194;
	pVP->xC = (pVP->xL + pVP->xR) >> 1;
	pVP->yC = (pVP->yT + pVP->yB) >> 1;

	DAT_800c7c00[0].vx = 0;
	DAT_800c7c00[0].vy = 0;
	DAT_800c7c00[0].vz = -4096;
	DAT_800c7c00[0].pad = pVP->Yon;
	DAT_800c7c00[1].vx = 0;
	DAT_800c7c00[1].vy = 0;
	DAT_800c7c00[1].vz = 4096;
	DAT_800c7c00[1].pad = -pVP->Hither;

	opp = (pVP->xR - pVP->xL) << 11;
	adj = pVP->Zoom * DAT_800d2190;
	hyp = M3dMaths_SquareRoot0((opp >> 12) * (opp >> 12) + (adj >> 12) * (adj >> 12));
	DAT_800c7c00[2].vx = 0;
	DAT_800c7c00[2].vy = adj / hyp;
	DAT_800c7c00[2].vz = opp / hyp;
	DAT_800c7c00[2].pad = 0;
	DAT_800c7c00[3].vx = 0;
	DAT_800c7c00[3].vy = -(adj / hyp);
	DAT_800c7c00[3].vz = opp / hyp;
	DAT_800c7c00[3].pad = 0;

	opp = (pVP->xR - pVP->xL) << 11;
	adj = pVP->Zoom * DAT_800d2194;
	hyp = M3dMaths_SquareRoot0((opp >> 12) * (opp >> 12) + (adj >> 12) * (adj >> 12));
	DAT_800c7c00[4].vx = adj / hyp;
	DAT_800c7c00[4].vy = 0;
	DAT_800c7c00[4].vz = opp / hyp;
	DAT_800c7c00[4].pad = 0;
	DAT_800c7c00[5].vx = -(adj / hyp);
	DAT_800c7c00[5].vy = 0;
	DAT_800c7c00[5].vz = opp / hyp;
	DAT_800c7c00[5].pad = 0;

	opp = (pVP->yB - pVP->yT) >> 1;
	adj = pVP->Zoom;
	hyp = M3dMaths_SquareRoot0(opp * opp + adj * adj);
	DAT_800c7c00[6].vx = 0;
	DAT_800c7c00[6].vy = (adj << 12) / hyp;
	DAT_800c7c00[6].vz = (opp << 12) / hyp;
	DAT_800c7c00[6].pad = 0;
	DAT_800c7c00[7].vx = 0;
	DAT_800c7c00[7].vy = -((adj << 12) / hyp);
	DAT_800c7c00[7].vz = (opp << 12) / hyp;
	DAT_800c7c00[7].pad = 0;

	opp = (pVP->xR - pVP->xL) >> 1;
	adj = pVP->Zoom;
	hyp = M3dMaths_SquareRoot0(opp * opp + adj * adj);
	DAT_800c7c00[8].vx = (adj << 12) / hyp;
	DAT_800c7c00[8].vy = 0;
	DAT_800c7c00[8].vz = (opp << 12) / hyp;
	DAT_800c7c00[8].pad = 0;
	DAT_800c7c00[9].vx = -((adj << 12) / hyp);
	DAT_800c7c00[9].vy = 0;
	DAT_800c7c00[9].vz = (opp << 12) / hyp;
	DAT_800c7c00[9].pad = 0;

	{
		int i;
		for (i = 0; i < 3; i++) {
			ApplyMatrixSV(&pCamera->Transform, &DAT_800c7c00[i], (SVECTOR *)&DAT_800c7c50[i]);
			ApplyMatrixSV(&pCamera->Transform, &DAT_800c7c00[i + 3], (SVECTOR *)&DAT_800c7c70[i]);
		}
	}
	SetGeomScreen(pVP->Zoom);
	SetGeomOffset(pVP->xC, pVP->yC);
	M3dMaths_TransposeMat((ushort *)&pCamera->Transform, (ushort *)&pCamera->Inverse);
	{
		int i;
		for (i = 0; i < 3; i++) {
			pCamera->View.m[0][i] = (pCamera->Inverse.m[0][i] * DAT_800d2194) >> 12;
			pCamera->View.m[1][i] = (pCamera->Inverse.m[1][i] * DAT_800d2190) >> 12;
			pCamera->View.m[2][i] = pCamera->Inverse.m[2][i];
		}
	}
	pTex = Spool_FindTextureEntry(0xcce0187c);
	DAT_800d21a4 = pTex->f2 << 16;
	DAT_800d21a8 = pTex->f6 << 16;
	DAT_800d21ac = pTex->f0 | (pTex->f1 << 8);
	M3d_PreprocessPulsingColours(DAT_800d1ed0);
	M3d_PreprocessPulsingColours(DAT_800d1ed4);
	M3d_PreprocessPulsingColours(DAT_800d1a14);
	M3d_PreprocessWibblyTextures(DAT_800d1a14);
	DAT_800d2180.vx = -DAT_800d217c->Transform.m[1][0];
	DAT_800d2180.vy = -DAT_800d217c->Transform.m[1][1];
	DAT_800d2180.vz = -DAT_800d217c->Transform.m[1][2];
	DAT_800d2180.pad = (DAT_800d16f0 >> 12) - DAT_800d217c->Position.vy;
}
