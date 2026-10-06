/* Spool_LoadTexturesToVRAM__Fii (0x8006f854) flags=-fstructure-noalias */
/* C++ (SPOOL.CPP). Fuzzy demo twin (0.84); locals from its MAIN.SYM. Walks a region's PSX file
   past the models, texture lookup, 36-byte and 516-byte tables to the texture records. For each
   texture not yet resident it finds VRAM space (Pack_Pack), uploads the image (8-bit or 4-bit),
   then fills the Texture entry: palette (ref-counted), tpage, UVs, texture-window command and the
   resident flag. */
extern "C" {
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
}
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
struct tag_S_Pal {
	ushort Clut;
	ushort pad2;
	ushort RefCount;
};
struct Texture {
	uchar u0, v0;
	ushort Clut;              /* 2 */
	uchar u1, v1;
	ushort TPage;             /* 6 */
	uchar u2, v2;
	uchar u3, v3;
	uint Window;              /* 12 */
	uint Flags;               /* 16 */
	uint Checksum;            /* 20 */
	tag_S_Pal *pPal;          /* 24 */
	short X;                  /* 28 */
	short Y;                  /* 30 */
};
struct SPSXRegion {
	char pad0[16];
	uint *pModels;            /* 0x10 */
	uint *pPSX;               /* 0x14 */
	char pad18[64 - 0x18];
};
extern SPSXRegion DAT_800bf7a8[];
void Pack_DefragmentFully(void);
uint *Spool_SkipPackets(uint *);
tag_S_Pal *Pal_FindPaletteEntry(uint);
extern "C" {
int FUN_8004982c(int, int, int, int *, int *, int, int, uint);
void FUN_8008c714(RECT *, uint *);
ushort FUN_8008f72c(int, int, int, int);
}

void Spool_LoadTexturesToVRAM(int Region, int defrag)
{
	uint *pPSX;
	uint *pStuff;
	int Temp;
	Texture **TextureLookup;
	uint *pTextureInfo;
	uint NumTextures;
	int i;

	if (defrag)
		Pack_DefragmentFully();
	pPSX = DAT_800bf7a8[Region].pPSX;
	pStuff = Spool_SkipPackets(pPSX);
	pStuff += DAT_800bf7a8[Region].pModels[-1];
	Temp = *pStuff++;
	TextureLookup = (Texture **)pStuff;
	pStuff += Temp;
	Temp = *pStuff++;
	pStuff += Temp * 9;
	Temp = *pStuff++;
	pStuff += Temp * 129;
	pTextureInfo = pStuff;
	NumTextures = *pTextureInfo++;
	for (i = 0; i < NumTextures; i++) {
		uint *pTexture = (uint *)((char *)pPSX + *pTextureInfo++);
		uint Flags = pTexture[0];
		uint NumColours = pTexture[1];
		uint PaletteChecksum = pTexture[2];
		Texture *pTextureEntry = TextureLookup[pTexture[3]];
		if (!pTextureEntry)
			continue;
		if (pTextureEntry->Flags & 0xf0000)
			continue;
		if (pTextureEntry->Checksum == 0xcce0187c)
			Flags |= 1;
		if (pTextureEntry->Checksum == 0x68b7b136)
			Flags |= 1;
		{
			tag_S_Pal *pPal;
			ushort Width = *(ushort *)&pTexture[4];
			ushort Height = *((ushort *)&pTexture[4] + 1);
			uint *pTextureData = pTexture + 5;
			int x;
			int y;
			if (NumColours == 256) {
				int AlignedWidth = (Width + 1) & ~1;
				RECT rec;
				FUN_8004982c(0, AlignedWidth, Height, &x, &y, 8, (Flags & 1) ? 2 : 0, pTextureEntry->Checksum);
				ushort sx = x;
				ushort sy = y;
				pTextureEntry->X = sx;
				pTextureEntry->Y = sy;
				rec.x = sx;
				rec.y = sy;
				rec.w = AlignedWidth / 2;
				rec.h = Height;
				FUN_8008c714(&rec, pTextureData);
			}
			if (NumColours == 16) {
				int AlignedWidth = (Width + 3) & ~3;
				RECT rec;
				FUN_8004982c(0, AlignedWidth, Height, &x, &y, 4, (Flags & 1) ? 2 : 0, pTextureEntry->Checksum);
				ushort sx = x;
				ushort sy = y;
				pTextureEntry->X = sx;
				pTextureEntry->Y = sy;
				rec.x = sx;
				rec.y = sy;
				rec.w = AlignedWidth / 4;
				rec.h = Height;
				FUN_8008c714(&rec, pTextureData);
			}
			pPal = Pal_FindPaletteEntry(PaletteChecksum);
			pPal->RefCount++;
			pTextureEntry->pPal = pPal;
			pTextureEntry->Clut = pPal->Clut;
			pTextureEntry->TPage = FUN_8008f72c(NumColours == 256, 0, x, y);
			{
				int u = x & 63;
				uchar v;
				if (NumColours == 256)
					u <<= 1;
				else
					u <<= 2;
				pTextureEntry->u0 = u;
				v = y;
				pTextureEntry->v0 = v;
				pTextureEntry->u1 = u + Width - 1;
				pTextureEntry->v1 = v;
				pTextureEntry->u2 = u;
				pTextureEntry->v2 = v + Height - 1;
				pTextureEntry->u3 = u + Width - 1;
				pTextureEntry->v3 = v + Height - 1;
				pTextureEntry->Window = 0xe2000000 | ((u & 0xf8) << 7) | ((v & 0xf8) << 12) | ((-Height & 0xf8) << 2) | ((-Width & 0xf8) >> 3);
				pTextureEntry->Flags = (pTextureEntry->Flags & 0xfff0ffff) | 0x10000;
			}
		}
	}
}
