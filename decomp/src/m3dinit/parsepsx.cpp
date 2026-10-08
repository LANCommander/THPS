/* M3dInit_ParsePSX__Fi (0x800821f8) */
/* C++ (M3DINIT.CPP). Locals from the demo's MAIN.SYM; SModel/Item/Texture are the demo's layouts.
   The per-region table (64-byte entries) is laid out by offset. */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

struct SVECTOR {
	short vx, vy, vz, pad;
};

struct Vector {
	int vx, vy, vz;
};

struct SVector {
	short vx, vy, vz;
};

struct SModel {
	ushort Flags;
	ushort NumVertices;
	ushort NumNormals;
	ushort NumFaces;
	int Radius;
	Vector Box;
	short zMax;
	ushort NextLOD;
	SVECTOR Vertices[1];
};

struct Item {
	ushort Flags;
	ushort Inquiry;
	Vector Position;
	SVector Angles;
	ushort Model;
	uchar Frame;
	uchar TintIndex;
	uchar Anim;
	uchar Region;
	Item *NextItem;
	uint RGB;
};

struct Texture {
	uchar u0, v0;
	ushort clut;
	uchar u1, v1;
	ushort tpage;
	uchar u2, v2, u3, v3;
	uint TexWin;
};

struct SRegion {
	char pad0[0x10];
	SModel **ppModels; /* 0x10; count at [-1] */
	int *pItems;       /* 0x14; count at [2], items from [3] */
	char pad18[0x30 - 0x18];
	short NumParts; /* 0x30 */
	uchar Fastable; /* 0x32 */
	char pad33[0x40 - 0x33];
};

extern SRegion DAT_800bf7a8[];

int DAT_800d2120;
int DAT_800d2124;
int DAT_800d2128;
int DAT_800d212c;

extern const int DAT_800d2130;
extern ushort DAT_800d2158;

void M3dInit_ParsePSX(int Region) {
	SModel *pModel;
	Item *pItem;
	uint *pFace;
	uint Fastable;
	int i;
	int j;
	int NumModels;
	int NumParts;
	int NumItems;
	int NumVertices;
	int NumNormals;
	int NumFaces;
	int NumStitchVertices;
	Texture *pTex;
	SVECTOR *pVertex;
	SVECTOR *pNormal;
	ushort clut;
	ushort tpage;
	ushort u0v0;
	ushort u1v1;
	ushort u2v2;
	ushort u3v3;
	uint OrOfFlags;
	uint AndOfFUFlags;

	if (DAT_800d2120 != -1) {
		if (DAT_800d2120 == 18) {
			DAT_800d2124 = 0;
			DAT_800d2128 = 1;
			DAT_800d212c = 2;
		} else {
			DAT_800d2124 = 16;
			DAT_800d2128 = 17;
			DAT_800d212c = 18;
		}
	}

	NumStitchVertices = 0;
	Fastable = 1;
	NumParts = 0;
	NumModels = (int)DAT_800bf7a8[Region].ppModels[-1];
	pModel = DAT_800bf7a8[Region].ppModels[0];

	for (i = 0; i < NumModels; i++) {
		OrOfFlags = 0;
		NumVertices = pModel->NumVertices;
		NumNormals = pModel->NumNormals;
		NumFaces = pModel->NumFaces;
		AndOfFUFlags = 0xffffffff;

		if (pModel->NextLOD == 0xffff)
			NumParts++;

		if (pModel->zMax == -1)
			pModel->zMax = DAT_800d2158;

		for (j = 0, pVertex = pModel->Vertices; j < NumVertices; j++, pVertex++) {
			if (i == DAT_800d2120 && !(pVertex->pad & 0x12)) {
				pVertex->vx *= 3;
				pVertex->vy *= 2;
				pVertex->vz *= 3;
				pVertex->vy += DAT_800d2130 * 16;

				if (DAT_800d2130 < 0)
					pVertex->vz -= 240;
			}

			if (pVertex->pad & 2) {
				pVertex->vx = (ushort)pVertex->vy * 8;
				pVertex->vy = 0;
			}

			if (pVertex->pad & 0x10)
				pModel->Flags |= 0x100;

			if (pVertex->pad & 1)
				NumStitchVertices++;
		}

		if (NumVertices + NumStitchVertices > 100)
			Fastable = 0;

		if (NumNormals == NumFaces + NumVertices) {
			pNormal = pVertex;
			pVertex -= NumVertices;

			for (j = 0; j < NumVertices; j++, pNormal++, pVertex++) {
				if (pVertex->pad & 1)
					pNormal->pad |= 1;

				if (pVertex->pad & 2) {
					pNormal->pad |= 2;
					pNormal->vx = pVertex->vx;
					pNormal->vy = 0;
				}
			}
		}

		pFace = (uint *)(pVertex + NumNormals);

		for (j = 0; j < NumFaces; j++) {
			((ushort *)pFace)[6] *= 8;

			if (!(pFace[0] & 0x40))
				pFace[0] ^= 0x80;

			if (!(pFace[0] & 0x800))
				pFace[2] &= 0xffffff;

			if ((pFace[0] & 3) == 3) {
				pTex = (Texture *)pFace[4];
				clut = pTex->clut;
				tpage = pTex->tpage;
				u0v0 = ((ushort *)pFace)[10];
				u1v1 = ((ushort *)pFace)[11];
				u2v2 = ((ushort *)pFace)[12];
				u3v3 = ((ushort *)pFace)[13];

				if (pFace[0] & 0x20) {
					pFace[7] = pTex->TexWin;
				} else {
					/* not in the SYM: an int temp keeps the load a zero_extend (no HI-mode
					   load whose dying pTex would pull pTex into a0 by preference) */
					int uv = *(ushort *)pTex;

					u0v0 += uv;
					u1v1 += uv;
					u2v2 += uv;
					u3v3 += uv;
				}

				pFace[4] = u0v0 | (clut << 16);
				pFace[5] = u1v1 | (tpage << 16);
				pFace[6] = u2v2 | (u3v3 << 16);
			}

			OrOfFlags |= pFace[0];
			AndOfFUFlags &= ((ushort *)pFace)[7];

			if (pFace[0] & 0x10)
				((uchar *)pFace)[7] = ((uchar *)pFace)[6];

			pFace += pFace[0] >> 18;
		}

		if (AndOfFUFlags & 1)
			pModel->Flags |= 0x10;

		if (!(OrOfFlags & 0xc0))
			pModel->Flags |= 0x20;

		if (OrOfFlags & 0x1000)
			pModel->Flags |= 0x40;

		if (OrOfFlags & 4)
			pModel->Flags |= 4;

		pModel = (SModel *)pFace;
	}

	DAT_800bf7a8[Region].Fastable = Fastable;
	DAT_800bf7a8[Region].NumParts = NumParts;
	NumItems = DAT_800bf7a8[Region].pItems[2];
	pItem = (Item *)(DAT_800bf7a8[Region].pItems + 3);

	for (i = 0; i < NumItems; i++) {
		if (i < NumItems - 1)
			pItem->NextItem = pItem + 1;
		else
			pItem->NextItem = 0;

		pItem->Region = Region;

		if (DAT_800bf7a8[pItem->Region].ppModels[pItem->Model]->Flags & 0x10)
			pItem->Flags |= 0x20;

		if (DAT_800bf7a8[pItem->Region].ppModels[pItem->Model]->Flags & 0x20)
			pItem->Flags |= 0x1000;

		pItem++;
	}
}

extern const int DAT_800d2130 = 0;
